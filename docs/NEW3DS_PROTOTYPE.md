# Premier prototype natif New 3DS — 16 septembre 2026

**Prototype de plateforme compilé, pas encore un jeu jouable. Aucun lancement
sur console physique n'a été vérifié.** Les tests de progression sur PC sont
suspendus au profit de l'adaptation 3DS.

## Essayer maintenant

1. Décompresser `fm-new3ds-prototype.zip`.
2. Copier le dossier `3ds` à la racine de la carte SD d'une New 3DS disposant
   déjà du Homebrew Launcher.
3. Ouvrir Homebrew Launcher et lancer `fm-new3ds.3dsx`.

Le disque n'est pas nécessaire pour afficher le prototype. La capture fixe du
duel, provenant du PC, est identifiée **CAPTURE PC FIXE** sur l'écran inférieur.
Elle sert à juger la lisibilité et le format, pas à simuler un portage terminé.

| Commande | Action dans ce prototype |
| --- | --- |
| X | Alterner capture fixe / rasteriseur PS1 natif ARM |
| Y | Image complète 4:3 / pixels 1:1 avec 8 lignes coupées en haut et en bas |
| Croix directionnelle | Déplacer le triangle dans la vue du rasteriseur |
| START + SELECT | Quitter |

Le rasteriseur est celui de PSXRecomp, recompilé pour ARM11 et alimenté par des
primitives de démonstration. Le triangle se déplace et change de couleur. Il ne
reçoit pas encore les commandes GPU du jeu. Aucun débit d'images du jeu n'est
mesuré par cette démonstration.

## Première couche du portage

- `3ds/source/platform.c` : présentation RGB555 PS1 vers framebuffer BGR8 libctru,
  écran supérieur 400×240, viewport 320×240 centré, stéréoscopie désactivée ;
  conversion des boutons en masque PS1 actif à zéro.
- `3ds/source/disc.c` : lecture de secteurs MODE2/Form1 depuis SD, contrôle de
  taille/synchronisation/PVD, chargement du payload de SLES_039.48 en RAM PS1.
- `3ds/source/main.c` : initialisation libctru, demande d'accélération New 3DS,
  boucle graphique, entrées et démonstration du rasteriseur partagé.
- Le binaire intègre `gpu_sw_renderer.c` et `gpu_vram_dirty.c` du moteur épinglé.
  Aucun SDL, OpenGL, serveur de débogage, BIOS ni code généré du jeu n'est lié.

En ajoutant le BIN français vérifié sous `3ds/fm-new3ds/disc.bin`, le prototype
charge son EXE en mémoire et affiche l'entrée `800128CC`. **Il ne l'exécute pas.**
Le lecteur ne couvre pas encore les secteurs Form2, CD-DA, XA ou les commandes
asynchrones du contrôleur CD. Il ne constitue pas un remplacement complet du CD.

Le masque de boutons prépare B→croix, A→rond, X→triangle, Y→carré,
L/R→L1/R1 et ZL/ZR→L2/R2. X et Y restent utilisés par l'interface de ce prototype.

## Compilation

Chaîne officiellement supportée par libctru : [devkitARM et devkitPro](https://github.com/devkitPro/libctru#setup).
Installer le groupe `3ds-dev` avec les outils devkitPro. Depuis le dépôt :

```sh
git clone https://github.com/Unchiga/psxrecomp.git work/upstream-psxrecomp
git -C work/upstream-psxrecomp checkout 1965b2df424da03483a5370340433a862f78f103
make -C 3ds PSXRECOMP_ROOT=../work/upstream-psxrecomp -j4
```

Sortie : `3ds/fm-new3ds.3dsx`. `DEVKITPRO`, `DEVKITARM` et le PATH des outils doivent
être configurés par devkitPro. Sous Windows, lancer `make` dans son shell MSYS2.

Préparer un nouveau dossier SD (Python 3.11+, Pillow pour la capture) :

```sh
python tools/prepare_3ds_sd.py --app 3ds/fm-new3ds.3dsx --preview research/first-duel/duel.png --output work/3ds-sd
```

Ajouter éventuellement `--disc "chemin/vers/le/disque.bin"`. Le script vérifie
alors la taille et le SHA-256 français avant de copier le disque. Ne jamais
committer ce disque ou les dossiers de travail.

## Validation effectuée et limites

Compilation et édition de liens ARM11 effectuées avec devkitARM GCC 16.1.0,
libctru issue de l'image officielle devkitpro/devkitarm. En-tête 3DSX et symboles
du rasteriseur présents. Les avertissements de compilation observés concernent
l'indentation et un commentaire dans le rasteriseur amont.

Pas de validation sur matériel, pas de preuve de performance d'un duel, pas de
son ni de sauvegarde. Le prochain jalon est de raccorder le CPU/dispatch, les
interruptions, le CD et les commandes GPU à cette cible, puis d'obtenir le menu
animé calculé par le jeu. Le chargement de l'EXE seul ne suffit pas à ce jalon.

Licences et provenance : `3ds/licenses/`. Preuve de compilation :
`research/new3ds/build.json`.
