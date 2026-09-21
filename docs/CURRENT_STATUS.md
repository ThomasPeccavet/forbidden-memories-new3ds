# État courant — New Nintendo 3DS

Dernière mise à jour : **19 septembre 2026**.

## Résumé

Le backend New 3DS/Azahar a franchi le boot graphique : le logo Konami et l'écran
titre de **Forbidden Memories PAL France SLES-03948** sont affichés à partir des
données réelles du jeu.

Le pad START est maintenant reconnu par le guest, l'overlay `SU.mrg` est chargé,
le menu principal est initialisé et sa boucle d'update s'exécute. Le callback de
dessin du menu est également appelé.

Le verrou actif n'est donc plus « démarrer le jeu », mais :

> **faire apparaître visuellement le menu SU alors que sa logique, ses objets et
> son callback de rendu sont déjà actifs.**

## Chemin actuellement validé

- PS-X EXE chargé à `0x80010000` ;
- entrée guest `0x800128CC` ;
- code résident ARM11 + fallback R3000A ;
- appels BIOS nécessaires au boot ;
- VBlank / pad / IRQ suffisants pour progresser ;
- lectures CD réelles depuis le BIN ;
- file CD asynchrone suffisamment fonctionnelle pour le boot ;
- GTE/helpers rencontrés sur le chemin du boot ;
- DMA2 / GPU waits bridgés pour les cas observés ;
- GP0/GP1 et rasteriseur logiciel actifs ;
- logo Konami affiché ;
- écran titre affiché ;
- START transmis au guest ;
- état résident 8 atteint ;
- `M:\\mrg\\SU\\SU.mrg` chargé ;
- overlay SU exécuté à `0x801xxxxx` ;
- init menu `0x8018001C` exécutée ;
- update menu `0x80180390` exécutée ;
- callback draw `0x80180B4C` installé et appelé.

## Jalons diagnostiques B57 → B75

Les builds de bring-up ont successivement isolé plusieurs verrous :

- **B57/B59** : lecture CD et curseur de requêtes ;
- **B62** : helpers GTE nécessaires au chemin courant ;
- **B67/B68** : file de requêtes CD async ;
- **B70** : completion d'une commande de file graphique type `0x20` ;
- **B71** : sortie robuste d'une attente DMA2 ;
- **B72** : START étiré 10 frames, conforme au scénario PC connu ;
- **B73** : transition contrôlée vers l'état 8 et chargement réel de SU ;
- **B74** : preuve que le callback draw du menu est bien appelé ;
- **B75** : finalisation de l'animation d'entrée des 11 objets du menu.

Ces bridges sont des outils de bring-up. Ils devront être remplacés ou
généralisés par une émulation matérielle/logicielle plus propre une fois les
causes racines stabilisées.

## Dernier résultat observé — B75

Capture du 19 septembre 2026 :

```text
BUILD B75-MENU-ENTRANCE-BRIDGE
RUN:Y
MENU I/U/D:1/148/0
CB:80180B4C
draw:147

ENT bridge:1
frame:3059
objs:11
C0:0
C5:1>0

O0 flags:00D8  x:160  target:160  timer:0
O4 flags:00D8  x:160             timer:0
O5 flags:0088  x:160             timer:0

GPU gp0:301316
display:0,0
view:0,0
```

Interprétation :

- le menu est bien initialisé ;
- l'update tourne ;
- le callback de dessin est réellement appelé ;
- les 11 objets existent ;
- l'animation initialement figée a été terminée ;
- les objets du groupe actif sont à la position finale `x=160` ;
- l'écran supérieur affiche pourtant encore le titre.

Le problème n'est donc plus un simple timer d'animation, ni un START manquant,
ni un overlay non chargé.

## Hypothèses de travail immédiates

À départager par instrumentation, sans en choisir une arbitrairement :

1. les objets SU ne sont pas réellement parcourus par le renderer de layer 2 ;
2. ils sont parcourus mais ne génèrent pas de primitives GP0 ;
3. les primitives sont générées mais utilisent texture/CLUT/coords incorrects ;
4. elles sont rendues dans une zone VRAM non affichée ;
5. elles sont rendues puis recouvertes par des objets de l'écran titre encore actifs.

## Prochaine instrumentation

Le prochain build doit mesurer séparément :

- GP0 avant/après `FUN_80041674` (renderer global) ;
- GP0 avant/après le callback `0x80180B4C` ;
- heads/tails des listes d'objets, en particulier le layer 2 ;
- appartenance des pointeurs `DAT_80184794..` à cette liste ;
- derniers opcodes/coordonnées de la trace GPU ;
- ordre relatif des objets titre et menu.

Critère de succès : savoir si le défaut est **avant GP0**, **dans GP0**, ou
**après GP0 dans la présentation VRAM**.

## Ce qui reste non validé

- menu SU visible et navigable ;
- nouvelle partie sur backend 3DS ;
- duel sur backend 3DS ;
- émulation CD/IRQ/DMA générale sans bridges de bring-up ;
- GTE complet ;
- audio SPU/XA ;
- memory card / sauvegarde ;
- performance et stabilité sur New 3DS physique.

Le runtime PC reste la référence fonctionnelle pour comparer le comportement du
menu et du premier duel.
