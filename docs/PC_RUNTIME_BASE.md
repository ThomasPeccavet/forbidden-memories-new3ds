# Base PC — première compilation réelle

Révision choisie : Unchiga/psxrecomp, 1965b2df424da03483a5370340433a862f78f103.
C'est le sous-module pointé par le projet YuGiOhForbiddenMemoriesRecomp lors
de cette inspection. Ne pas appliquer les adresses SLUS du jeu américain au
jeu français.

## Vérification effectuée

- Récupération du moteur et checkout détaché de cette révision.
- Compilation Release de psxrecomp-game et psxrecomp-toml : succès.
- GCC/G++ 13.3, CMake 4.4.3, générateur Unix Makefiles, Linux.
- Mode CHD et tests globaux désactivés pour construire uniquement les outils.
- Programme de contrôle original : addiu v0,zero,42 ; jr ra ; nop.
- Traduction stricte avec découverte reachable et profil OpenBIOS : succès.
- Compilation du shard C généré avec gcc -std=c11, PSX_NO_DEBUG_TOOLS et
  runtime/include : succès, production d'un fichier objet.
- Le script bootstrap_pc.py a lui-même été exécuté avec le checkout existant :
  configuration, compilation et génération réussies.

Ces validations portent sur l'outil et une fonction synthétique, pas sur le
jeu. Aucun exécutable de Forbidden Memories n'a été généré, lié ou démarré.
Aucun test New 3DS n'a été réalisé. Le test synthétique ne valide ni les delay
slots complexes, ni les interruptions, ni les accès matériels.

## Architecture retenue pour l'expérience

PS1 EXE français -> recompiler -> shards C -> runtime PC -> futur backend 3DS.
Le pseudo-C Ghidra reste une source d'analyse ; on ne le compile pas directement.
La première génération française utilise l'entrée et les 17 gestionnaires
d'états observés. Elle ne déclare pas l'intégralité des fonctions Ghidra comme
fiables et n'intègre pas encore les overlays SU. Les différentes images de
code occupant la même adresse devront rester distinctes.

## Pourquoi la 3DS n'est pas encore un simple build

Le runtime contient SDL2/SDL3, rendu OpenGL/Vulkan ou logiciel, gestion de
threads via Win32/POSIX, audio et périphériques PS1. Son mécanisme d'overlays
prévoit aussi des bibliothèques natives chargées dynamiquement et un recours
à l'interprétation pour le code non traduit. Il ne faut pas supposer ces
mécanismes disponibles tels quels sur New 3DS.

La version 3DS demandera notamment un affichage adapté au GPU de la console,
une sortie audio, les entrées, les fichiers SD et l'ordonnancement compatible.
La stratégie privilégie une compilation des overlays avant l'exécution, avec
sélection selon le contenu chargé. La faisabilité et les performances restent
à mesurer ; aucune prise en charge 3DS n'est ajoutée dans cette livraison.

## Reproduire

Prérequis : Python 3.11+, Git, CMake 3.20+, compilateur C/C++20.
Sous Windows, lancer depuis l'invite développeur du compilateur installé.

```bat
py -3 tools\bootstrap_pc.py
```

Cela télécharge la révision dans work/psxrecomp, compile les outils et traduit
le programme synthétique. Le script ne modifie pas un checkout préexistant
qui n'est pas propre et à la bonne révision.

Avec l'exécutable français extrait (en-tête PS-X EXE inclus, pas payload.bin) :

```bat
py -3 tools\bootstrap_pc.py --exe "CHEMIN_COMPLET\SLES_039.48"
```

Cette voie prépare une expérience de génération française ; elle n'a pas
encore été exécutée ici, le binaire français n'étant plus présent dans
l'espace de travail. La génération peut exposer de nouveaux blocages du
recompilateur ; conserver le journal même en cas d'échec.

Résultats et journaux à partager : research/pc-bootstrap/<date>.
Code généré et dépendances locales : work/, exclus par le gitignore existant.
Les chemins TOML sont absolus et utilisent des slashs : le test a révélé que
la résolution des chemins relatifs en amont peut remonter hors du projet.

## Dépendance et licences

Le moteur affiche PolyForm Noncommercial 1.0.0 dans son fichier LICENSE,
avec ses notices de dépendances propres. Aucun changement de licence n'est
appliqué, et le moteur n'est pas recopié dans ce dépôt : le script le récupère
avec ses notices. OpenBIOS possède sa notice distincte. La configuration
sélectionne explicitement son profil pour éviter le profil SCPH implicite.

Sources inspectées :
- https://github.com/Unchiga/YuGiOhForbiddenMemoriesRecomp/blob/main/.gitmodules
- https://github.com/Unchiga/psxrecomp/tree/1965b2df424da03483a5370340433a862f78f103
- recompiler/CMakeLists.txt, src/main_psx.cpp et src/config_loader.cpp
- runtime/runtime.cmake, README.md, LICENSE, bios/OpenBIOS.toml

Prochain jalon : générer le C français, résoudre les blocages de génération,
puis construire le runtime et observer son démarrage. La compilation réussie
de l'outil seule ne garantit pas que ce jalon sera immédiatement atteint.
