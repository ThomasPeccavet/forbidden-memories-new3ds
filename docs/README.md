# Documentation

Point d'entrée de la documentation du portage New Nintendo 3DS.

Dernière mise à jour globale : **21 septembre 2026**.

## État courant

- [CURRENT_STATUS.md](CURRENT_STATUS.md) — état réel du backend : menu, nouvelle partie, saisie du nom, première cinématique et problème FPS.
- [ACTION_PLAN.md](ACTION_PLAN.md) — plan actif : profiling, timing, fallback, puis cinématique.
- [ROADMAP.md](ROADMAP.md) — feuille de route globale jusqu'au jeu complet.
- [WORK_HANDOFF.md](WORK_HANDOFF.md) — contexte compact pour reprendre immédiatement.
- [NEW3DS_PROTOTYPE.md](NEW3DS_PROTOTYPE.md) — architecture et build du prototype.
- [ANALYSIS.md](ANALYSIS.md) — constantes et observations de la version française.
- [AUTOMATED_TESTS.md](AUTOMATED_TESTS.md) — contrôles automatisés disponibles.

## Jalon actuel New 3DS

Le backend a dépassé le menu SU :

- logo Konami ;
- écran titre ;
- menu principal visible ;
- navigation / validation ;
- nouvelle partie ;
- saisie et validation du nom ;
- première cinématique / premiers dialogues atteints.

Le verrou prioritaire est maintenant la **performance**, avec seulement quelques
FPS observés. La cinématique atteinte reste également visuellement incorrecte.

## Références historiques PC

- [PC_RUNTIME_BASE.md](PC_RUNTIME_BASE.md)
- [PC_RUNTIME_BUILD.md](PC_RUNTIME_BUILD.md)
- [FIRST_MENU.md](FIRST_MENU.md)
- [FIRST_DUEL.md](FIRST_DUEL.md)

## Analyse Ghidra / SU

- [GHIDRA_FIRST_PASS_REVIEW.md](GHIDRA_FIRST_PASS_REVIEW.md)
- [SU_LOADING_TRACE.md](SU_LOADING_TRACE.md)
- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)

Quand une note historique contredit [CURRENT_STATUS.md](CURRENT_STATUS.md), le
document courant prévaut.
