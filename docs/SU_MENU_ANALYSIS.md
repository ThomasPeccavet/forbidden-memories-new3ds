> [!NOTE]
> **Analyse historique d'overlay.** Cette page identifie un menu chargé à `0x80180000`. Le backend New 3DS actuel n'affiche pas encore ce menu, mais son fallback R3000A est conçu pour exécuter ce code lorsqu'il sera chargé par le chemin CD. Voir [CURRENT_STATUS.md](CURRENT_STATUS.md) et [ACTION_PLAN.md](ACTION_PLAN.md).

# Menu SU retrouvé — seconde passe

Source : `research/su-ghidra/20260914T192136Z-c0a29453`.

## Validation

Les deux exécutions Ghidra retournent 0, avec `export_completed=true`, `functions=1582`, `failed=1`. L'échec restant est `80100000: Flow exceeded maximum allowable instructions`.

Les compteurs de fonctions ne sont pas un indicateur de couverture ni de correction du portage.

## Cycle d'un menu

| Adresse | Nom de travail | Éléments observés |
|---|---|---|
| 8018001c | su_menu_init | Création d'objets d'interface, index initial, callback |
| 80180390 | su_menu_update | Navigation, transitions, sous-dialogues, codes de retour |
| 80180da4 | su_menu_begin_transition | Positions cible et compteurs de transition |
| 80180e48 | su_menu_destroy | Libération et remise à zéro du callback |

Ces noms restent descriptifs ; ils ne remplacent pas des symboles originaux.

Le retour `0xffffffff` correspond généralement à une poursuite du traitement. `0xfffffffe` apparaît dans une branche liée à l'inactivité. Les unités temporelles exactes restent à valider.

## Lien avec le code résident

L'entrée 8 de la table `80091f7c` pointe vers `8002d75c`. Le chemin observé charge l'overlay, initialise le menu avec `8018001c`, appelle ensuite `80180390`, puis nettoie avec `80180e48` avant de repasser par la sélection d'état résidente.

Cette chaîne constitue une référence utile pour le backend New 3DS : lorsqu'un overlay identique est chargé à `0x80180000`, le fallback R3000A doit pouvoir commencer son exécution avant toute recompilation dédiée.

## États résidents observés

Les 17 états étudiés sont conservés comme table de travail. Plusieurs chemins chargent d'autres blocs dynamiques `0x801xxxxx`; leur signification doit être validée à l'exécution avant de leur donner un nom fonctionnel définitif.

## Limites

- les fonctions dynamiques ne doivent pas être nommées globalement par adresse seule ;
- certaines signatures Ghidra restent imparfaites ;
- l'absence de `halt_baddata` dans une fonction ne valide pas tout l'overlay ;
- les autres overlays restent à extraire/observer.

## Utilité actuelle

Ce document sert maintenant de cible comportementale pour la phase « overlays » de [ACTION_PLAN.md](ACTION_PLAN.md). Le jalon immédiat reste toutefois plus bas niveau : IRQ/VBlank, DMA GPU et première VRAM réelle sur New 3DS.
