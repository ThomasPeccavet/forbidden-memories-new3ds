# B136.48 — accès mémoire du cœur recompilé

## Pourquoi

Unai a diminué le coût du GPU, mais les derniers rapports gardent environ
1,4–1,5 seconde de travail avant présentation par fenêtre de 2 secondes.
Le rendu et les callbacks SEQ sont inclus dans ce temps ; le reliquat ne
prouve pas à lui seul le coût de la mémoire ou du dispatcher.

Les callbacks RAM du CPU recompilé assemblent encore les mots de 16/32 bits
par octets. Le chemin rapide de l'interpréteur B135.75 ne les remplace pas.
Sur ARM11, les accès alignés peuvent utiliser une instruction mémoire de la
bonne largeur. Les tests MDEC/SPU étaient également évalués avant la RAM.
En mode PROFILE, chaque écriture vérifiait dix adresses surveillées.

## Changement

- RAM avant les cas MMIO 16/32 bits ; les plages ne se recouvrent pas.
- memcpy avec alignement connu uniquement après un test du pointeur hôte.
  Le compilateur peut émettre LDR/STR et LDRH/STRH pour ces accès.
- Conserver les opérations par octets pour les pointeurs non alignés, les
  bornes du tampon et le chemin MMIO existant.
- Surveillance équivalente avec deux plages, plutôt qu'une boucle de dix
  adresses (une adresse isolée et neuf octets contigus).
- Essai conseillé : `make -C 3ds PROFILE=0 UNAI=1 -j2`, cible
  `fm-new3ds-unai.3dsx`, instrumentation désactivée.

Les octets et l'horloge du jeu ne sont pas modifiés. Le correctif CD B136.47
reste présent ; une sauvegarde de duel déjà corrigée peut être restaurée.

## Validation et estimation

Le module mémoire réel est testé dans les deux modes PROFILE. Les nouveaux
cas couvrent les miroirs RAM, KSEG0/KSEG1, les quatre alignements hôtes,
les offsets pairs/impairs, les dernières positions valides et les écritures
mixtes byte/half/word. Les tests SPU/DMA/timers/MDEC existants restent requis.

Le gain total dépend de la part réelle du temps dans ces callbacks et de
l'instrumentation ; aucune estimation fiable de FPS ni garantie de 30 FPS
n'est possible sans essai du combat réel. Ce changement réduit du travail
CPU sans sauter des images ou accélérer artificiellement le jeu.
