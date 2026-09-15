# Construction du moteur PC français

Cette cible assemble les shards français, le runtime psxrecomp et OpenBIOS.
Ce n'est pas une cible New 3DS. La traduction des overlays SU n'est pas
encore intégrée ; le moteur possède une voie d'interprétation du code dynamique.
Un futur démarrage par cette voie ne prouverait pas une recompilation complète.

## Résultat vérifié

Le 15 septembre 2026, la cible fm-pc a été compilée et liée sous Linux avec
GCC/G++ 13.3, CMake 4.4.3 et SDL3 3.4.10. Le binaire obtenu fait 13 923 240
octets. Les objets français et le backend OpenBIOS sont inclus dans le lien.
Le build final conserve cinq avertissements dans des sources du moteur
(retour de system ignoré et risques de troncature de messages), sans erreur.

Le lancement headless entre dans main(), charge le profil SLES-03948 et
configure la borne des overlays à 0x9D000. Il quitte avec le code 1 :
`psxrecomp: no disc image selected; exiting.`
Le disque n'étant pas disponible, ce test n'exécute pas le jeu et ne valide
ni OpenBIOS en fonctionnement, ni le menu, ni les périphériques PS1.

Les journaux et empreintes sont dans
[evidence.json](../research/pc-runtime/evidence.json).

## Préparation

Exécuter d'abord `tools/bootstrap_pc.py --exe <SLES_039.48>`.
Noter le répertoire de travail produit : `work/pc-bootstrap/<identifiant>`.
Les commandes suivantes utilisent des chemins à adapter, depuis la racine du dépôt.

La révision du moteur est `1965b2df424da03483a5370340433a862f78f103`.
Son fichier main.cpp inclut auth.h même avec PSX_NETPLAY=OFF ; il faut donc
initialiser le sous-module d'en-têtes, sans activer le réseau :

```sh
git -C work/psxrecomp submodule update --init lib/recomp-net
```

Révision obtenue pour recomp-net : `83b8468e165ff5459b7f51dd3c821d91e2fb977c`.
La cible du jeu ajoute ce chemin d'inclusion ; aucun source du moteur n'est modifié.

Générer OpenBIOS depuis le répertoire du moteur (Bash sous Linux ou Git Bash
sous Windows ; CMake et le compilateur doivent être disponibles) :

```sh
cd work/psxrecomp
PSXRECOMP_BIOS_BUILD=recompiler/build-pc bash tools/regen_bios.sh --config bios/OpenBIOS.toml
```

Adapter build-pc si bootstrap_pc.py a reçu un autre --build-dir.
Le BIOS libre fourni et ses notices restent dans le checkout du moteur.

## Configuration et compilation

Depuis la racine du dépôt, remplacer chaque chemin entre chevrons :

```sh
cmake -S pc -B work/pc-runtime -DCMAKE_BUILD_TYPE=Release -DPSXRECOMP_ROOT="<chemin absolu du moteur>" -DFM_GENERATED_DIR="<chemin absolu du run>/generated" -DFM_GAME_CONFIG="<chemin absolu du run>/game.toml" -DBUILD_TESTING=OFF -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build work/pc-runtime --config Release --target fm-pc --parallel 4
```

SDL3 est récupéré par CMake si nécessaire. Rewind, Vulkan et le lanceur
graphique sont désactivés pour cette première cible. Sur un PC Linux avec
fenêtres, les bibliothèques de développement X11/Wayland doivent être disponibles.

Dans notre environnement sans serveur d'affichage, la configuration utilise
en plus `-DSDL_UNIX_CONSOLE_BUILD=ON` et
`-DOPENGL_gl_LIBRARY=/usr/lib/x86_64-linux-gnu/libGL.so.1`.
Ce dernier chemin est propre à la machine de test, pas un réglage Windows.
Cette version sert à lancer des diagnostics avec `--headless`.

## Lancement avec les ressources originales

```sh
work/pc-runtime/fm-pc --game "<run>/game.toml" --bios "<moteur>/bios/openbios.bin" --disc "<jeu>/disc.cue" --headless --renderer software
```

Le nom/emplacement du binaire peut inclure `.exe` et `Release/` sous Windows.
Pour un build doté d'un backend de fenêtres, retirer `--headless` pour afficher
le rendu logiciel. Cette procédure graphique n'est pas encore validée ici.

Le fichier SLES_039.48 seul ne remplace pas le disque : la configuration exe
sert notamment au contrôle du code en mémoire ; le lancement du jeu demande
une image disque. Fournir le BIN et son CUE ensemble, avec leurs noms d'origine.
Ne pas versionner ces fichiers ni les sources C générées dans Git.

Empreinte du BIN attendu :
`9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835`
(548 427 600 octets, 233 175 secteurs de 2352 octets).
