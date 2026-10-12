# B136.32 — profiler les performances globales

## Validation précédente

L'utilisateur confirme une attente d'environ 15 secondes entre la fin de
l'intro et le début du jeu avec B136.31. Le chemin est désormais suffisamment
fonctionnel pour mesurer les performances globales (10 FPS ou moins ressentis).
Le log intro montre 3492 ISR servies, aucun refus par les gardes du séquenceur,
et un maximum ISR de 14 ms. Ce maximum seul ne donne pas la charge audio moyenne.

## Mesures nouvelles

`perf-latest.txt` est réécrit toutes les deux secondes de temps réel, uniquement
en PROFILE. L'écran inférieur reste vide. Le gameplay, les timers, les limites
de scheduler et les primitives du jeu sont conservés.

- `host_fps_x100` : boucles hôte par seconde, multipliées par 100.
- `new_images_fps_x100` : nouveaux latches de framebuffer par seconde ×100.
  Ce n'est ni le compteur de swaps, ni une preuve de frames de gameplay complètes.
- `sum_ms` : cumuls pendant la fenêtre. `pre_guest_input` inclut chargements,
  logique/input, code ARM/MIPS et rasterisation GPU effectuée pendant ces appels.
  `presentation` est la conversion/copie vers l'écran hôte. `vblank` contient
  le callback VBlank ; `gfx` contient le flush/swap. `wait` est l'attente hôte.
- `seq_nested_ms` : temps ISR audio, également inclus dans les phases ci-dessus
  ou dans `unclassified_ms`. **Ne pas l'ajouter aux autres temps.** Résolution ms.
- `unclassified_ms` : reste du temps de boucle, dont diagnostics et service IRQ
  en fin de boucle. `previous_report_ms` donne le coût de l'écriture précédente.
- `ot_last_window_ms` : dernier bilan disponible de GsSortOt, réparation,
  soumission/rasterisation et merge. Peut appartenir à une fenêtre précédente.
- `nativeN` : appels du code ARM échantillonnés, 1 sur 64 en release PROFILE,
  classés par temps mesuré dans la fenêtre. Les temps ne sont pas multipliés
  par 64 et ne doivent pas être comparés directement aux temps exhaustifs.
- `overlay_totals` : compteurs MIPS/overlay cumulatifs, pas coûts de cette fenêtre.

L'ancien profiler exhaustif ARM n'était actif que sans NDEBUG. Le build PROFILE
habituel utilise NDEBUG ; le classement affichait donc peu d'informations.
Le sampling ajoute deux lectures d'horloge seulement une fois sur 64 probes,
et un rapport bref toutes les deux secondes. CLEAN n'inclut pas ce rapport.

Le test hôte compile le reporter de production et vérifie une fenêtre de
2000 ms, 50 boucles/s, 10 images/s, les cumuls et le temps audio imbriqué.
Les tests de livraison timer et les autres contrôles fonctionnels restent actifs.

## Essai nécessaire

Compiler PROFILE=1, lancer B136.32 puis rester environ 20 secondes dans une
scène lente de gameplay (par exemple le dialogue de Simon Muran). Lire :

```powershell
$testSd = Join-Path $env:APPDATA "Azahar\sdmc\3ds\fm-new3ds"
Get-Content "$testSd\perf-latest.txt"
```

Faire idéalement une deuxième mesure pendant la navigation dans la carte ou
un duel, en précisant la scène. Le classement guidera ensuite une optimisation
ciblée : limiter les coûts de rasterisation, accélérer un fallback MIPS identifié,
ou réduire le coût du séquenceur. La cadence globale reste à améliorer ;
B136.32 fournit la mesure et n'annonce pas encore un correctif de FPS.
