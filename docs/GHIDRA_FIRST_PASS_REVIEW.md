> [!NOTE]
> **Analyse historique.** Cette première passe Ghidra précède le runtime PC puis le backend New 3DS. Les hypothèses statiques restent utiles, mais l'état courant se trouve dans [CURRENT_STATUS.md](CURRENT_STATUS.md).

# Première lecture de l'export Ghidra français

Source : `research/ghidra-fr/export`, exécution `20260914T181943Z-c81e28dd`.
Analyse statique du pseudo-C uniquement à cette date.

## Résultat vérifié

`COMPLETE.txt` indique 1546 fonctions reconnues et 4 échecs :

| Adresse | Erreur |
|---|---|
| 80100000 | Flow exceeded maximum allowable instructions |
| 8013b004 | Flow exceeded maximum allowable instructions |
| 80140000 | Flow exceeded maximum allowable instructions |
| 80146258 | Flow exceeded maximum allowable instructions |

Ces résultats ont ensuite été complétés par des extractions ciblées des overlays SU et des observations en exécution. Ils ne doivent pas être interprétés comme un pourcentage de couverture.

## Chemin observé depuis le démarrage

| Adresse | Observation | Interprétation historique |
|---|---|---|
| 80012a44 | Initialisations puis appels vers 80044084/8002d62c/8002df60 | Point de départ utile pour l'analyse |
| 80044084 | Boucles et appels vers 8018xxxx | Piste vers code chargé dynamiquement |
| 8002d62c | Switch sur résultat et état global | Sélection d'état |
| 8002df60 | Boucle infinie, appel indirect via 80091f7c | Répartiteur d'états |
| 80012c50 | Service récurrent | Cadence/rôle à établir |
| 800158f4 | Initialisation puis attente d'indicateur | Dépendance asynchrone |

## Leçon conservée

Les appels vers `0x801xxxxx` ne doivent pas être assimilés à une fonction résidente unique. Les analyses SU ont confirmé qu'une partie de ces zones reçoit du code dynamique. Le backend New 3DS utilise désormais un fallback R3000A pour ces destinations non couvertes, avant toute éventuelle recompilation dédiée.

## Limites importantes

- le pseudo-C Ghidra ne constitue pas une source compilable ;
- les prototypes inférés doivent être vérifiés au niveau registres/instructions ;
- une même adresse dynamique peut contenir plusieurs images différentes ;
- `halt_baddata()` ou une décompilation réussie ne suffisent pas à décider qu'une fonction est exploitable.

Pour la suite des overlays, voir [SU_LOADING_TRACE.md](SU_LOADING_TRACE.md), [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md) et [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md).
