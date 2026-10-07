# État courant — New Nintendo 3DS

Dernière mise à jour : **7 octobre 2026**.

## B136.14 : position du transport ReadS/XA

L'essai B136.13 atteint la phase XA 06 et le script 0A, mais GetlocL renvoie
encore 00004D8C alors que la lecture demandée commence à 00031734 et finit
à 00031834. Le backend confirmait ReadS (1B) sans appliquer le wrapper
7BA00 : SetMode, Setloc puis ReadS. B136.14 applique ces effets dans le
backend commun main/IRQ, après acceptation de la commande.

Le transport XA silencieux avance selon le temps hôte (75 secteurs/s,
150 si mode double vitesse), avec fraction conservée, et s'arrête sur
Pause/Stop/Init. ReadN garde sa progression par secteurs/DataReady. La pause
hôte ne rattrape pas le temps passé en pause. Aucune modification des flags
XA, de la fin de requête ou de l'état script. intro-diag ajoute xa_transport.
Les 38 tests passent, dont les scénarios C de position, GetlocL BCD,
Pause, changement de mode, ReadN et rejet sans effets d'une commande.
Le texte/scène reste à confirmer en jeu. Audio XA et vidéo STR/MDEC ne
sont pas décodés par cette correction.

## B136.13 : livraison asynchrone des callbacks CD

L'introduction reste avec une requête type 4, flags 00080410, Pause terminée,
file vide et script état 84. Le bridge livrait le callback avant de retourner
au demandeur, alors que 80014478 pose son busy après l'enqueue. B136.13
rend d'abord la main, puis livre la completion à partir de la frame hôte
suivante. Le contexte interrompu est sauvegardé à la livraison (GPR, PC,
HI/LO), avec métadonnées pending séparées des callbacks actifs. Une commande
supplémentaire en attente est refusée sans écraser la précédente.

38 tests host passent, dont un test C du scheduler/delivery réel. L'essai
jeu reste nécessaire : la correction de timing n'est pas une implémentation
audio XA ou STR/MDEC et ne prouve pas encore la résolution du texte/scène.
intro-diag expose maintenant la phase XA et le callback pending/actif.

## Nouvelle partie : titre/menu validés, introduction à diagnostiquer

L'essai utilisateur B136.11 valide Konami, l'attente START, l'animation du menu,
la nouvelle partie et la saisie du nom. Après validation, la boîte de dialogue
apparaît sans texte et la zone de scène contient des données graphiques
corrompues. C460 reste à 00080410 sur plusieurs collectes ; le GPU continue.
Ce constat ne prouve pas encore une cause unique CD, script ou MDEC.

B136.12 ajoute intro-diag.txt en PROFILE : requête active lue à 8009C2A8,
états CD et DataReady, état/script/glyphes du traceur existant, tête de liste
texte et compteurs STR/MDEC. Lecture seule, même cadence 120 frames ; aucun
skip supplémentaire ou changement de rendu. Reproduire après le nom et
collecter intro-diag.txt, debug-latest.txt complet et c4b8-diag.txt.

## B136.11 : distinguer le STR du titre interactif

L'essai B136.10 révèle une attente STR avant le titre SU : attendre START
à cet endroit était une régression. Le premier STR non pris en charge est
à nouveau terminé automatiquement. Le titre interactif attend ensuite
START dans 80180390. Le bridge B75 est supprimé : après 24 updates, il
rendait prématurément visibles les entrées que SU initialise masquées,
pendant que « Appuyer sur START » reste affiché. Animation et visibilité
appartiennent au code guest. Les fondus restent sans mutation hôte.
Le rendu B136.11 et l'attente de START sont validés par l'essai utilisateur.

## Correction B136.9 après essai Azahar

Essai utilisateur du 7 octobre : les écrans s'enchaînent et C4B8 reste à 1.
Deux défauts restent visibles : passage au menu sans START et fonds superposés.
B136.10 désarmait le skip STR automatique, réservait la demande à un front START,
retire le saut hôte vers l'état menu et remplace le bridge de fondu par une
observation : seul 8001522C applique désormais la progression et le nettoyage.
Le comportement visuel reste à tester. Le décodage STR/MDEC est incomplet.

Le correctif SPU/DMA4 permet d'atteindre le titre et le menu, puis l'écran
devient noir. La trace B136.8 et le code identifient une corruption hôte :
le bridge CD efface 16 octets à 8009C4B4, dont le verrou de rendu C4B8 et
ses couleurs. B136.9 utilise le tampon LibCD sync 800F7130 sur 8 octets,
sans toucher au tampon ready adjacent. Test C du writer réel avec sentinelles
ajouté. La disparition de l'écran noir reste à confirmer sur le jeu.

## Audit hors jeu du 6 octobre

La branche `fix/b136-spu-dma4-mmio-audit` corrige quatre défauts reproduits :
déclaration C du helper SPU, écritures SPU 16 bits perdues, écritures partielles
DMA4 ignorées et état SPU/DMA4 non réinitialisé. Les tests host du vrai module
mémoire passent en CLEAN et PROFILE. **Le démarrage du jeu reste à retester.**
Voir [preuves et limites de l'audit](B136_MMIO_AUDIT.md).

## Résumé

Le projet a déjà atteint menu, nouvelle partie, saisie du nom, dialogues, carte
et duel dans différentes itérations B135. Le travail courant vise maintenant à
reconstruire un chemin startup plus fidèle, avec moins de bypass et davantage de
modèles matériels réels.

Le verrou actif est désormais identifié comme une chaîne précise :

~~~text
second FUN_80043CD4
  -> FUN_80014478
  -> FUN_800777D8(0)
  -> TestEvent(F1000000)
  -> événement BIOS F0000009 / 0x20
  -> synchronisation SPU
  -> DMA4
  -> relance ReadN
~~~

Le correctif SPU minimal vient d'être intégré et doit encore être testé.

## Branche active

~~~text
diag/b135.90-main-menu-items
~~~

## Startup validé

Le chemin Europe/PAL est restauré :

~~~text
bios_region_bfc7ff52=45
ov68160_enter=1
ov68160_return=1
ov68160_v0=00000000
~~~

Le startup poursuit ensuite jusqu'au second `FUN_80043CD4`.

## Point de blocage

Trace typique :

~~~text
post681_43cd4=2
post681_43dc8=0
post681_159f4=0

c460=01C00016
c484=00000000
~~~

La requête active est :

~~~text
remaining = 0x2000
buffer    = 0x801E1639
LBA       = 0x3172D
callback  = 0x80014A4C
cmd       = 0x06 (ReadN)
~~~

## Pipeline CD : ce qui est prouvé

La chaîne précédente fonctionne :

~~~text
b34_start=62
b34_done=62
b32_calls=62
b32_ok=62
b32_fail=0
~~~

Le watcher a prouvé que la nouvelle requête est correctement créée par le chemin
autour de `800142F8`.

Il ne faut donc pas corriger ce problème en forçant le compteur remaining ou
`C460`.

## Gate BIOS

Le code atteint :

~~~text
FUN_800777D8(0)
  -> FUN_80073DC8(F1000000)
~~~

`80073DC8` correspond à `TestEvent`.

Événement :

~~~text
used    = 1
enabled = 1
ready   = 0
class   = F0000009
spec    = 00000020
mode    = 00002000
~~~

Le consommateur est donc valide. Le problème se situe dans le producteur.

## SPU / DMA4

La routine de transfert est bien appelée :

~~~text
FUN_80075AFC(3, 801DC000, 0x200)
hits = 63
~~~

Pointeurs confirmés :

~~~text
MADR = 1F8010C0
BCR  = 1F8010C4
CHCR = 1F8010C8
~~~

Mais avant de programmer DMA4, Psy-Q attend l'état SPU :

~~~text
spu_base=1F801C00
spu_mode=0
spu_reg_1a6=0000
spu_reg_1aa=0000
spu_reg_1ae=0000
~~~

Pour le mode 0, la condition attendue est :

~~~text
(SPU + 0x1AA) & 0x30 == 0x20
~~~

Comme le runtime ne modélisait pas le SPU, cette condition n'était jamais vraie.

## Correctifs intégrés mais pas encore validés

### DMA4 minimal

Ajout de :
- MADR/BCR/CHCR canal 4 ;
- START et completion synchrone de bring-up ;
- flag DICR canal 4 ;
- compteur de completion ;
- bridge vers l'événement BIOS exact.

### SPU minimal

Ajout des registres utilisés par Psy-Q :

~~~text
1F801DA6 transfer address
1F801DA8 transfer data
1F801DAA control
1F801DAE status
~~~

Le modèle reflète les bits de mode de transfert nécessaires aux wait loops.
Il ne produit pas encore d'audio.

## Prochain critère de succès

Après build PROFILE :

~~~text
dma4_madr_writes > 0
dma4_bcr_writes  > 0
dma4_chcr_writes > 0
dma4_transfers    > 0
dma4_event_bridge > 0
~~~

Ensuite :
- `req10` doit descendre sous `0x2000` ou atteindre zéro ;
- `C460` doit progresser ;
- `post681_43dc8` et `post681_159f4` doivent devenir non nuls.

## Performance

Les problèmes de performance observés dans les branches fonctionnelles restent
réels, mais **ils ne sont pas le verrou immédiat de cette branche startup**.

Le profiling B105-B135 reste utile une fois la chaîne de démarrage propre
rétablie.

## Ce qui reste non validé

- correction SPU minimale ;
- passage du DMA4 ;
- livraison de l'événement BIOS ;
- progression du ReadN à 0x3172D ;
- sortie du second 80043CD4 ;
- reprise complète du startup ;
- audio SPU réel ;
- XA ;
- sauvegarde ;
- fidélité générale sans bridges.

Voir [B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).
