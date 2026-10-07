# État courant — New Nintendo 3DS

Dernière mise à jour : **7 octobre 2026**.

## Correction B136.9 après essai Azahar

Essai utilisateur du 7 octobre : les écrans s'enchaînent et C4B8 reste à 1.
Deux défauts restent visibles : passage au menu sans START et fonds superposés.
B136.10 désarme le skip STR automatique, réserve la demande à un front START,
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
