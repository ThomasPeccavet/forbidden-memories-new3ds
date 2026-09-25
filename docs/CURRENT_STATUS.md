# État courant — New Nintendo 3DS

Dernière mise à jour : **25 septembre 2026**.

## Résumé

Le port 3DS a franchi le menu, la nouvelle partie, la carte et le premier duel.
La lignée **B135.71** permet d'afficher la main, jouer plusieurs tours et laisser
l'adversaire jouer. Le rendu 3D du duel est fonctionnel.

Deux problèmes restent séparés :

1. **duel lent** : typiquement ~12–15 FPS et ~4 FPS lors de certaines attaques ;
2. **dialogues 2D absents** : les objets existent mais leur renderer C2 ne tourne pas.

## Baseline fonctionnelle

B135.71 reste l'oracle du duel. Ses correctifs B135.64/B135.66/B135.71 doivent
être conservés tant que leur cause native n'a pas été reconstruite.

Le gate `DAT_8009C4B8` est forcé uniquement dans la condition documentée où
une main valide attend sa soumission.

## Performance : résultats récents

### B135.74 — PROFILE / CLEAN

Le CLEAN compile hors du chemin chaud plusieurs familles de diagnostics :
timers GP0, compteurs pixel, scans DMA et gros blocs console.

**Résultat de test : aucune amélioration FPS observable.**

### B135.75 — Interpreter Fast Path

- chunks interpréteur : 256 → 2048 ;
- limite externe : 256 → 32 ;
- plafond total inchangé : 65536 instructions ;
- accès RAM 16/32 bits simplifiés ;
- écriture redondante de `gpr[0]` supprimée.

**Résultat de test : pas d'amélioration visible.**

Conclusion : ne pas continuer les micro-optimisations de ce type sans nouvelle
mesure du budget dominant.

## Dialogues : localisation du défaut

### B135.76

Correction de plusieurs erreurs du presenter :

- B135.44 lisait des champs draw-area jamais remplis par
  `fm_gpu_b127_perf_snapshot()` ;
- prise en compte de Y=256 ;
- échantillonnage de la page Y courante.

### B135.77

Tentative de priorité systématique à la draw-area E3/E4.

**Résultat : régression écran noir.** La draw-page pouvait être le backbuffer en
construction et ne devait pas être assimilée au frontbuffer.

### B135.78

GP1 redevient autoritaire sur un vrai changement d'affichage. Le suivi de la
draw-page n'est utilisé que dans un cas stale-GP1 conservateur.

Capture importante sur le premier villageois :

```text
PRES g:0,0 l:0,0 d:0,0 p:0 nz:0/0
```

La bonne page est choisie mais elle ne contient pas le dialogue. Le presenter
n'est donc plus le suspect principal.

### B135.79

Instrumentation de la chaîne objets → walker → primitives GPU.

Observation :

```text
OBJ79 n:0/5/0/0/0/0/0
WALK79 ... 408bc:0 ...
GP2D79 rect/q/2c/3a:0/0/0/0
```

Interprétation : la liste C2 contient **5 objets**, mais
`FUN_800408BC`, qui parcourt précisément `DAT_800F11C2`, n'est pas exécuté.
Aucune primitive 2D correspondante n'atteint ensuite le GPU.

### B135.80 — en attente de test

B135.80 affiche :

- la table de renderers `0x800923DC..0x800923F4` ;
- la case C2 `0x800923E0` ;
- l'adresse attendue `800408BC` ;
- si `800408BC` est une entrée reconnue du dispatcher ;
- le nombre d'entrées dans `FUN_80041674`.

Le prochain test doit séparer :

- table C2 incorrecte ;
- entrée 408BC absente du dispatcher ;
- appel indirect/JALR cassé.

## Problèmes encore ouverts

- dialogue/personnage avant duel non rendu ;
- dialogue après duel non rendu ;
- images de cartes parfois associées aux mauvais noms/stats ;
- duel trop lent ;
- dette de bridges CD/DMA/GPU/IRQ ;
- audio ;
- sauvegarde memory card ;
- validation New 3DS physique.

## Ce qui ne doit plus être réinvestigué sans nouvelle preuve

- menu SU invisible ;
- simple sélection de page framebuffer comme cause du dialogue noir ;
- probes de debug comme cause principale des 12–15 FPS ;
- augmentation simple de la taille des chunks interpréteur comme solution FPS.

Le runtime PC reste l'oracle fonctionnel pour les scènes attendues.
