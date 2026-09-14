# Forbidden Memories — New Nintendo 3DS

Projet de portage natif intégral de **Yu-Gi-Oh! Forbidden Memories**, version
française **SLES-03948**, pour **New Nintendo 3DS**.

**État : outils de rétro-ingénierie. Aucun jeu 3DS compilé ou jouable.**
L'objectif est de conserver l'ensemble du jeu ; sa faisabilité et ses performances
sur console restent à établir.

## Démarrer

Prérequis : Python 3.11+, copie locale du disque français en BIN/CUE, puis Ghidra
et le JDK demandé par la version de Ghidra installée.

Depuis la racine du dépôt :

```sh
python tools/inspect_disc.py "chemin/Forbidden Memories (France).bin" work/extracted
python tools/run_ghidra.py --ghidra "chemin/ghidra" --payload work/extracted/payload.bin
```

Sur Windows, utiliser `py -3` si `python` n'est pas disponible. Les chemins
contenant des espaces doivent rester entre guillemets. Le lanceur appelle
`support/analyzeHeadless.bat` sous Windows et `support/analyzeHeadless` ailleurs.

L'analyse écrit dans un nouveau sous-dossier horodaté de `work/ghidra/` :
projet Ghidra, pseudo-C par fonction, index des fonctions, appels reconnus et
journal. Il s'agit du pseudo-C des fonctions identifiées par Ghidra, pas d'une
restauration complète du code source ni d'un programme compilable.

L'extraction fonctionne sans dépendance externe. `pip install capstone` permet
également d'obtenir un désassemblage initial local.

## Organisation

- `tools/inspect_disc.py` : inventaire ISO9660 et extraction du programme PS1.
- `tools/run_ghidra.py` : validation du payload français et lancement de Ghidra.
- `tools/ghidra/` : initialisation du programme et export d'analyse.
- `profiles/SLES-03948.json` : empreintes et paramètres mesurés sur le disque fourni.
- `docs/ANALYSIS.md` : observations confirmées et limites.
- `docs/ROADMAP.md` : étapes du portage et critères de validation.

## Validation actuelle

L'extracteur a été exécuté sur le disque fourni et son inventaire comparé au
profil. Les chemins d'échec du lanceur Python sont vérifiés localement.
**Les scripts Java et l'exécution Ghidra complète ne sont pas encore validés** :
Ghidra n'est pas installé dans l'environnement ayant préparé ce dépôt.

Les fichiers du disque, les extractions et les exports Ghidra restent dans les
dossiers locaux ignorés par Git. Ne pas les ajouter avec `git add -f`.
Aucun code provenant du projet PC n'est inclus.
