# Feuille de route

Objectif final : **Yu-Gi-Oh! Forbidden Memories PAL France jouable de bout en
bout sur New Nintendo 3DS**, avec un backend reproductible et de moins en moins
dépendant des bridges de bring-up.

Dernière mise à jour : **25 septembre 2026**.

## 1 — Base française et analyse

- [x] Identifier SLES-03948.
- [x] Extraire/analyser le PS-X EXE.
- [x] Passes Ghidra françaises.
- [x] Étude résident + overlays.
- [x] Runtime PC jusqu'au premier duel.

## 2 — Backend natif New 3DS

- [x] libctru / ARM11.
- [x] lecture BIN MODE2/2352.
- [x] RAM PS1 / CPUState.
- [x] code résident recompilé.
- [x] dispatcher statique.
- [x] fallback R3000A.
- [x] HLE BIOS nécessaire au chemin courant.
- [x] GP0/GP1 + rasteriseur logiciel.

## 3 — Menu / nouvelle partie / carte

- [x] logo Konami.
- [x] écran titre.
- [x] SU.mrg.
- [x] menu français.
- [x] navigation.
- [x] nouvelle partie.
- [x] saisie/validation du nom.
- [x] carte et choix d'adversaire.

## 4 — Premier duel 3DS

- [x] entrer dans un duel.
- [x] afficher la main.
- [x] jouer plusieurs tours.
- [x] tour adverse.
- [x] rendu 3D du duel.
- [ ] corriger les images de cartes.
- [ ] stabiliser toutes les transitions pré/post duel.
- [ ] rendre les dialogues 2D visibles.

## 5 — Chaîne dialogue 2D — priorité actuelle

- [x] éliminer la sélection framebuffer comme cause principale.
- [x] prouver que la liste C2 contient des objets.
- [x] identifier `FUN_800408BC` comme renderer de C2.
- [x] prouver qu'il n'est pas exécuté dans l'écran noir.
- [x] instrumenter la table `0x800923DC..F4`.
- [ ] tester B135.80.
- [ ] corriger table / dispatcher / indirect call selon résultat.
- [ ] valider dialogue avant et après duel.

## 6 — Performance

- [x] -O3 / release.
- [x] PROFILE/CLEAN séparés.
- [x] B135.74 : diagnostics compilés hors CLEAN.
- [x] conclure que B135.74 n'améliore pas les FPS.
- [x] B135.75 : fast path interpréteur.
- [x] conclure que B135.75 n'améliore pas visiblement les FPS.
- [ ] profiler le budget réel duel.
- [ ] identifier le hotspot dominant.
- [ ] viser une cadence exploitable.
- [ ] tester New 3DS physique.

## 7 — Fidélité matérielle

- [ ] CD async général.
- [ ] DMA GPU général.
- [ ] IRQ/timers propres.
- [ ] GTE complet selon besoins.
- [ ] MDEC/RGB24.
- [ ] texture window / CLUT / semi-transparence / masking validés.
- [ ] suppression progressive des bridges.

## 8 — Audio / sauvegarde

- [ ] SPU.
- [ ] XA.
- [ ] synchronisation audio/vidéo.
- [ ] memory card.
- [ ] sauvegarde/chargement.

## 9 — Validation complète

- [ ] campagne complète.
- [ ] menus/duels/progression.
- [ ] robustesse overlays.
- [ ] profiling ARM11 final.
- [ ] nettoyage diagnostics.
- [ ] test New 3DS physique.

## Jalon immédiat

> **Tester B135.80 et restaurer le renderer C2 du dialogue.**
