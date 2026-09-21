# Feuille de route

Objectif final : **Yu-Gi-Oh! Forbidden Memories PAL France jouable de bout en
bout sur New Nintendo 3DS**, avec un chemin reproductible et de moins en moins
dépendant des bridges de bring-up.

Dernière mise à jour : **21 septembre 2026**.

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
- [x] Logo Konami.
- [x] Écran titre.

## 3 — Kernel / CD / GPU du chemin courant

- [x] Pad START transmis au guest.
- [x] VBlank / IRQ suffisants pour atteindre le menu.
- [x] Lectures CD suffisantes pour les overlays rencontrés.
- [x] File CD async suffisante pour le chemin observé.
- [x] DMA2 / waits GPU bridgés pour le chemin observé.
- [x] Helpers GTE nécessaires au chemin courant.
- [ ] Remplacer les bridges de bring-up par des modèles généraux.

## 4 — Overlay SU et menu principal

- [x] Charger SU.mrg.
- [x] Exécuter init/update/draw.
- [x] Créer les objets du menu.
- [x] Débloquer l'animation d'entrée.
- [x] Afficher le menu français.
- [x] Naviguer dans le menu.
- [x] Valider une entrée.

## 5 — Nouvelle partie / introduction

- [x] Lancer « Nlle partie ».
- [x] Afficher la saisie du nom.
- [x] Saisir le nom.
- [x] Valider le nom.
- [x] Atteindre la première cinématique.
- [x] Atteindre les premiers dialogues.
- [ ] Corriger le rendu de la première cinématique.
- [ ] Stabiliser les transitions suivantes.
- [ ] Atteindre Simon Muran sur le backend 3DS.

## 6 — Performance — priorité actuelle

- [x] Compiler le runtime 3DS en -O3.
- [x] Recompiler les shards générés en release.
- [x] Optimiser la conversion RGB555.
- [x] Éviter le clear complet à chaque frame.
- [x] Limiter le flush/swap au top screen.
- [x] Ajouter des mesures de temps de frame.
- [x] Ajouter un profiler de plages guest.
- [ ] Mesurer précisément interpréteur vs code ARM recompilé.
- [ ] Identifier le hotspot dominant.
- [ ] Vérifier les boucles d'attente/bypass CD-DMA-GPU.
- [ ] Vérifier le ratio frame guest / VBlank hôte.
- [ ] Ramener le chemin menu → cinématique à une cadence acceptable.
- [ ] Tester ensuite sur New 3DS physique.

## 7 — Premier duel 3DS

- [ ] Atteindre Simon Muran.
- [ ] Afficher le plateau.
- [ ] Afficher la main.
- [ ] Jouer une carte.
- [ ] Terminer un tour complet.
- [ ] Comparer avec le runtime PC.

## 8 — Fidélité matérielle

- [ ] CD-ROM async général.
- [ ] DMA GPU général.
- [ ] IRQ/timers propres.
- [ ] GTE complet selon les besoins rencontrés.
- [ ] MDEC / RGB24 / cinématiques fidèles.
- [ ] Texture window / CLUT / semi-transparence / masking validés.
- [ ] Suppression progressive des bridges temporaires.

## 9 — Audio et sauvegarde

- [ ] SPU.
- [ ] XA.
- [ ] Synchronisation audio/vidéo.
- [ ] Memory card.
- [ ] Sauvegarde / chargement.

## 10 — Validation complète

- [ ] Test New 3DS physique.
- [ ] Profiling ARM11 final.
- [ ] Campagne complète.
- [ ] Menus / duels / progression validés.
- [ ] Robustesse des changements d'overlay.
- [ ] Nettoyage des diagnostics de bring-up.

## Jalon immédiat

> **Identifier la cause principale des quelques FPS actuels, la corriger, puis
> reprendre le rendu de la première cinématique.**

Voir [ACTION_PLAN.md](ACTION_PLAN.md).
