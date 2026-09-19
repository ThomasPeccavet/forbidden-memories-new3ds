# Plan d'action — New Nintendo 3DS

Objectif actif : obtenir le **menu principal français visible et navigable** sur
Azahar à partir du vrai overlay SU.

Les anciens objectifs « première VRAM » et « premier écran réel » sont atteints :
le logo Konami et l'écran titre sont déjà rendus.

## Phase 1 — Isoler le défaut de rendu du menu SU

### 1.1 Mesurer le coût GP0 par étape de frame

Instrumenter :

- entrée/sortie de `FUN_80041674` ;
- entrée/sortie du callback `0x80180B4C` ;
- compteur GP0 avant/après chaque étape.

Critère de succès : déterminer qui émet réellement les primitives du menu.

### 1.2 Inspecter les listes du renderer

Le menu crée ses objets via `FUN_800403D0(..., 2)`, donc ils sont associés au
layer/type 2.

Tracer :

- `DAT_800F11C0[]` / `DAT_800F11D0[]` ;
- chaîne next/prev des objets ;
- présence des pointeurs `DAT_80184794 .. DAT_801847BC` ;
- flags `+0x08`, position `+0x30`, type `+0x1E`, callback/données utiles.

Critère de succès : prouver que les objets SU sont réellement vus par le renderer
global.

### 1.3 Tracer les dernières primitives GPU

Utiliser la trace B29/B38 existante pour conserver plusieurs commandes récentes :

- opcode ;
- coordonnées ;
- texpage ;
- CLUT ;
- draw offset ;
- draw area.

Critère de succès : identifier des primitives correspondant au menu à
`x ~= 160`, ou prouver qu'elles n'atteignent jamais GP0.

### 1.4 Départager les scénarios

- **pas de GP0 menu** → réparer le parcours/layer/callback objet ;
- **GP0 menu présent mais hors écran** → corriger coords / draw offset / display page ;
- **GP0 menu présent mais transparent/noir** → inspecter texture / CLUT / flags ;
- **GP0 menu présent puis recouvert** → identifier et désactiver/retirer les objets titre obsolètes.

## Phase 2 — Menu visible et navigable

Une fois le menu visible :

1. valider Haut/Bas ;
2. valider la sélection ;
3. valider Croix / Rond ;
4. comparer le comportement avec le runtime PC ;
5. supprimer ou réduire les bridges B70/B71/B73/B75 si la cause racine est comprise.

Critère de succès :

> menu français visible, sélection déplaçable et validation fonctionnelle.

## Phase 3 — Nouvelle partie

Sélectionner « Nlle partie » et tracer :

- transition d'état ;
- nouvel overlay chargé ;
- nouveaux besoins CD ;
- nouvelles instructions GTE ;
- nouveaux besoins GPU/DMA.

Critère de succès : quitter proprement le menu SU sans patch manuel d'adresse.

## Phase 4 — Premier duel

Utiliser le runtime PC comme oracle fonctionnel et avancer jusqu'à Simon Muran.

Critères :

- introduction franchie ;
- plateau visible ;
- main de cartes visible ;
- entrée utilisateur fonctionnelle ;
- un tour complet exécutable.

## Phase 5 — Remplacer les bridges de bring-up

Les bridges actuels ont permis d'identifier les attentes réelles, mais ne doivent
pas devenir l'architecture finale.

À généraliser :

- completion CD async ;
- DMA2 ;
- synchronization GPU ;
- GTE helpers ;
- état / overlays ;
- timing d'animation.

Pour chaque bridge : documenter la condition qui le déclenche, retrouver la
sémantique PS1 originale, puis déplacer la correction dans le composant matériel
ou runtime approprié.

## Phase 6 — Audio, sauvegarde et performance

Après un premier duel visuel :

- SPU ;
- XA ;
- memory card ;
- sauvegarde/chargement ;
- tests New 3DS physique ;
- profiling ARM11/interpréteur/rasteriseur ;
- optimisation des seuls hotspots mesurés.

## Discipline de travail

- conserver des diagnostics courts et reproductibles ;
- ne pas transformer un appel inconnu en no-op sans preuve ;
- comparer chaque gros jalon avec le runtime PC ;
- ne pas versionner le BIN, le BIOS Sony, l'EXE extrait ni les shards C générés ;
- garder PSXRecomp sur la révision documentée tant qu'un changement amont n'est
  pas volontairement validé.
