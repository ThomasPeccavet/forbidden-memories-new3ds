# Feuille de route

L'objectif reste le jeu intégral sur New 3DS. Chaque étape doit produire des
preuves vérifiables ; aucun pourcentage global de portage n'est estimé.

## 1 — Base reproductible

- [x] Identifier le disque français et extraire son exécutable.
- [x] Consigner les adresses de démarrage et empreintes.
- [x] Préparer le lanceur et les scripts Ghidra.
- [ ] Exécuter Ghidra et vérifier le journal, les fonctions et le pseudo-C.
- [ ] Identifier le chemin d'initialisation et les dépendances PS1.

## 2 — Comprendre le chargement du jeu

- [ ] Documenter les archives et éventuels overlays.
- [ ] Cartographier appels BIOS, accès GPU/GTE, audio, CD-ROM et manettes.
- [ ] Comparer des fonctions françaises avec les analyses américaines.
- [ ] Définir le runtime de portage et ses contraintes de licence.

## 3 — Premier démarrage natif New 3DS

- [ ] Mettre en place la compilation ARM et une application de diagnostic.
- [ ] Adapter le chemin de démarrage jusqu'à l'écran titre.
- [ ] Mesurer les performances et la mémoire sur console.

## 4 — Couverture complète

- [ ] Menus, collection, construction des decks et mots de passe.
- [ ] Duels, fusions, IA, récompenses et progression.
- [ ] Graphismes de combat 3D, animations, vidéos, musiques et effets sonores.
- [ ] Sauvegardes, chargement, échanges et modes à plusieurs du jeu original.
- [ ] Campagne complète, transitions et cas particuliers.

Critère de fin : couverture fonctionnelle documentée et comparée au jeu PS1,
avec campagne et modes validés sur New 3DS. Les limites matérielles éventuelles
seront exposées avant toute modification du périmètre.
