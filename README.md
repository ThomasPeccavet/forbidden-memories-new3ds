# Yu-Gi-Oh! Forbidden Memories — New Nintendo 3DS

Projet expérimental de portage/recompilation de **Yu-Gi-Oh! Forbidden Memories**
(version française **SLES-03948**) vers **New Nintendo 3DS**.

> [!IMPORTANT]
> Le port n'est pas encore jouable, mais le backend 3DS exécute désormais une
> part substantielle du vrai jeu : boot PS1, chargements CD, rendu GPU logiciel,
> écran Konami, écran titre, entrée START, chargement de l'overlay `SU.mrg` et
> boucle logique du menu principal. Le verrou courant est désormais **le rendu
> visible du menu**, pas le boot général du jeu.

## État du projet — 19 septembre 2026

| Partie | État actuel |
| --- | --- |
| Profil PAL France / SLES-03948 | ✅ Vérifié |
| Extraction / analyse PS-X EXE | ✅ Fonctionnelle |
| Analyse Ghidra française | ✅ Résident + overlays SU étudiés |
| Runtime PC | ✅ Menu, nouvelle partie et premier duel atteints |
| Build natif New 3DS | ✅ `.3dsx` ARM11 compilé avec devkitARM/libctru |
| Code résident recompilé ARM11 | ✅ Lié dans le binaire 3DS |
| Dispatch hybride | ✅ ARM recompilé + fallback R3000A |
| BIOS / IRQ / VBlank nécessaires au boot | 🟡 Couverture suffisante pour atteindre le titre |
| CD-ROM / lecture secteurs | 🟡 Boot + overlay SU atteints, émulation encore partielle |
| GP0 / GP1 + rasteriseur logiciel | ✅ Rendu réel confirmé |
| Première image réelle du jeu sur 3DS/Azahar | ✅ Konami puis écran titre |
| DMA2 / synchronisation GPU | 🟡 Plusieurs chemins bridgés, à généraliser |
| GTE | 🟡 Sous-ensemble / helpers nécessaires au boot couverts |
| Pad / START | ✅ START propagé jusqu'au guest |
| Overlay `SU.mrg` | ✅ Chargé et exécuté |
| Logique du menu principal | ✅ Init + update + callback draw actifs |
| Menu principal visible | 🟡 Objets présents et positionnés, rendu final encore invisible |
| Audio XA / SPU | ❌ Non implémenté |
| Sauvegarde | ❌ Non implémentée |
| Test sur New 3DS physique | ❌ Pas encore validé |

## Jalon New 3DS atteint

Le backend Azahar affiche maintenant de vraies images produites par le jeu :

1. logo Konami ;
2. écran titre Forbidden Memories ;
3. START reconnu par la logique guest ;
4. chargement de `M:\\mrg\\SU\\SU.mrg` ;
5. initialisation du menu SU à `0x8018001C` ;
6. boucle menu à `0x80180390` ;
7. callback de dessin installé à `0x80180B4C`.

Le build diagnostique **B75** confirme également que les 11 objets d'entrée du
menu existent et que l'animation initialement figée peut être finalisée :
les objets sont ramenés à `x=160`, timer `0`, et le groupe actif reçoit les
flags attendus. Malgré cela, l'écran visible reste encore le titre.

Le problème actif est donc très ciblé :

> **déterminer pourquoi les objets SU, pourtant présents, actifs et parcourus par
> le callback de rendu, ne remplacent pas visuellement l'écran titre.**

Voir :
[État courant](docs/CURRENT_STATUS.md) ·
[Plan d'action](docs/ACTION_PLAN.md) ·
[Handoff](docs/WORK_HANDOFF.md) ·
[Prototype New 3DS](docs/NEW3DS_PROTOTYPE.md)

## Architecture actuelle

```text
SLES_039.48 / disc.bin
        |
        v
   PS-X EXE + CD
        |
        v
 CPUState / RAM PS1
        |
        v
 dispatcher hybride
   |             |
 ARM11       R3000A fallback
   \             /
    v           v
      BIOS / MMIO
        |
  +-----+------+------+
  |            |      |
 IRQ/VBlank    CD    GPU/DMA
                      |
                 GP0 / GP1
                      |
               rasteriseur SW
                      |
                    VRAM
                      |
              écran supérieur
```

Les overlays dynamiques restent exécutables via le fallback R3000A, ce qui permet
de progresser sans recompiler immédiatement chaque image chargée à
`0x801xxxxx`.

## Avancement PC vérifié

Le runtime PC expérimental a atteint le menu principal français, créé une nouvelle
partie et atteint le premier duel contre Simon Muran. Une carte a été posée et un
tour terminé.

<p align="center">
  <img src="research/first-duel/duel.png" width="48%" alt="Premier duel sur le runtime PC">
  <img src="research/first-duel/card-set.png" width="48%" alt="Carte posée pendant le premier duel">
</p>

Ces captures restent des références fonctionnelles PC. Le backend 3DS possède
désormais son propre rendu réel jusqu'à l'écran titre.

## Prototype New 3DS

Le dossier [`3ds/`](3ds/) contient notamment :

- lecture du BIN français MODE2/2352 depuis SD ;
- chargement du PS-X EXE à `0x80010000`, entrée `0x800128CC` ;
- RAM PS1 2 Mio, scratchpad et alias KSEG ;
- `CPUState` PSXRecomp ;
- dispatcher ARM11 + fallback R3000A ;
- HLE BIOS / MMIO / IRQ / pad nécessaires au chemin actuel ;
- lecture CD et file de requêtes asynchrones ;
- bridge GPU GP0/GP1, DMA et rasteriseur logiciel ;
- chargement et exécution de l'overlay SU ;
- diagnostics détaillés sur l'écran inférieur.

## Compiler

Prérequis : devkitPro `3ds-dev`, Git, Python 3.11+ et PSXRecomp épinglé à :

```text
1965b2df424da03483a5370340433a862f78f103
```

```sh
git clone https://github.com/Unchiga/psxrecomp.git work/upstream-psxrecomp
git -C work/upstream-psxrecomp checkout 1965b2df424da03483a5370340433a862f78f103
export PATH=$DEVKITARM/bin:$PATH
make -C 3ds clean
make -C 3ds PSXRECOMP_ROOT=../work/upstream-psxrecomp -j4
```

Sorties :

```text
3ds/fm-new3ds.elf
3ds/fm-new3ds.3dsx
```

## Disque de test

Le runtime cherche :

```text
sdmc:/3ds/fm-new3ds/disc.bin
```

Profil :

```text
Version        : PAL France / SLES-03948
Format         : BIN brut MODE2/2352
Taille         : 548 427 600 octets
SHA-256        : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
Point d'entrée : 0x800128CC
```

Aucun dump du jeu ni BIOS Sony n'est distribué par ce dépôt.

## Priorités immédiates

1. mesurer les commandes GP0 produites autour du rendu SU ;
2. vérifier la présence des objets du menu dans les listes de rendu du layer 2 ;
3. déterminer si les primitives du menu sont absentes, invisibles ou recouvertes ;
4. obtenir le **menu français visible et navigable** sur Azahar ;
5. poursuivre ensuite vers « Nlle partie » puis le premier duel ;
6. généraliser les bridges temporaires en émulation matérielle propre.

Le plan détaillé est dans [`docs/ACTION_PLAN.md`](docs/ACTION_PLAN.md).

## Données du jeu et licences

**Aucun disque, BIOS PlayStation propriétaire, exécutable original ou contenu
propriétaire du jeu n'est distribué dans ce dépôt.**

Yu-Gi-Oh! et Forbidden Memories appartiennent à leurs ayants droit respectifs.
Ce projet de recherche et de portage n'est pas affilié à Konami.
