# Plan d'action — New Nintendo 3DS

Objectif : obtenir le **premier écran réellement produit par Forbidden Memories sur New 3DS/Azahar**, puis poursuivre jusqu'au menu et au premier duel.

Le plan est volontairement ordonné par dépendances. Éviter de travailler sur l'audio, les sauvegardes ou l'optimisation tant que le boot graphique n'est pas stable.

## Phase 0 — Stabiliser le boot actuel

### 0.1 Implémenter A0:44 `FlushCache`

Critère de succès : le boot ne s'arrête plus sur `PC=0xA0 / T1=0x44` et revient à `$ra` sans altérer les registres guest non concernés.

### 0.2 Journaliser les prochains appels BIOS inconnus

Ajouter un diagnostic compact : vecteur A0/B0/C0, numéro, A0-A3, RA, PC avant/après.

Critère de succès : chaque nouvel arrêt BIOS est identifiable sans modifier manuellement plusieurs fichiers.

## Phase 1 — Interruptions PS1 minimales

### 1.1 I_STAT / I_MASK

Implémenter au minimum :

- `0x1F801070` I_STAT ;
- `0x1F801074` I_MASK ;
- lectures/écritures 16 et 32 bits cohérentes ;
- acquittement des bits I_STAT selon la sémantique PS1.

Critère de succès : `Last MMIO` ne reste plus bloqué sur `1F801074` et les boucles d'attente IRQ progressent.

### 1.2 VBlank minimal

Lever périodiquement l'IRQ VBlank dans I_STAT en fonction de la boucle 3DS/Azahar.

Critère de succès : les fonctions de synchronisation ne tournent plus indéfiniment en attente d'une interruption verticale.

### 1.3 Respecter I_MASK

Une IRQ ne doit devenir visible au CPU que si son bit est autorisé.

Critère de succès : pas de déclenchement permanent ni d'IRQ storm.

## Phase 2 — GPU jusqu'à la première VRAM réelle

### 2.1 Instrumenter GP0

Compteurs séparés :

- mots GP0 ;
- commandes environnement E1-E6 ;
- fill ;
- triangles ;
- rectangles/sprites ;
- CPU→VRAM ;
- VRAM→VRAM ;
- linked-list DMA ;
- commandes inconnues.

Critère de succès : savoir exactement pourquoi `Frame VRAM` reste NON.

### 2.2 DMA2 GPU

Implémenter les registres DMA nécessaires, en priorité channel 2 : MADR, BCR, CHCR et linked-list GPU.

Le wrapper BIOS `A0:4B` est déjà utile, mais le jeu peut programmer le DMA directement via MMIO.

Critère de succès : une linked-list guest envoyée par DMA arrive réellement dans `fm_gpu_gp0_write`.

### 2.3 Première écriture VRAM

Critère de succès : `fm_gpu_has_frame()` devient vrai suite au code du jeu, pas suite à une primitive de démonstration.

### 2.4 Présentation écran supérieur

Présenter la zone VRAM définie par GP1 display start et le mode vidéo courant.

Critère de succès : premier écran, même partiel/corrompu, provenant de Forbidden Memories.

## Phase 3 — CD-ROM et chargement dynamique

### 3.1 Identifier le premier besoin CD après le boot

Tracer les accès MMIO CD-ROM `0x1F801800..803` et les appels BIOS associés.

### 3.2 Contrôleur CD minimal

Implémenter uniquement les commandes réellement nécessaires au démarrage : status, Setloc, ReadN/ReadS, Getloc, Pause/Stop selon la trace.

### 3.3 IRQ CD et secteurs Form1/Form2

Réutiliser le lecteur BIN existant et étendre au besoin vers Form2/XA sans charger tout le disque en RAM.

Critère de succès : le jeu charge ses données sans dépendre d'un stub permanent.

## Phase 4 — Overlays dynamiques

### 4.1 Détecter les écritures de code vers `0x801xxxxx`

Journaliser l'adresse, taille, source disque et SHA-256 de chaque image chargée.

### 4.2 Fallback R3000A comme filet de sécurité

Le code dynamique doit pouvoir démarrer immédiatement via l'interpréteur avant toute recompilation dédiée.

### 4.3 Recompilation optionnelle des overlays chauds

Une fois les images identifiées de manière stable, générer des objets ARM distincts par overlay et sélectionner la bonne version selon le contenu RAM.

Critère de succès : ne jamais confondre deux images occupant la même adresse PS1 à des moments différents.

## Phase 5 — GTE

Commencer uniquement lorsqu'un arrêt `FM_INTERP_GTE` ou `FM_STOP_GTE` empêche le boot/rendu.

Réutiliser autant que possible la sémantique du runtime PSXRecomp au lieu de créer des approximations silencieuses.

Critère de succès : géométrie de menu/duel cohérente et pas seulement absence de crash.

## Phase 6 — Entrées et menu

Raccorder les boutons 3DS au pad PS1 du jeu, sans conflit avec l'interface de diagnostic.

Critère de succès : écran titre puis menu français navigable dans Azahar.

## Phase 7 — Audio et sauvegarde

Après obtention du menu et d'un duel visuel :

- SPU ;
- XA ;
- synchronisation audio ;
- memory card ;
- sauvegarde/chargement.

## Phase 8 — Performance New 3DS

Mesurer sur matériel physique :

- temps ARM recompilé ;
- temps interpréteur ;
- temps rasteriseur ;
- mémoire ;
- débit CD ;
- frame pacing.

Optimiser seulement les zones mesurées comme réellement coûteuses.

## Priorité Work immédiate

Pour une session autonome ChatGPT Work, suivre cet ordre :

1. lire `docs/WORK_HANDOFF.md` et `docs/CURRENT_STATUS.md` ;
2. inspecter les sources 3DS actuelles ;
3. implémenter et tester A0:44 ;
4. implémenter I_STAT/I_MASK ;
5. instrumenter le GPU ;
6. implémenter DMA2 si la trace le demande ;
7. obtenir `Frame VRAM = OUI` ;
8. afficher cette VRAM sur l'écran supérieur ;
9. commit/push après chaque jalon reproductible.

## Règles de travail

- ne pas ajouter des seeds une par une si le fallback R3000A peut continuer ;
- ne pas stubber silencieusement GTE/CD/IRQ avec des valeurs arbitraires ;
- conserver un diagnostic précis à chaque arrêt ;
- ne jamais committer BIN, BIOS Sony, EXE extrait, dumps RAM ou C généré du jeu ;
- garder PSXRecomp épinglé à la révision documentée tant qu'un changement amont n'est pas volontairement validé.
