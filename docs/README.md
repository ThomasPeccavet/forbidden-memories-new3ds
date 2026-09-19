# Documentation

Point d'entrée de la documentation du portage New Nintendo 3DS.

## État courant

- [CURRENT_STATUS.md](CURRENT_STATUS.md) — résultat réel du backend 3DS au 19 septembre 2026.
- [ACTION_PLAN.md](ACTION_PLAN.md) — instrumentation et prochaines étapes vers le menu visible.
- [WORK_HANDOFF.md](WORK_HANDOFF.md) — contexte compact pour reprendre immédiatement le chantier.
- [NEW3DS_PROTOTYPE.md](NEW3DS_PROTOTYPE.md) — architecture et build du prototype.
- [ROADMAP.md](ROADMAP.md) — feuille de route globale.
- [ANALYSIS.md](ANALYSIS.md) — constantes et observations de la version française.

## Jalons actuels New 3DS

Le backend a désormais affiché le logo Konami et l'écran titre. START fonctionne,
`SU.mrg` est chargé et la logique du menu SU s'exécute. Le problème actif est
le rendu visible de ce menu, malgré des objets valides et un callback draw actif.

## Références historiques PC

Ces documents restent des preuves utiles, mais ne décrivent pas l'état du backend
3DS actuel :

- [PC_RUNTIME_BASE.md](PC_RUNTIME_BASE.md)
- [PC_RUNTIME_BUILD.md](PC_RUNTIME_BUILD.md)
- [FIRST_MENU.md](FIRST_MENU.md)
- [FIRST_DUEL.md](FIRST_DUEL.md)

## Analyse Ghidra / SU

- [GHIDRA_FIRST_PASS_REVIEW.md](GHIDRA_FIRST_PASS_REVIEW.md)
- [SU_LOADING_TRACE.md](SU_LOADING_TRACE.md)
- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)

Quand une note historique contredit `CURRENT_STATUS.md`, le document courant
prévaut.
