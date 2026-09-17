> [!NOTE]
> **Analyse historique d'overlay.** Cette page décrit la première cartographie statique de SU.MRG. Le backend New 3DS dispose maintenant d'un fallback R3000A destiné précisément à exécuter ces images dynamiques avant toute recompilation dédiée. Voir [CURRENT_STATUS.md](CURRENT_STATUS.md) et [ACTION_PLAN.md](ACTION_PLAN.md).

# Piste SU.MRG et chargement par étapes

Analyse statique des exports `research/ghidra-fr/export/pseudo-c`.

## Chemin suivi

`80012a44` appelle `80043e3c(0)`, qui appelle notamment `8006b560` puis attend via `80013700`. `8006b560` configure `80014d38` avec une requête associée au symbole `s_M__mrgSU_SU_mrg_800117fc`, une position liée à `DAT_8009c44b`, une longueur `0x73` et le callback `8006b350`.

`80014d38` passe la requête à `800138b4`, qui appelle `8001385c`. Cette dernière convertit les longueurs négatives en octets avec un facteur `0x800` et les positions positives par un décalage de 11 bits.

Le chemin `80012c50 -> 80012f70 -> 80014978 -> 80014478` assure le traitement récurrent.

## Étapes de 8006b350

| Index | Taille | Destination indiquée |
|---|---|---|
| 0 | 0x20000 | Tampon DAT_8009c4b0, mode 2 |
| 1 | 0x10000 | Même tampon, mode 2 |
| 2 | 0x1000 | 0x801dd000, mode 1 |
| 3 | 0x8000 | PTR_DAT_8001002c, mode 1 |
| 4 | 0x800 | 0x801af800, mode 1 |

Somme : `0x39800 = 0x73 * 0x800`.

La capture de références fournie lors de l'analyse identifie `PTR_DAT_8001002c` comme pointant vers `0x80180000`. Sous hypothèse de consommation séquentielle, l'étape 3 commence à `+0x31000` dans la requête.

## Ce qui a été confirmé ensuite

Le sondage SU et la seconde passe Ghidra ont fortement confirmé que le bloc chargé à `0x80180000` contient du code MIPS cohérent et correspond à un overlay de menu. Voir :

- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)

Cette zone dynamique ne doit pas être considérée comme une fonction permanente : différentes images peuvent réutiliser la même adresse.

## Conséquence pour le backend New 3DS

Le fallback R3000A permet maintenant d'exécuter immédiatement un bloc chargé dans `0x801xxxxx` sans attendre une nouvelle génération PSXRecomp. Une recompilation ARM dédiée pourra être ajoutée plus tard pour les overlays chauds et identifiés de manière stable.

Le prochain travail lié aux overlays consiste à journaliser l'adresse, la taille, la source et une empreinte de chaque image réellement chargée pendant le boot New 3DS.
