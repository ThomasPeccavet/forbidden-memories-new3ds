# Prototype natif New 3DS — état du 25 septembre 2026

Le prototype ne se limite plus au menu : il peut entrer dans le premier duel et
jouer plusieurs tours.

## Backend

- libctru / ARM11 ;
- BIN MODE2/2352 depuis SD ;
- PS-X EXE à `0x80010000` ;
- RAM PS1 2 Mio + scratchpad + KSEG ;
- code résident PSXRecomp ;
- dispatcher natif ;
- fallback R3000A ;
- BIOS/MMIO/IRQ/pad du chemin courant ;
- CD async / overlays ;
- GP0/GP1 ;
- DMA / bridges de bring-up ;
- rasteriseur logiciel ;
- diagnostics écran inférieur.

## Chemin graphique validé

Le backend a affiché :

1. Konami ;
2. écran titre ;
3. menu principal ;
4. saisie du nom ;
5. carte ;
6. main du duel ;
7. plateau 3D ;
8. plusieurs tours.

## Duel

B135.71 constitue la baseline fonctionnelle.

Points positifs :

- main visible ;
- sélection/jeu de cartes ;
- adversaire actif ;
- animations 3D utilisables.

Limites :

- performance ~12–15 FPS ;
- ~4 FPS sur certaines attaques ;
- associations image de carte / contenu encore fausses dans certains cas.

## Dialogues 2D

Le défaut actuel n'est plus classé comme un problème de simple framebuffer.

B135.79 a montré :

- 5 objets dans C2 ;
- renderer C2 `800408BC` jamais appelé ;
- aucune primitive 2D issue de ce chemin.

B135.80 instrumente la table de renderers utilisée par `80041674`.

## Builds CLEAN / PROFILE

Depuis B135.74 :

```sh
cd 3ds
make clean
make -j4           # CLEAN
make profile -j4   # PROFILE
```

Les objets sont séparés dans `build-clean` et `build-profile`.

## Limites

- dialogue 2D avant/après duel ;
- performance ;
- images de cartes ;
- bridges matériels ;
- audio ;
- sauvegarde ;
- hardware New 3DS non validé.

Voir [CURRENT_STATUS.md](CURRENT_STATUS.md).
