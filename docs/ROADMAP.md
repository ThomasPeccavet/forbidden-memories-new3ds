# Feuille de route

Objectif final : jeu complet sur New Nintendo 3DS, avec preuves reproductibles à chaque étape. Aucun pourcentage global de portage n'est utilisé.

## 1 — Base française et analyse

- [x] Identifier le disque SLES-03948 et ses empreintes.
- [x] Extraire et analyser le PS-X EXE.
- [x] Exécuter plusieurs passes Ghidra.
- [x] Identifier le chemin de démarrage résident.
- [x] Étudier SU.MRG et plusieurs overlays candidats.
- [x] Valider un runtime PC jusqu'au menu puis au premier duel.

## 2 — Backend natif New 3DS

- [x] Construire une application libctru native.
- [x] Lire le BIN depuis SD et charger le PS-X EXE.
- [x] Initialiser RAM PS1, CPUState et registres.
- [x] Recompiler le code résident en ARM11.
- [x] Lier le dispatcher statique.
- [x] Ajouter un fallback R3000A pour les blocs inconnus.
- [x] Ajouter un HLE BIOS minimal nécessaire au boot.
- [x] Brancher GP0/GP1 et le rasteriseur logiciel.
- [ ] Obtenir la première écriture VRAM réellement produite par le jeu.
- [ ] Afficher cette VRAM sur l'écran supérieur.

## 3 — Interruptions et GPU

- [ ] Implémenter A0:44 `FlushCache` et les prochains appels BIOS simples.
- [ ] Implémenter `I_STAT` / `I_MASK`.
- [ ] Ajouter un VBlank minimal.
- [ ] Fiabiliser DMA2 / linked-list GPU.
- [ ] Valider le display start et le mode vidéo.
- [ ] Atteindre l'écran titre / menu sur Azahar.

## 4 — CD-ROM et overlays

- [ ] Tracer les accès CD-ROM réels du boot 3DS.
- [ ] Implémenter les commandes asynchrones nécessaires.
- [ ] Gérer les IRQ CD.
- [ ] Identifier chaque image overlay chargée à `0x801xxxxx`.
- [ ] Exécuter immédiatement les overlays via R3000A.
- [ ] Recompiler en ARM11 les overlays chauds/stables lorsque cela apporte un gain mesurable.

## 5 — GTE et rendu complet

- [ ] Implémenter les opérations GTE effectivement rencontrées.
- [ ] Valider les scènes 3D et le plateau de duel.
- [ ] Corriger texture window, CLUT, semi-transparence et masking selon les écarts observés.

## 6 — Contrôles et jouabilité

- [ ] Raccorder le pad 3DS au jeu sans conflit avec l'interface de diagnostic.
- [ ] Naviguer dans le menu français.
- [ ] Créer une nouvelle partie.
- [ ] Atteindre Simon Muran.
- [ ] Terminer un duel complet.

## 7 — Audio et sauvegarde

- [ ] SPU.
- [ ] XA.
- [ ] synchronisation audio/vidéo.
- [ ] memory card.
- [ ] sauvegarde / chargement.

## 8 — Validation matériel et optimisation

- [ ] Tester sur New 3DS physique.
- [ ] Mesurer CPU ARM recompilé vs fallback R3000A.
- [ ] Mesurer rasteriseur, mémoire et débit SD.
- [ ] Optimiser uniquement les zones réellement limitantes.
- [ ] Valider campagne, menus, duels, progression et cas particuliers.

## Jalon immédiat

Le jalon actif n'est plus « faire exécuter le CPU » : cela fonctionne déjà. Le jalon actif est désormais :

> **produire puis afficher la première VRAM réellement calculée par Forbidden Memories sur le backend New 3DS.**

Voir [ACTION_PLAN.md](ACTION_PLAN.md) pour l'ordre de travail détaillé.
