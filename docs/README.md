# Documentation

Point d'entrée de la documentation du portage New Nintendo 3DS.

Dernière mise à jour globale : **29 septembre 2026**.

## À lire en premier

- [CURRENT_STATUS.md](CURRENT_STATUS.md) — état réel du backend et verrou actif.
- [B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md) — diagnostic détaillé du blocage startup/CD/SPU/DMA4.
- [ACTION_PLAN.md](ACTION_PLAN.md) — plan actif pour débloquer le startup proprement.
- [ROADMAP.md](ROADMAP.md) — feuille de route globale.
- [WORK_HANDOFF.md](WORK_HANDOFF.md) — résumé compact pour reprendre immédiatement.

## Jalon actuel

Le travail actif n'est plus centré sur le menu invisible ni uniquement sur la
performance. La branche de diagnostic reconstruit désormais le startup fidèle
sans bypass arbitraire.

Le verrou actuel est :

> **un ReadN CD à LBA 0x3172D attend un événement BIOS F0000009/0x20 qui dépend
> de la chaîne SPU / DMA4.**

Les preuves accumulées montrent que :
- le pipeline CD précédent fonctionne ;
- la requête ReadN est construite correctement ;
- TestEvent est appelé correctement ;
- l'événement existe mais n'est pas READY ;
- FUN_80075AFC(3) est bien exécutée ;
- les pointeurs DMA4 sont corrects ;
- la routine bloque avant les stores DMA4 car les registres SPU n'étaient pas modélisés.

Un modèle SPU minimal vient d'être ajouté et attend validation.

## Diagnostics persistants

~~~text
sdmc:/3ds/fm-new3ds/debug-latest.txt
sdmc:/3ds/fm-new3ds/memory-watch.txt
~~~

Les traces TXT sont désormais la référence pour les tests de bring-up.

## Documents historiques utiles

### Runtime PC / jalons fonctionnels
- [PC_RUNTIME_BASE.md](PC_RUNTIME_BASE.md)
- [PC_RUNTIME_BUILD.md](PC_RUNTIME_BUILD.md)
- [FIRST_MENU.md](FIRST_MENU.md)
- [FIRST_DUEL.md](FIRST_DUEL.md)

### Analyse Ghidra / SU
- [GHIDRA_FIRST_PASS_REVIEW.md](GHIDRA_FIRST_PASS_REVIEW.md)
- [SU_LOADING_TRACE.md](SU_LOADING_TRACE.md)
- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)

### Série B135
- [B135.74_PROFILE_CLEAN.md](B135.74_PROFILE_CLEAN.md)
- [B135.75_INTERP_FASTPATH.md](B135.75_INTERP_FASTPATH.md)
- [B135.81_C2_OVERLAY_DIAG.md](B135.81_C2_OVERLAY_DIAG.md)
- [B135.82_C2_ACTIVE.md](B135.82_C2_ACTIVE.md)
- [B135.83_C2_CREATION.md](B135.83_C2_CREATION.md)
- [B135.84_DIALOGUE_LAYER.md](B135.84_DIALOGUE_LAYER.md)
- [B135.85_OBJECT_STATE.md](B135.85_OBJECT_STATE.md)
- [B135.86_TEXT_PATH.md](B135.86_TEXT_PATH.md)
- [B135.87_BLACK_PAGE.md](B135.87_BLACK_PAGE.md)

Quand une note historique contredit [CURRENT_STATUS.md](CURRENT_STATUS.md) ou
[B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md), les documents les
plus récents prévalent.
