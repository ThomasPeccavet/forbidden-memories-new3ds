# Feuille de route

Objectif final : jeu complet sur New Nintendo 3DS, avec preuves reproductibles à
chaque étape.

## 1 — Base française et analyse

- [x] Identifier SLES-03948 et ses empreintes.
- [x] Extraire et analyser le PS-X EXE.
- [x] Exécuter plusieurs passes Ghidra.
- [x] Étudier le chemin résident.
- [x] Étudier SU.MRG et plusieurs overlays.
- [x] Valider le runtime PC jusqu'au premier duel.

## 2 — Backend natif New 3DS

- [x] Application libctru native.
- [x] Lecture BIN depuis SD.
- [x] RAM PS1 / CPUState.
- [x] Code résident recompilé ARM11.
- [x] Dispatcher statique.
- [x] Fallback R3000A.
- [x] HLE BIOS nécessaire au boot.
- [x] GP0/GP1 + rasteriseur logiciel.
- [x] Première VRAM réellement produite par le jeu.
- [x] Première image réelle affichée : logo Konami.
- [x] Écran titre affiché.

## 3 — Kernel / CD / GPU nécessaires au chemin actuel

- [x] Pad START transmis au guest.
- [x] VBlank / IRQ suffisants pour atteindre le titre.
- [x] Lectures CD suffisantes pour atteindre SU.
- [x] File CD async suffisante pour le chemin observé.
- [x] DMA2 / waits GPU bridgés pour le boot observé.
- [x] Helpers GTE nécessaires au boot observé.
- [ ] Remplacer les bridges de bring-up par des modèles généraux.

## 4 — Overlay SU et menu principal

- [x] Atteindre l'état résident 8.
- [x] Charger `SU.mrg`.
- [x] Exécuter `0x8018001C`.
- [x] Exécuter `0x80180390`.
- [x] Installer / appeler le callback draw `0x80180B4C`.
- [x] Créer les 11 objets de menu.
- [x] Débloquer leur animation d'entrée.
- [ ] Comprendre pourquoi ils ne sont pas encore visibles.
- [ ] Afficher le menu français.
- [ ] Naviguer Haut/Bas.
- [ ] Valider une entrée.

## 5 — Nouvelle partie et premier duel

- [ ] Lancer « Nlle partie ».
- [ ] Charger les overlays suivants.
- [ ] Parcourir l'introduction.
- [ ] Atteindre Simon Muran.
- [ ] Afficher le plateau.
- [ ] Jouer un tour complet.

## 6 — Fidélité matérielle

- [ ] CD-ROM async général.
- [ ] DMA GPU général.
- [ ] IRQ/timers propres.
- [ ] GTE complet selon les besoins rencontrés.
- [ ] Texture window / CLUT / semi-transparence / masking validés.
- [ ] Suppression progressive des bridges temporaires.

## 7 — Audio et sauvegarde

- [ ] SPU.
- [ ] XA.
- [ ] synchronisation audio/vidéo.
- [ ] memory card.
- [ ] sauvegarde / chargement.

## 8 — Matériel et optimisation

- [ ] Test New 3DS physique.
- [ ] Profiling ARM11 / fallback / rasteriseur.
- [ ] Optimisation.
- [ ] Validation campagne / menus / duels / progression.

## Jalon immédiat

> **Afficher le menu SU déjà actif en mémoire et dans la boucle de rendu.**

Voir [ACTION_PLAN.md](ACTION_PLAN.md) pour l'instrumentation suivante.
