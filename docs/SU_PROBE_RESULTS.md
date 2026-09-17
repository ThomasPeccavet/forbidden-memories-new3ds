> [!NOTE]
> **Jalon historique d'analyse.** Ces résultats ont servi à confirmer le code dynamique chargé vers `0x80180000`. Le backend New 3DS actuel possède un fallback R3000A capable d'exécuter ce type de bloc ; voir [CURRENT_STATUS.md](CURRENT_STATUS.md).

# Résultat du sondage SU

Source : `research/su-probe/20260914T191332Z-c4ce3241/report.json`.

## Constats

- le mot initial à `8001002c` vaut `80180000`, comme celui à `80010008` ;
- les deux blocs de 32768 octets sondés ont des empreintes distinctes ;
- à `+0x390`, le prologue `d8ffbd27 1000b0af` correspond à du code MIPS cohérent ;
- l'association à un overlay chargé à `0x80180000` est fortement appuyée par les pointeurs de destination, les appels résidents et le code retrouvé ;
- les bases initiales à `800eb198` sont nulles et ne doivent pas être interprétées comme les valeurs effectives après initialisation.

## Table des états

Les 17 premiers mots à `80091f7c` sont des pointeurs dans le code résident. Le mot suivant `01030103` marque une frontière probable : ne pas extrapoler arbitrairement 32 fonctions à partir du masque `0x1f`.

## Nouvelle passe groupée

Les scripts `tools/run_su_ghidra.py` et `tools/ghidra/PrepareSU.java` construisent des instantanés statiques pour analyser les variantes candidates. Ils ne prétendent pas reproduire toute la RAM d'un instant d'exécution.

## Conséquence actuelle

Cette analyse est désormais intégrée à la stratégie 3DS :

1. les zones dynamiques `0x801xxxxx` sont considérées comme des images chargées, pas comme du code résident permanent ;
2. le fallback R3000A permet leur exécution immédiate ;
3. une éventuelle recompilation ARM doit être associée à une empreinte de l'image réellement chargée ;
4. les prochains tests 3DS devront journaliser les chargements d'overlay au moment où le contrôleur CD devient fonctionnel.

Voir [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md) pour l'analyse du menu et [ACTION_PLAN.md](ACTION_PLAN.md) pour l'intégration runtime.
