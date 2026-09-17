# Analyse française — observations vérifiées

Dernière mise à jour : **17 septembre 2026**.

Source principale : profil `profiles/SLES-03948.json`, analyses Ghidra, runtime PC et backend New 3DS. Les empreintes identifient la copie de travail ; elles ne certifient pas l'authenticité commerciale du dump.

| Paramètre | Valeur |
|---|---|
| Programme de démarrage | SLES_039.48 |
| Taille du programme | 1 902 592 octets |
| Charge utile, hors en-tête PS-X EXE | 1 900 544 octets |
| Chargement | `0x80010000` |
| Fin exclusive | `0x801E0000` |
| Point d'entrée | `0x800128CC` |
| Pile dans l'en-tête | `0x801FFFF0` |
| GP établi par le démarrage | `0x8009C298` |
| SHA-256 EXE | `57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44` |
| SHA-256 BIN | `9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835` |

Le démarrage efface la zone `0x8009C408..0x800FFC30`, établit la pile à proximité de `0x801FFFF8` et passe par `0x80012A44` avant la boucle d'initialisation principale.

## Analyse statique et code résident

La première génération PSXRecomp limitée au résident utilise une borne expérimentale de `0x8D000` octets à partir de `0x80010000`. Cette borne évite d'interpréter comme code certaines zones dynamiques ou de données situées plus haut dans l'EXE.

Le code résident français a été généré en shards C puis recompilé en ARM11 pour New 3DS. Plusieurs destinations indirectes manquantes ont été découvertes pendant le bring-up ; elles ont d'abord été ajoutées comme seeds, puis la stratégie a évolué vers un fallback R3000A pour éviter une régénération permanente.

## Overlays et zones 0x801xxxxx

Les analyses SU montrent qu'une partie du code dynamique est chargée vers `0x80180000`. Les variantes étudiées contiennent du MIPS cohérent et correspondent fortement à des overlays chargés depuis SU.MRG.

Une même adresse `0x801xxxxx` peut contenir plusieurs images différentes au cours de l'exécution. Toute future recompilation d'overlay doit donc être indexée par le contenu réellement chargé, pas uniquement par l'adresse virtuelle.

Le fallback R3000A du backend New 3DS est destiné à permettre l'exécution immédiate de ces blocs avant toute recompilation dédiée.

## Runtime PC

Le runtime PC a atteint :

- le logo / écran titre ;
- le menu principal français ;
- une nouvelle partie ;
- l'introduction ;
- le premier duel contre Simon Muran ;
- pose d'une carte et fin d'un tour.

Ces résultats servent de référence fonctionnelle, pas de preuve que le backend New 3DS possède déjà toutes les dépendances nécessaires.

## Backend New 3DS

Le backend actuel exécute :

- code ARM11 recompilé quand le dispatcher connaît l'adresse ;
- un basic block R3000A lorsque le code statique ne couvre pas la destination ;
- des appels BIOS HLE partiels ;
- les écritures GPU GP0/GP1 via `fm_gpu.c`.

Le dernier état observé atteint `A0:44 FlushCache`. Le dernier MMIO observé est `0x1F801074` (`I_MASK`). Le bridge GPU reçoit des mots GP0 mais aucune première image VRAM réelle n'est encore confirmée.

## Archives

SU.MRG, SD_SE.DAT, SD_BGM.DAT, WA_MRG.MRG, MODEL.MRG, MASTER.XA et MOVIE.STR ont été inventoriés. Les flux XA/STR peuvent utiliser des secteurs Form2 et demanderont un chemin CD spécifique.

## Prudence sur les adresses US

Le projet PC américain de référence utilise SLUS-01411 et des adresses différentes. Le delta observé entre points d'entrée ne prouve pas un décalage uniforme : ne jamais appliquer un offset global aux symboles US pour produire des symboles FR.

## Documents liés

- [GHIDRA_FIRST_PASS_REVIEW.md](GHIDRA_FIRST_PASS_REVIEW.md)
- [SU_LOADING_TRACE.md](SU_LOADING_TRACE.md)
- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)
- [CURRENT_STATUS.md](CURRENT_STATUS.md)
- [ACTION_PLAN.md](ACTION_PLAN.md)
