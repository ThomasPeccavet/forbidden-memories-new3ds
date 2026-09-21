# Plan d'action — New Nintendo 3DS

Dernière mise à jour : **21 septembre 2026**.

## Objectif actif

Le menu SU est visible et navigable, « Nlle partie » fonctionne, la
saisie/validation du nom fonctionne et le backend atteint la première
cinématique / les premiers dialogues.

L'objectif immédiat est :

> **retrouver une cadence acceptable en identifiant le hotspot réel, puis
> corriger le rendu de la première cinématique.**

## Phase 1 — Mesurer avant de modifier

Créer un profil court et lisible sur une fenêtre stable de plusieurs frames.

Mesurer par frame :

- temps total boucle hôte ;
- temps dispatcher / guest ;
- temps callback VBlank ;
- temps rendu GPU logiciel ;
- temps composition/copie VRAM ;
- temps de présentation 3DS ;
- temps d'attente VBlank ;
- instructions interprétées ;
- appels fallback R3000A ;
- commandes GP0 et primitives dessinées.

Conserver les tops B110 de plages guest par temps cumulé, temps maximum et nombre
d'appels.

### Critère de succès

Attribuer la majorité du coût à une catégorie concrète avant toute nouvelle
optimisation.

## Phase 2 — Vérifier le timing guest

Contrôler :

1. nombre de VBlanks guest par seconde hôte ;
2. appels des callbacks guest par frame ;
3. boucles qui attendent un état CD/DMA/GPU ;
4. bridges qui passent immédiatement un wait au lieu de reproduire sa latence ;
5. fonctions relancées plusieurs fois car un drapeau matériel n'évolue pas comme
   sur PS1.

### Angle d'attaque prioritaire

Rechercher une plage PC avec énormément de hits et peu de progression logique :
une routine qui devrait attendre mais tourne en boucle active expliquerait mieux
quelques FPS qu'une simple conversion framebuffer déjà optimisée.

## Phase 3 — Isoler interpréteur vs code recompilé

Ajouter ou exploiter des compteurs distincts :

- appels vers fonction recompilée ;
- appels fallback ;
- instructions R3000A interprétées ;
- temps cumulé dans l'interpréteur ;
- temps cumulé dans les fonctions ARM générées.

Si quelques fonctions overlay dominent, les identifier par adresse et envisager
leur recompilation ciblée.

## Phase 4 — GPU logiciel et présentation

Ne poursuivre ici que si le profiling l'indique.

Mesurer :

- pixels réellement rasterisés ;
- primitives par frame ;
- coût texture/CLUT ;
- coût composition base + overlay ;
- coût conversion RGB555 ;
- coût flush framebuffer.

Pistes possibles seulement si confirmées : dirty rectangles, moins de copies,
chemins spécialisés, traitement cache-friendly, puis à plus long terme rendu
natif GPU 3DS.

## Phase 5 — Première cinématique

Une fois les FPS maîtrisés, reprendre :

- GP0 E3/E4/E5 draw area/draw offset ;
- GP1 display start ;
- display mode ;
- RGB24 ;
- MDEC input/output ;
- page VRAM affichée ;
- composition des plans.

### Critère de succès

Cinématique lisible et cadrée suffisamment pour poursuivre les dialogues sans
patch visuel spécifique.

## Phase 6 — Premier duel

1. progresser dans les dialogues ;
2. tracer chaque nouvel overlay ;
3. corriger uniquement les nouveaux besoins matériels rencontrés ;
4. atteindre Simon Muran ;
5. afficher le plateau ;
6. jouer un tour complet.

## Phase 7 — Réduire la dette de bring-up

Pour chaque bridge : documenter sa condition, retrouver le comportement PS1,
déplacer la correction dans CD/DMA/GPU/IRQ/timing, puis supprimer le patch
spécifique.

## Discipline de travail

- profiler avant d'optimiser ;
- ne pas transformer un appel inconnu en no-op sans preuve ;
- ne pas réouvrir un problème déjà validé sauf régression ;
- conserver capture/mesure à chaque jalon ;
- comparer avec le runtime PC ;
- ne pas versionner BIN, BIOS Sony, EXE extrait ni shards C propriétaires ;
- garder PSXRecomp sur la révision documentée tant qu'un changement amont n'est
  pas volontairement validé.
