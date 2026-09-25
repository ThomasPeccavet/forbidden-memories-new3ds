# Documentation

Point d'entrée de la documentation du portage New Nintendo 3DS.

Dernière mise à jour globale : **25 septembre 2026**.

## À lire en premier

- [CURRENT_STATUS.md](CURRENT_STATUS.md) — état réel du backend au jalon B135.80.
- [ACTION_PLAN.md](ACTION_PLAN.md) — plan actif : restaurer le renderer C2, puis reprendre les performances.
- [ROADMAP.md](ROADMAP.md) — feuille de route globale.
- [WORK_HANDOFF.md](WORK_HANDOFF.md) — contexte compact pour reprendre sans historique de chat.
- [B135.76_80_RENDER_PIPELINE.md](B135.76_80_RENDER_PIPELINE.md) — enquête actuelle sur les dialogues 2D.
- [NEW3DS_PROTOTYPE.md](NEW3DS_PROTOTYPE.md) — architecture du prototype.
- [ANALYSIS.md](ANALYSIS.md) — observations françaises consolidées.
- [AUTOMATED_TESTS.md](AUTOMATED_TESTS.md) — CI et tests de régression.

## Jalon actuel

Le backend New 3DS sait désormais aller beaucoup plus loin que le menu :

- nouvelle partie et nom ;
- carte / sélection d'adversaire ;
- premier duel ;
- main visible ;
- plusieurs tours jouables ;
- tour adverse fonctionnel.

La baseline duel B135.71 reste lente (~12–15 FPS, chute ~4 FPS en attaque) mais
fonctionnelle.

Le verrou immédiat est distinct : les dialogues 2D autour des combats ne sont
plus rendus. B135.79 a prouvé que 5 objets existent dans la liste C2 mais que le
renderer attendu `FUN_800408BC` n'est jamais appelé. B135.80 instrumente
désormais la table de pointeurs utilisée par `FUN_80041674`.

## Notes de performance

- B135.74 CLEAN : aucun gain mesurable.
- B135.75 Interpreter Fast Path : aucun gain visible.
- Ne plus supposer que les probes ou le chunking de l'interpréteur expliquent
  seuls la lenteur du duel.

## Références historiques

- [FIRST_MENU.md](FIRST_MENU.md)
- [FIRST_DUEL.md](FIRST_DUEL.md)
- [PC_RUNTIME_BASE.md](PC_RUNTIME_BASE.md)
- [PC_RUNTIME_BUILD.md](PC_RUNTIME_BUILD.md)
- [GHIDRA_FIRST_PASS_REVIEW.md](GHIDRA_FIRST_PASS_REVIEW.md)
- [SU_LOADING_TRACE.md](SU_LOADING_TRACE.md)
- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)

Les notes historiques restent volontairement conservées. Si elles contredisent
[CURRENT_STATUS.md](CURRENT_STATUS.md), l'état courant prévaut.
