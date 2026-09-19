# Prototype natif New 3DS — état du 19 septembre 2026

Le prototype exécute désormais suffisamment de la version française pour
afficher le logo Konami et l'écran titre, reconnaître START, charger l'overlay
SU et entrer dans la boucle du menu principal.

## Backend actuel

- libctru / ARM11 ;
- BIN MODE2/2352 depuis SD ;
- PS-X EXE à `0x80010000` ;
- RAM PS1 2 Mio + scratchpad + alias KSEG ;
- code résident PSXRecomp ;
- dispatcher natif ;
- fallback R3000A ;
- BIOS/MMIO/IRQ/pad nécessaires au chemin courant ;
- CD sector reader + requêtes async ;
- GPU GP0/GP1 + DMA/bridges de synchronization ;
- rasteriseur logiciel ;
- overlays dynamiques exécutables en RAM guest ;
- diagnostics détaillés écran inférieur.

## Résultat graphique validé

Le backend a affiché de vraies images du jeu dans Azahar :

1. Konami ;
2. écran titre Forbidden Memories.

Ce résultat invalide l'ancienne description « aucune image réelle » des notes du
17 septembre.

## Overlay SU

Après START :

- état résident 8 sélectionné ;
- `SU.mrg` chargé ;
- signature overlay observée à `0x80180000` ;
- init `0x8018001C` exécutée ;
- update `0x80180390` exécutée en boucle ;
- `DAT_8009C898 = 0x80180B4C` ;
- callback draw réellement appelé ;
- 11 objets du menu présents en RAM.

B75 montre que l'animation d'entrée peut être terminée et que les objets du groupe
actif se retrouvent à `x=160`, timer `0`, flags visibles. L'écran reste
néanmoins sur le titre : le prochain travail est donc dans la chaîne
**objet → renderer → GP0 → VRAM visible**.

## Architecture

```text
EXE + CD
   |
   v
CPUState / RAM
   |
   +--> code ARM11 recompilé
   |
   +--> fallback R3000A
   |
   v
BIOS / MMIO / IRQ / pad
   |
   +--> CD / overlays
   |
   +--> GPU / DMA --> GP0 --> rasteriseur --> VRAM --> écran
```

## Bridges de bring-up importants

Le `main.c` courant contient plusieurs bridges instrumentés qui ont permis de
franchir des attentes spécifiques :

- CD stream / requêtes async ;
- helpers GTE ;
- completion graphique type `0x20` ;
- attente DMA2 ;
- impulsion START 10 frames ;
- entrée contrôlée vers l'état 8 ;
- animation d'entrée SU.

Ils sont utiles pour localiser les causes, mais constituent encore de la dette de
bring-up à remplacer progressivement.

## Build

PSXRecomp :

```text
1965b2df424da03483a5370340433a862f78f103
```

```sh
export PATH=$DEVKITARM/bin:$PATH
make -C 3ds clean
make -C 3ds PSXRECOMP_ROOT=../work/upstream-psxrecomp -j4
```

Disque :

```text
sdmc:/3ds/fm-new3ds/disc.bin
```

## Limites

- menu SU pas encore visible ;
- pas encore de nouvelle partie sur 3DS ;
- CD/IRQ/DMA/GTE encore partiellement bridgés ;
- audio absent ;
- sauvegarde absente ;
- pas encore de validation New 3DS physique.

Voir [CURRENT_STATUS.md](CURRENT_STATUS.md) et [ACTION_PLAN.md](ACTION_PLAN.md).
