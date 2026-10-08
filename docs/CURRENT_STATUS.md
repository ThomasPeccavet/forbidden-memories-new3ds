# État courant — New Nintendo 3DS

Dernière mise à jour : **8 octobre 2026**.

## B136.42 : servir l'horloge avant l'exécution guest

B136.41 tient 60 Hz mais mesure 53 attentes VSync pour 24 images, sans gain.
B136.42 déplace les ticks/callbacks dus avant l'exécution du jeu, après les
entrées et le quick-load. Le VSync voit ainsi les ticks écoulés pendant
l'attente hôte précédente. Cadence, budgets et règles de présentation
restent identiques ; le gain reste à mesurer dans Azahar.
Voir [l'ordre d'exécution et ses limites](B136_42_CLOCK_ORDER.md).

## B136.41 : reprise des tranches et horloge VBlank indépendante

B136.40 mesure 285 ms d'attente après épuisement du budget sur 2006 ms.
B136.41 reprend ces tranches sans attendre si aucun VSync guest n'est actif.
Le VBlank PS1 et les root timers suivent désormais le temps hôte à 60 Hz,
avec rattrapage borné et reset à la reprise d'une longue pause/quick-load.
Les frontières de présentation et l'isolation SEQ sont conservées.
Le gain de FPS et le rythme visible restent à vérifier dans Azahar.
Voir [les règles et limites](B136_41_WALL_CLOCK.md).

## B136.40 : attribution des attentes du planificateur

B136.39 divise par deux le coût moyen des sprites au repos, mais le temps
économisé se retrouve largement dans les attentes. B136.40 distingue les
attentes après sortie sur budget, avec VSync actif, et les autres attentes.
Les compteurs VSync et sorties sur budget sont des deltas par fenêtre.
Le rythme du jeu et du séquenceur reste inchangé.
Voir [la définition et les limites](B136_40_WAIT_ATTRIBUTION.md).

## B136.39 : boucle spécialisée des sprites opaques

Au repos, B136.38 mesure 469 ms pour les sprites 64h sur 2004 ms,
contre 26 ms de parcours/autres opérations DMA. B136.39 spécialise les
formats texture et utilise des tables de modulation constantes par sprite.
700 cas dans deux modes conservent tous les pixels et compteurs de texels,
y compris les accès VRAM chevauchants. Le débit du cas modulé est environ
2–2,45 fois supérieur sur le banc x86 ; le gain ARM/global reste à mesurer.
Voir [validation et limites](B136_39_SPRITE_SPANS.md).

## B136.38 : diagnostic complet du coût GPU

B136.37 mesure 982 ms DMA2 sur 2049 ms dans une autre fenêtre de duel.
Une commande 2Ah échantillonnée prend 30,9 ms. B136.38 chronomètre toutes
les commandes terminées et sépare le traitement des paquets du reste du
DMA. Ce build PROFILE sert à identifier le prochain hotspot ; aucun gain
de FPS n'est annoncé. Les mesures comprennent leur coût d'instrumentation.
Voir [la définition des compteurs](B136_38_COMPLETE_GPU_TIMING.md).

## B136.37 : modulation exacte des couleurs par table

B136.36 reste à 16,50 latches/s dans le duel utilisateur : aucun triangle
ne prend le chemin neutre. B136.37 cible les couleurs variables des 4488
triangles rapides mesurés. Une table de 1 Kio remplace les multiplications
et saturations des composantes, avec spécialisation par format de texture.
Les tests vérifient toutes les entrées et comparent le rendu complet sur
640 cas dans deux modes. Le banc x86 montre 1,12–1,25 fois le débit du
chemin ciblé ; le gain ARM et la cadence globale restent à mesurer.
Voir [validation et limites](B136_37_COLOR_LOOKUP.md).

## B136.36 : modulation neutre des polygones texturés

La fenêtre utilisateur B136.35 mesure 16,45 latches/s et identifie 3Ch/34h
comme premiers opcodes GPU échantillonnés. B136.36 spécialise leur cas
opaque à modulation neutre, avec les mêmes pixels que B136.35 sur 640 cas
compilés en deux modes. 57 tests passent. Le cas ciblé est environ 2,7 à
3 fois plus rapide sur le banc local x86 ; aucun gain ARM/global n'est
annoncé avant mesure. Le rapport ajoute la couverture du cas neutre.
Voir [les résultats et limites](B136_36_NEUTRAL_TEXTURE.md).

## B136.35 : calcul exact des gradients Gouraud et classement GPU

B136.34 mesure 920 ms de DMA2 sur 2064 ms en duel. B136.35 remplace
les divisions 64 bits du setup Gouraud non texturé par une estimation
corrigée et vérifiée en entier, avec fallback exact. Les tests comparent
250000 quotients et 600 triangles pixel par pixel avec B136.34.
Le rapport compact classe désormais les opcodes GPU sur toute sa fenêtre.
56 tests passent ; le gain sur ARM/Azahar reste à mesurer.
Voir [les changements et leurs limites](B136_35_EXACT_GOURAUD.md).

## B136.34 : suppression des dumps lourds pendant les mesures

La seconde mesure en duel B136.33 indique 12,45 latches/s, sans gain
observable sur B136.32 (14,6/s). Elle ne prouve pas une régression causale,
les fenêtres de combat pouvant différer. Les scans sont bien désactivés.
B136.34 coupe les anciens dumps SD par défaut, conserve le rapport compact,
et expose les temps DMA2/rendu imbriqués. Le gain reste à mesurer.
Voir [la validation et les limites](B136_34_COMPACT_PERF.md).

## B136.33 : réduction des scans de diagnostic pendant les combats

La mesure utilisateur en duel B136.32 indique 14,6 latches d'image/s,
avec 1013 ms avant présentation sur 2122 ms. B136.33 désactive les anciens
parcours d'OT dédiés aux diagnostics des cartes en main. Le prédicat du
bridge de récupération reste actif, ainsi que le tri et le rendu.
Le gain en jeu reste à mesurer sur la même sauvegarde de combat.
Voir [les changements et leur validation](B136_33_OT_DIAGNOSTICS.md).

## B136.32 : mesure des performances globales

L'essai utilisateur B136.31 valide le début du jeu après environ 15 secondes
à la fin de l'intro. Le problème prioritaire devient la cadence globale,
annoncée à 10 FPS ou moins. Le diagnostic intro ne suffit pas à attribuer
cette lenteur au GPU, au CPU ou au séquenceur.

B136.32 ajoute `perf-latest.txt` en PROFILE, par fenêtres réelles de deux
secondes, et réactive un échantillonnage limité du code ARM (1 appel sur 64).
Il distingue la cadence hôte des nouveaux latches d'image, expose les temps
par phase et le temps audio imbriqué. Aucun gain FPS n'est annoncé avant les
mesures en jeu. Voir [la procédure](B136_32_GLOBAL_PERF.md).

## B136.31 : livraison du timer découplée des updates graphiques

L'utilisateur a confirmé que B136.30 termine finalement l'intro et atteint
Simon Muran. La longue attente reste anormale. Le timer avançait à chaque
intervalle hôte, mais son callback n'était autorisé qu'à l'entrée `80012C50`,
une fois par update du jeu. Le rendu lent et les tranches de l'interpréteur
retardaient cette livraison ; plusieurs échéances se regroupaient dans I_STAT.

B136.31 exécute le callback natif complet dans un CPU et une pile séparés,
à la frontière VBlank hôte et dès la réactivation des IRQs dans le dispatcher,
en conservant les masques et événements BIOS.
Le rejeu de la capture B136.30 termine après 374 livraisons supplémentaires,
avec le contexte principal préservé. Les tests menu antérieurs passent aussi.
Le parcours et la durée réelle dans Azahar restent à confirmer. Voir
[la méthode, les preuves et les limites](B136_31_SEQ_DELIVERY.md).

## B136.30 : timer du séquenceur 17 fois trop lent

Le log utilisateur B136.29 confirme les retours des interruptions audio
(279 appels / 279 retours), mais le script attend encore la fin du SEQ.
Le compteur 2 avançait de 4096 ticks par VBlank 3DS ; sa source système/8
demande 70560 ticks à 60 Hz. Cette erreur de cadence pouvait prolonger
l'attente de plusieurs minutes.

Le rejeu avec le vrai timer termine la même séquence après 13833 intervalles
avec l'ancien code, contre 989 après correction (230,55 s contre 16,48 s
simulées à 60 Hz). Le parcours Azahar reste à confirmer. Voir
[le détail de cadence et les limites du rejeu](B136_30_SEQ_CLOCK.md).

## B136.29 : registre SPU manquant, freeze menu reproduit

Les captures menu B136.24/25 et fin d'intro B136.27 ont été rejouées avec
`fm_memory.c` et l'interpréteur natif réels. Les stores SH au masque SPU
`1F801D98/1F801D9A` étaient ignorés ; le séquenceur attendait ensuite un bit
qui restait nul. Le masque 24 bits est désormais mémorisé et relisible.

Les deux callbacks menu reviennent en 291/302 blocs. Le SEQ de fin d'intro
termine et le service natif efface son drapeau `0x80`, sans forçage du script.
Le test antérieur avec MMIO générique ne reproduisait pas le vrai backend.
Voir [les preuves et limites](B136_29_SPU_REVERB_FREEZE.md).

Le parcours complet Azahar reste à valider. Retester depuis un boot neuf :
le format quickstate passe en version 3 pour sauvegarder le nouveau registre.
L'écran inférieur reste sans lignes de debug ; les diagnostics fichiers restent.

## B136.18 : limite VLC native 00FFFFFF

Essai B136.17 : amélioration ressentie (~15 FPS visuels), mais petites pauses.
Le log mesure 155 décodages sur 26281 ms (5,85 images/s MDEC), codec 7293 ms,
309 frames STR et surtout `vlc_hle calls=0 fallback=312 limit=00FFFFFF`.
La HLE n'était donc pas active : le garde-fou limitait arbitrairement le
nombre de demi-mots à 20000h. Le jeu utilise FFFFFFh comme frontière de
comparaison pour traiter une frame entière, sans écrire jusqu'à cette adresse.

B136.18 accepte cette frontière sans modifier la limite du jeu. Les accès
restent bornés au vrai buffer de sortie, au flux et aux tables en RAM ; un
calcul de frontière qui déborde uint32 reste refusé avec fallback atomique.
49 tests host passent, dont 525 fixtures différentielles contre la routine
Ghidra, avec la valeur native FFFFFFh pour les trois versions du format.
`movie_perf` ajoute max_decode_ms pour observer les pics du codec MDEC.
Ni cadence CD, saut de frame natif ni décodage audio ne sont modifiés.

Retester au boot, vidéo entière sans START. Vérifier l'activation `vlc_hle`
et comparer movie_perf ; les petites pauses ne sont pas encore attribuées
à une cause unique ni annoncées corrigées avant cet essai.

## B136.17 : Huffman/VLC natif en C

L'essai B136.16 confirme une amélioration ressentie, mais une cadence basse
et une impression d'accélération. Mesure : 153 décodages en 25757 ms, soit
5,90 FPS ; le codec MDEC consomme 7237 ms (~47 ms par image). 309 frames STR
sont publiées. Le lecteur natif compare les frames disponibles à la position
du flux et peut en sauter ; cette différence n'est pas une mesure directe
du nombre d'images affichées ou une preuve d'un bug d'horloge.

B136.17 traduit la routine FR 800914A8 en C, avec les tables Huffman étendues
du jeu, DC signés/prédictifs, codes d'échappement, tokens groupés et état
résident de continuation. Les commandes et coefficients envoyés au MDEC
sont conservés. Un buffer temporaire permet un fallback natif sans modifier
la RAM/CPU si les adresses, tables, tailles ou overlaps sont incompatibles.
Le dispatcher principal et les appels générés imbriqués utilisent cette HLE.
Ni le timing CD ni la règle de synchronisation du lecteur ne sont changés.

49 tests host passent. Une référence distincte issue du pseudo-C Ghidra
original est exécutée sur 420 fixtures (versions 1/2/3, coefficients signés,
AC/escape/table secondaire/tokens groupés, quatre tailles de morceaux).
Sortie entière, retour, pointeurs et sept mots de continuation sont comparés.
Le checkpoint généré retourne au RA et conserve le chemin natif en cas de
refus. `vlc_hle` expose succès, fallback, durée, table et taille de morceau.
Le gain en FPS et la compatibilité avec le vrai flux restent à valider dans
Azahar, depuis un boot neuf et sans START pendant la vidéo d'ouverture.

## B136.16 : transferts vidéo par blocs

Essai utilisateur B136.15 : la vidéo entre Konami et le titre fonctionne,
mais à environ 5–10 FPS. Le XA est décodé (387 secteurs / 780192 frames PCM)
et ndspInit échoue avec D880A7FA ; sortie audio toujours non validée.
La scène après le nom n'affiche pas encore la vidéo/animation attendue.
La priorité utilisateur est maintenant la fluidité de la vidéo d'ouverture.

B136.16 remplace les copies STR octet par octet par des copies RAM bornées,
active les bursts DMA0/1 et copie le FIFO MDEC de sortie par bloc. Les uploads
GPU DMA2 et LoadImage passent par un flux GP0 groupé : en phase A0, copie
par ligne via le renderer, avec conservation du dirty-state et du miroir.
Le chemin par mot reste disponible pour les DMA inversés, débordements RAM
et sources LoadImage non alignées. Aucun saut de frame ni changement IDCT.

47 tests host passent. Comparaison bit à bit des chemins GP0, uploads RGB24,
stripes, transferts partiels, pixels impairs et débordements VRAM ; MDEC
word/burst, DMA inversés et rebouclage RAM. Un benchmark synthétique sur
l'hôte mesure environ 24 ms contre 3 ms pour les uploads de 100 images ;
ce résultat ne prédit pas les FPS dans Azahar ou sur New3DS.

intro-diag conserve `movie_perf=decoded/elapsed_ms/decode_ms/fps_x100` après
la vidéo. FPS = cadence des décodages MDEC couleur entre le premier et le
dernier, pas cadence du framebuffer Azahar. `decode_ms` mesure le codec
seul ; `elapsed_ms` inclut lecture, lecteur/Huffman, uploads et attente.
Retester depuis un boot neuf, laisser finir la vidéo sans START et collecter
intro-diag au titre. L'amélioration réelle reste à confirmer sur cet essai.

## B136.15 : décodage XA et lecteur STR/MDEC

L'utilisateur confirme le texte après validation du nom sur B136.14.
La position XA dépasse la fin demandée, les flags CD retombent à zéro et le
script continue. Konami/titre/menu et texte sont donc validés sur B136.14.

B136.15 ajoute la lecture complète MODE2/2352, un décodeur XA ADPCM
4/8 bits mono/stéréo avec historique par canal et le filtrage fichier/canal.
Les échantillons à 37800/18900 Hz sont envoyés à NDSP via des buffers PCM
stéréo en mémoire linéaire, sans écraser les buffers en cours. Le CdlMix du
jeu règle la matrice CD. Le résultat ndspInit est exposé ; si le DSP échoue,
le décodage et le lecteur vidéo peuvent continuer sans sortie audio.

Les secteurs STR sont réassemblés par frame et publiés dans le ring natif
uniquement une fois complets, avec marqueur de rebouclage et backpressure.
Le lecteur/Huffman/LoadImage du jeu est conservé. Le décodeur MDEC de la
révision PSXRecomp épinglée est raccordé aux registres 1F801820/824, au DMA0
entrée et DMA1 sortie ; un callback DMA1 séparé reprend le contexte guest.
Le skip STR automatique est désarmé pour tester la vraie vidéo du boot.

46 tests locaux passent. L'oracle FFmpeg compare exactement le PCM de
16 secteurs synthétiques utilisant les quatre filtres ; les tests couvrent
également le ring STR, MDEC RGB16/RGB24, DMA en attente, callback, CdlMix et
propriété des buffers NDSP. L'essai audiovisuel dans Azahar reste nécessaire.
Pas encore de mixage des 24 voix SPU ; la conversion de fréquence NDSP
n'est pas le filtre zigzag matériel PS1. Emphase XA non prise en charge.
Les savestates du port ne sérialisent pas encore ce nouveau pipeline :
tester par démarrage neuf, sans quick-load. intro-diag expose media_raw,
xa_decoded, pcm_frames, dsp, str_sectors/frames et mdec_blocks/in/out.

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
