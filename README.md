# Yu-Gi-Oh! Forbidden Memories — New Nintendo 3DS

Projet expérimental de portage/recompilation de **Yu-Gi-Oh! Forbidden Memories**
PAL France (**SLES-03948**) vers **New Nintendo 3DS**.

> [!IMPORTANT]
> Le projet n'est pas encore jouable de bout en bout. En revanche, le backend 3DS
> exécute désormais une partie très importante du vrai jeu : boot, écran titre,
> menu, nouvelle partie, saisie du nom, carte, dialogues, entrée en duel et duel
> interactif. Le premier duel est jouable plusieurs tours sur la branche B135.71.
>
> Au **25 septembre 2026**, deux chantiers dominent :
> **(1) performance du duel** et **(2) chaîne de rendu 2D des dialogues hors duel**.

## État du projet — 25 septembre 2026

| Partie | État |
| --- | --- |
| Profil PAL France / SLES-03948 | ✅ Vérifié |
| Extraction / analyse PS-X EXE | ✅ |
| Analyse Ghidra française | ✅ Résident + overlays |
| Runtime PC | ✅ Jusqu'au premier duel |
| Build natif New 3DS | ✅ ARM11 / libctru |
| Code résident recompilé | ✅ |
| Fallback R3000A | ✅ |
| CD / overlays | 🟡 Fonctionnel sur le chemin courant |
| GP0 / GP1 / rasteriseur logiciel | ✅ |
| Menu principal | ✅ |
| Nouvelle partie / nom | ✅ |
| Carte / navigation | ✅ |
| Premier duel 3DS | 🟡 Jouable plusieurs tours |
| Main / adversaire | ✅ Fonctionnels sur B135.71 |
| Images des cartes | 🟡 Correspondances encore incorrectes dans certains cas |
| Dialogues avant/après duel | 🔴 Objets créés mais renderer C2 non exécuté |
| Performance duel | 🔴 ~12–15 FPS, chute vers ~4 FPS en attaque |
| Audio | ❌ |
| Sauvegarde memory card | ❌ |
| New 3DS physique | ❌ Non validé |

## Référence fonctionnelle 3DS

La branche de référence du duel reste la lignée **B135.71**. Elle a permis :

- nouvelle partie ;
- saisie et validation du nom ;
- progression jusqu'à la carte ;
- sélection d'un adversaire ;
- entrée en duel ;
- affichage de la main ;
- jeu de plusieurs tours ;
- réponse de l'adversaire ;
- rendu 3D du duel fonctionnel.

Le correctif B135.71 conserve un filet de sécurité sur le gate
`DAT_8009C4B8` lorsqu'une main valide est en attente.

## Ce que les essais B135.74 → B135.80 ont appris

### Performance

- **B135.74 PROFILE/CLEAN** : suppression des probes chauds → **aucun gain FPS mesurable**.
- **B135.75 Interpreter Fast Path** : chunks 256→2048, accès RAM accélérés → **aucun gain visible**.

Conclusion actuelle : les probes et ces micro-optimisations d'interpréteur ne
sont pas le goulet principal du duel.

### Dialogues / rendu 2D

- **B135.76** : correction de plusieurs erreurs de sélection de page VRAM.
- **B135.77** : priorité trop agressive à la draw-page → régression écran noir.
- **B135.78** : arbitrage conservateur GP1/draw-page. Sur l'écran noir :
  `GP1 = latch = draw = 0,0` et la page échantillonnée reste vide.
- **B135.79** : diagnostic chaîne objets → renderer → GP0.
  Observation : `OBJ79 n:0/5/0/0/0/0/0` mais `408BC:0` et aucun primitive 2D.
- **B135.80** : diagnostic en attente de test sur la table de fonctions
  `0x800923DC..0x800923F4`, spécialement C2 `0x800923E0`.

Le problème dialogue est donc maintenant localisé **en amont du GPU** :
la liste C2 contient 5 objets, mais son renderer attendu `FUN_800408BC`
n'est pas exécuté.

## Architecture

```text
SLES_039.48 / disc.bin
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

## Build

PSXRecomp épinglé :

```text
1965b2df424da03483a5370340433a862f78f103
```

```sh
git clone https://github.com/Unchiga/psxrecomp.git work/upstream-psxrecomp
git -C work/upstream-psxrecomp checkout 1965b2df424da03483a5370340433a862f78f103

export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
export PATH=$DEVKITARM/bin:$PATH

bash rebuild_generated_release.sh
make -C 3ds clean
make -C 3ds -j4
```

Depuis B135.74 :

- `make` → CLEAN ;
- `make profile` → PROFILE ;
- objets séparés `build-clean/` et `build-profile/`.

## Disque de test

```text
sdmc:/3ds/fm-new3ds/disc.bin

Version        : PAL France / SLES-03948
Format         : BIN brut MODE2/2352
Taille         : 548 427 600 octets
SHA-256        : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
Point d'entrée : 0x800128CC
```

Aucun dump du jeu ni BIOS Sony n'est distribué par ce dépôt.

## Priorités immédiates

1. tester B135.80 et trancher **table C2 vs dispatch indirect** ;
2. rétablir les dialogues 2D sans bridge spécifique à un personnage ;
3. conserver B135.71 comme oracle du duel ;
4. reprendre ensuite le profiling du vrai budget CPU/GPU du duel ;
5. corriger les images de cartes ;
6. poursuivre la progression et réduire les bridges de bring-up.

Voir :
[État courant](docs/CURRENT_STATUS.md) ·
[Plan d'action](docs/ACTION_PLAN.md) ·
[Roadmap](docs/ROADMAP.md) ·
[Handoff](docs/WORK_HANDOFF.md) ·
[Journal B135](docs/B135.76_80_RENDER_PIPELINE.md).

## Licences et données

**Aucun disque, BIOS PlayStation propriétaire, exécutable original ou contenu
propriétaire du jeu n'est distribué dans ce dépôt.**

Yu-Gi-Oh! et Forbidden Memories appartiennent à leurs ayants droit respectifs.
Ce projet de recherche et de portage n'est pas affilié à Konami.
