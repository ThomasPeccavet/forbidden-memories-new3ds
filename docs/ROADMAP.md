# Feuille de route

Objectif final : **Yu-Gi-Oh! Forbidden Memories PAL France jouable de bout en
bout sur New Nintendo 3DS**, avec un chemin reproductible et progressivement
moins dépendant des bridges de bring-up.

Dernière mise à jour : **29 septembre 2026**.

## 1 — Base française et analyse

- [x] Identifier SLES-03948 et ses empreintes.
- [x] Extraire/analyser le PS-X EXE.
- [x] Export Ghidra massif.
- [x] Étudier code résident et overlays.
- [x] Valider le runtime PC jusqu'au premier duel.

## 2 — Backend natif New 3DS

- [x] Application libctru.
- [x] Lecture BIN depuis SD.
- [x] RAM PS1 / CPUState.
- [x] Code résident recompilé ARM11.
- [x] Dispatcher hybride.
- [x] Fallback R3000A.
- [x] HLE BIOS de bring-up.
- [x] GP0/GP1 + rasteriseur logiciel.
- [x] DMA2 GPU.
- [x] DMA6 OTC.

## 3 — Startup fidèle — priorité actuelle

- [x] Restaurer la détection PAL BIOS BFC7FF52 = 0x45.
- [x] Passer l'overlay 801680F4/80168160.
- [x] Identifier le blocage dans le second FUN_80043CD4.
- [x] Identifier la requête ReadN 0x2000 / LBA 0x3172D.
- [x] Prouver le pipeline CD précédent sain.
- [x] Identifier FUN_800142F8 comme réarmement de la requête.
- [x] Identifier FUN_800777D8 / TestEvent comme gate.
- [x] Identifier l'événement F0000009 / 0x20.
- [x] Identifier la dépendance SPU / DMA4.
- [x] Ajouter un modèle DMA4 minimal.
- [x] Identifier le wait SPU qui empêche DMA4 de démarrer.
- [x] Ajouter un modèle SPU minimal de synchronisation.
- [ ] Valider le nouveau modèle SPU.
- [ ] Observer le premier DMA4 réel.
- [ ] Livrer l'événement BIOS via completion DMA4.
- [ ] Relancer le ReadN à LBA 0x3172D.
- [ ] Sortir du second FUN_80043CD4.
- [ ] Revenir au chemin SU sans bypass arbitraire.

## 4 — Overlay SU / menu

- [x] Charger SU.mrg.
- [x] Exécuter le menu.
- [x] Afficher le menu français dans les branches fonctionnelles.
- [x] Naviguer.
- [x] Valider.
- [ ] Revalider tout le chemin après nettoyage startup.

## 5 — Nouvelle partie / progression

- [x] Nouvelle partie atteinte historiquement.
- [x] Saisie du nom atteinte.
- [x] Nom saisi/validé.
- [x] Dialogues atteints.
- [x] Carte atteinte.
- [x] Duel atteint et tours joués dans les branches précédentes.
- [ ] Revalider ces jalons sur la chaîne startup corrigée.

## 6 — Matériel PS1

- [x] VBlank minimal.
- [x] événements BIOS de base.
- [x] CD sector read.
- [x] DMA2/DMA6.
- [x] DMA4 minimal.
- [x] SPU contrôle minimal.
- [ ] IRQ DMA générales.
- [ ] timers complets.
- [ ] CD async général sans bridges.
- [ ] SPU RAM / voix / mixer.
- [ ] XA.
- [ ] GTE complet selon besoins.
- [ ] MDEC / RGB24.
- [ ] suppression progressive des bridges temporaires.

## 7 — Performance

- [x] build -O3 / release.
- [x] shards générés en release.
- [x] instrumentation VSync / frame.
- [x] profiling de plages guest.
- [x] plusieurs optimisations GPU/present.
- [ ] reprendre le profiling après startup stable.
- [ ] réduire fallback/interpréteur sur hotspots.
- [ ] atteindre une cadence confortable.
- [ ] valider sur New 3DS physique.

## 8 — Fidélité visuelle

- [ ] cinématiques fidèles.
- [ ] draw area / draw offset.
- [ ] display start/mode.
- [ ] RGB24/MDEC.
- [ ] texture window / CLUT.
- [ ] semi-transparence / masking.
- [ ] cohérence des assets/cartes.

## 9 — Sauvegarde

- [ ] memory card.
- [ ] sauvegarde.
- [ ] chargement.
- [ ] compatibilité de progression.

## 10 — Validation complète

- [ ] campagne complète.
- [ ] menus / duels / progression.
- [ ] changements d'overlay robustes.
- [ ] audio.
- [ ] performance ARM11.
- [ ] nettoyage diagnostics.
- [ ] build utilisateur reproductible.

## Jalon immédiat

> **Valider que le nouveau modèle SPU libère FUN_80075AFC(3), déclenche DMA4,
> rend READY l'événement BIOS et permet au ReadN 0x3172D de progresser.**

Voir [B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).
