# Analyse française — observations consolidées

Dernière mise à jour : **25 septembre 2026**.

Source : profil SLES-03948, analyses Ghidra, runtime PC et backend New 3DS.

## Identité

| Paramètre | Valeur |
|---|---|
| Programme | SLES_039.48 |
| Taille EXE | 1 902 592 octets |
| Payload | 1 900 544 octets |
| Load | `0x80010000` |
| Fin exclusive | `0x801E0000` |
| Entry | `0x800128CC` |
| Stack | `0x801FFFF0` |
| GP | `0x8009C298` |
| SHA-256 EXE | `57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44` |
| SHA-256 BIN | `9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835` |

## Résident / overlays

Le code résident français est recompilé en ARM11 dans le prototype. Les
destinations dynamiques et overlays restent exécutables par fallback R3000A.

Les zones `0x801xxxxx` peuvent être réutilisées par plusieurs images : une
recompilation d'overlay doit être indexée par le contenu chargé, pas uniquement
par l'adresse.

## Runtime PC

Le runtime PC reste l'oracle fonctionnel. Il a validé :

- menu ;
- nouvelle partie ;
- introduction ;
- Simon Muran ;
- main ;
- pose d'une carte ;
- passage au tour adverse.

## Backend New 3DS : état confirmé

Le backend 3DS affiche et exécute désormais :

- logo et titre ;
- menu ;
- nouvelle partie ;
- saisie du nom ;
- carte ;
- premier duel ;
- main ;
- plusieurs tours ;
- tour adverse ;
- rendu 3D du duel.

Les anciennes notes indiquant qu'aucune vraie image VRAM n'était confirmée sont
désormais obsolètes.

## Système d'objets 2D

Les objets display sont stockés à partir de :

```text
0x800F1210
stride 0x70
```

Heads :

```text
C0 0x800F11C0
C2 0x800F11C2
C4 0x800F11C4
C6 0x800F11C6
C8 0x800F11C8
CA 0x800F11CA
CC 0x800F11CC
```

Ghidra montre que `FUN_80041674` parcourt ces 7 heads en parallèle avec une
table de 7 fonctions située à `0x800923DC..0x800923F4`.

Le renderer de C2 est `FUN_800408BC`, qui lit `DAT_800F11C2`, construit des
primitives texturées 0x2C et appelle notamment `FUN_800424B8`.

Sur le bug dialogue actuel, C2 contient 5 objets mais 408BC n'est pas exécuté.

## Presenter / VRAM

Les essais B135.76–78 ont montré qu'il faut distinguer :

- GP1 display page ;
- draw-area E3/E4 ;
- backbuffer en construction ;
- page effectivement présentée.

B135.77 a prouvé qu'on ne peut pas traiter systématiquement la draw-page comme
frontbuffer.

## Performance

B135.74 et B135.75 n'ont pas amélioré visiblement la cadence. La lenteur ne doit
donc plus être attribuée par défaut aux probes ou au seul overhead de chunking
de l'interpréteur.

## Prudence sur les adresses US

Ne jamais appliquer un delta global SLUS→SLES. Les symboles français doivent
être vérifiés individuellement.

## Documents liés

- [CURRENT_STATUS.md](CURRENT_STATUS.md)
- [ACTION_PLAN.md](ACTION_PLAN.md)
- [B135.76_80_RENDER_PIPELINE.md](B135.76_80_RENDER_PIPELINE.md)
