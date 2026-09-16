# Yu-Gi-Oh! Forbidden Memories — New Nintendo 3DS

Projet expérimental de portage/recompilation de **Yu-Gi-Oh! Forbidden Memories**
(version française **SLES-03948**) vers **New Nintendo 3DS**.

> [!IMPORTANT]
> Le port **New 3DS n'est pas encore jouable**. Un prototype natif ARM11 compile
> en `.3dsx`, mais le CPU du jeu n'est pas encore raccordé et son exécution sur
> console physique n'a pas encore été validée.

## État du projet — 16 septembre 2026

| Partie | État actuel |
| --- | --- |
| Identification du disque français | ✅ Profil SLES-03948 vérifié |
| Extraction / analyse PS-X EXE | ✅ Fonctionnelle |
| Analyse statique / outils Ghidra | ✅ Première passe et outils disponibles |
| Runtime expérimental PC | ✅ Menu principal atteint |
| Nouvelle partie sur PC | ✅ Introduction française parcourue |
| Premier duel sur PC | ✅ Main distribuée, carte posée, tour terminé |
| Build native New 3DS | ✅ `.3dsx` ARM11 compilé avec devkitARM/libctru |
| Affichage 3DS | ✅ RGB555 PS1 → framebuffer 3DS + rasteriseur logiciel ARM |
| Lecture du BIN depuis SD | ✅ MODE2/Form1 + chargement du PS-X EXE |
| Exécution du jeu sur 3DS | ❌ Pas encore raccordée |
| Audio / XA / SPU / sauvegarde 3DS | ❌ Pas encore implémentés |
| Test sur New 3DS physique | ❌ Pas encore validé |

### Avancement PC vérifié

Le runtime PC expérimental a permis de démarrer la version française, atteindre
le menu principal, créer une nouvelle partie, parcourir l'introduction et entrer
dans le premier duel contre Simon Muran. Une carte a été posée face cachée et le
tour a été terminé avec apparition du tour adverse.

<p align="center">
  <img src="research/first-duel/duel.png" width="48%" alt="Premier duel sur le runtime PC">
  <img src="research/first-duel/card-set.png" width="48%" alt="Carte posée pendant le premier duel">
</p>

Ces captures proviennent du **runtime PC**, pas encore de la New 3DS.

Documentation associée :
[Premier menu](docs/FIRST_MENU.md) ·
[Premier duel](docs/FIRST_DUEL.md) ·
[Runtime PC](docs/PC_RUNTIME_BUILD.md)

## Prototype New 3DS actuel

Le dossier [`3ds/`](3ds/) contient maintenant une vraie application native
libctru. Elle permet de valider la couche plateforme avant de raccorder
l'exécution du jeu.

Le prototype sait actuellement :

- initialiser l'affichage et les entrées avec **libctru** ;
- activer l'accélération New 3DS ;
- présenter une image PS1 **BGR/RGB555 320×256** sur l'écran supérieur ;
- utiliser le rasteriseur logiciel PSX de **PSXRecomp** compilé pour ARM11 ;
- convertir les boutons 3DS vers un masque de manette PS1 ;
- lire le BIN français directement depuis la carte SD sans charger le disque
  complet en RAM ;
- vérifier la structure MODE2/Form1 du disque ;
- charger le `PS-X EXE` français dans une RAM PS1 de 2 Mio et retrouver son point
  d'entrée `0x800128CC`.

Le point d'entrée est seulement **chargé et affiché : il n'est pas encore
exécuté**. Le CPU/dispatch, les interruptions, le contrôleur CD complet, XA,
SPU, les sauvegardes et les commandes GPU du jeu restent à raccorder.

Voir [`docs/NEW3DS_PROTOTYPE.md`](docs/NEW3DS_PROTOTYPE.md) et la preuve de build
[`research/new3ds/build.json`](research/new3ds/build.json).

## Compiler le prototype New 3DS

### Prérequis

- devkitPro avec le groupe **3ds-dev** (`devkitARM`, `libctru`, `3dsxtool`) ;
- Git ;
- Python 3.11+ pour les outils de préparation ;
- une copie locale de PSXRecomp à la révision utilisée par ce projet.

Depuis la racine du dépôt :

```sh
git clone https://github.com/Unchiga/psxrecomp.git work/upstream-psxrecomp
git -C work/upstream-psxrecomp checkout 1965b2df424da03483a5370340433a862f78f103
make -C 3ds PSXRECOMP_ROOT=../work/upstream-psxrecomp -j4
```

Sous Windows, utiliser de préférence le shell **MSYS2/devkitPro** afin que
`DEVKITPRO`, `DEVKITARM`, `make` et les outils 3DS soient correctement exposés.

La sortie attendue est :

```text
3ds/fm-new3ds.3dsx
```

## Préparer la carte SD

Le script fourni peut construire automatiquement un dossier prêt à copier :

```sh
python tools/prepare_3ds_sd.py \
  --app 3ds/fm-new3ds.3dsx \
  --preview research/first-duel/duel.png \
  --output work/3ds-sd
```

Puis copier le dossier `work/3ds-sd/3ds/` à la racine de la carte SD.

Structure obtenue :

```text
SD:/
└── 3ds/
    └── fm-new3ds/
        ├── fm-new3ds.3dsx
        ├── preview.rgb555   # optionnel
        └── disc.bin         # optionnel, dump personnel vérifié
```

Le disque n'est **pas nécessaire** pour afficher la démonstration graphique.
Pour tester également son ouverture et le chargement du PS-X EXE :

```sh
python tools/prepare_3ds_sd.py \
  --app 3ds/fm-new3ds.3dsx \
  --preview research/first-duel/duel.png \
  --disc "chemin/vers/votre/disc.bin" \
  --output work/3ds-sd-disc
```

Le script refuse un BIN ne correspondant pas au profil français connu.

### Profil du disque actuellement supporté

```text
Version       : PAL France / SLES-03948
Format        : BIN brut MODE2/2352, piste unique
Taille        : 548 427 600 octets
SHA-256       : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
Point d'entrée: 0x800128CC
```

## Commandes du prototype 3DS

| Bouton | Action actuelle |
| --- | --- |
| `X` | Alterner capture PC fixe / rasteriseur PSX ARM |
| `Y` | Basculer image complète 4:3 / affichage 1:1 recadré |
| Croix directionnelle | Déplacer le triangle de démonstration |
| `START + SELECT` | Quitter |

Le triangle du rasteriseur est une **primitive de démonstration** : il ne
provient pas encore des commandes GPU exécutées par Forbidden Memories.

## Outils de rétro-ingénierie

Extraction et inventaire du disque :

```sh
python tools/inspect_disc.py "chemin/Forbidden Memories (France).bin" work/extracted
```

Première analyse Ghidra automatisée :

```sh
python tools/run_ghidra.py \
  --ghidra "chemin/vers/ghidra" \
  --payload work/extracted/payload.bin
```

Le dépôt contient aussi des outils pour le bootstrap PC, les probes du runtime,
le suivi des overlays et la préparation de la SD 3DS.

## Organisation du dépôt

- [`3ds/`](3ds/) — prototype natif New 3DS, Makefile, code plateforme et licences ;
- [`pc/`](pc/) — intégration du runtime expérimental PC ;
- [`tools/`](tools/) — extraction, Ghidra, bootstrap/replay PC et préparation 3DS ;
- [`profiles/`](profiles/) — empreintes et paramètres de la version française ;
- [`docs/`](docs/) — analyses, preuves de progression et documentation technique ;
- [`research/`](research/) — captures, manifests et éléments de validation reproductibles ;
- `work/` — fichiers générés/localement récupérés, ignorés par Git.

## Prochains jalons

1. raccorder le CPU/dispatch du runtime au prototype ARM11 ;
2. implémenter les interruptions et les accès CD nécessaires au démarrage ;
3. envoyer les vraies commandes GPU du jeu au rasteriseur ;
4. obtenir le premier menu **calculé par le jeu directement sur New 3DS** ;
5. mesurer les performances et la mémoire sur console physique ;
6. raccorder audio, XA/SPU, sauvegardes et overlays jusqu'à obtenir un duel puis
   la campagne complète.

## Données du jeu et licences

**Aucun disque, BIOS PlayStation, exécutable original ou contenu propriétaire du
jeu n'est distribué dans ce dépôt.** Les utilisateurs doivent fournir leur propre
copie du jeu lorsqu'un test l'exige. Ne commitez jamais de BIN/CUE, dumps RAM ou
autres données extraites du jeu.

Le prototype 3DS réutilise du code du rasteriseur de PSXRecomp et libctru. Les
informations de provenance et licences correspondantes se trouvent dans
[`3ds/licenses/`](3ds/licenses/).

Yu-Gi-Oh! et Forbidden Memories appartiennent à leurs ayants droit respectifs.
Ce projet communautaire de recherche et de portage n'est pas affilié à Konami.
