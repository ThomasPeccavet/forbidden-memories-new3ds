# Base PC — C résident français compilé

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

### Validation française du 15 septembre 2026

L'exécutable français fourni a été vérifié par SHA-256 :
`57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44`.

- Première analyse du payload complet : 721 fonctions, 17 shards, 62 346 796 octets de C et 179 lignes WARNING. Deux fonctions découvertes à 0x80100880 et 0x80146258 entraînent une analyse jusque dans des données. Cette sortie n'est pas une base validée.
- Expérience limitée au résident : 719 fonctions, 15 shards, 18 706 527 octets de C et aucune ligne WARNING dans le journal de génération.
- Les 15 shards et la table de dispatch compilent avec GCC 13.3, C11, -O0, PSX_NO_DEBUG_TOOLS : 16 fichiers objets, 16 retours 0, journaux de compilation vides.
- Le script actualisé a été exécuté de bout en bout sur le vrai EXE avec `--cc gcc`.

Preuves et journaux complets, y compris les journaux vides de compilation :
[research/pc-bootstrap/20260915T064032Z-586189fa/evidence.json](../research/pc-bootstrap/20260915T064032Z-586189fa/evidence.json).
Le champ `logs` contient les fichiers nommés par `result.steps`.

Le C français a été généré et compilé en objets, mais aucun exécutable du jeu
n'a été lié ou démarré. Aucun test New 3DS n'a été réalisé. La compilation ne
valide ni le comportement du jeu, ni les appels indirects, ni les accès matériels.
719 fonctions n'est pas un pourcentage de couverture.

### Borne résidente expérimentale

L'entrée 0x800128CC efface la mémoire de 0x8009C408 à 0x800FFC30.
Nous bornons provisoirement l'analyse à 0x8009D000, soit une taille de 0x8D000
depuis 0x80010000. La borne précise 0x8C408 a été refusée : cette révision
du recompilateur exige un alignement de 4 Kio pour une réduction de text_size.

Ce périmètre conserve les 719 autres entrées de la première génération.
La fin maximale des plages générées est 0x800918DC. C'est un argument pour
cette expérience, pas une preuve que tout code au-delà serait inutile.
La borne inclut encore des données et un morceau de la zone effacée :
ce n'est donc pas une carte exacte du code. Les images dynamiques devront
être analysées dans leur état réellement chargé.

Seul le périmètre d'analyse du recompilateur est réduit ; le fichier EXE
fourni reste intact. Le futur runtime devra conserver le chargement du payload
complet et gérer les overlays séparément. Le profil reste expérimental.

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
py -3 tools\bootstrap_pc.py --exe "CHEMIN_COMPLET\SLES_039.48" --cc gcc
```

Cette commande a été validée sous Linux. `--cc` attend un compilateur compatible
avec les options GCC/Clang ; sous Windows, installer ce compilateur ou omettre
cette option pour générer uniquement le C. La configuration CMake du
recompilateur peut utiliser un autre compilateur.

Le profil français utilise maintenant la borne résidente 0x8D000. Pour
reproduire l'essai non borné et ses avertissements, ajouter
`--analysis-size 0x1d0000`. Le résultat distingue les avertissements de
génération, la compilation des objets, le lien du runtime et le démarrage.

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

Prochain jalon : intégrer ces objets au runtime PC, fournir les données disque,
puis observer la première transition vers le menu SU. Les overlays SU déjà
identifiés doivent être intégrés avant de revendiquer un menu recompilé.
Le backend New 3DS reste un chantier distinct après validation fonctionnelle.
