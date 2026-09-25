# B135.73 CARD-LI — chargement natif des illustrations

## But

Conserver le duel fonctionnel de B135.71 tout en corrigeant le chemin GPU
utilise par le cache des miniatures de cartes.

Les tests B135.72 ont montre que les noms, identifiants et statistiques sont
coherents, mais que les illustrations appartiennent a d'autres cartes. Une
mauvaise illustration suit sa carte lorsque la main se decale : le probleme
n'est donc pas un emplacement d'ecran fige.

## Chemin original reconstitue

```text
FUN_80024A9C
  -> table DAT_801A7E20
  -> source DAT_8018C2D8 + image_index * 0x580
  -> FUN_8007FF10(rect, pixels)
  -> driver GPU indirect / DMA2
  -> VRAM

FUN_80017E94
  -> memorise le slot de cache dans objet+0x6A

FUN_800166A0
  -> relit objet+0x6A
  -> DAT_801A7AD8[slot]
  -> UV/TPAGE de la miniature
```

`FUN_8007FF10` est le chemin synchrone utilise par le cache de cartes. Le HLE
CPU->VRAM valide ne couvrait jusque-la que `FUN_80082380` (`LoadImage2`). Les
miniatures continuaient donc par le chemin DMA2 incomplet du bring-up.

## Correction isolee

- `8007FF10` et `80082380` utilisent maintenant le meme transfert GP0(A0h)
  CPU->VRAM deja valide ;
- les appels ARM directs sont interceptes a l'entree generee avant que le
  corps DMA original ne s'execute ;
- les arguments `a0/a1` et `ra` du code original sont preserves ;
- B135.71 reste actif sans modification comme filet de securite ;
- une trace en lecture seule capture la correspondance
  slot/ressource/ID/index/source de `80024A9C`.

## Lignes de diagnostic

```text
T73 LI 7F/823/N/F:a/b/c/d
T73 C n:x s/r:y/z id/i:i/j
T73 V src:aaaaa p:bbbbbbbb e/ra:ccccc/ddddd
```

- `7F` : uploads traites depuis `8007FF10` ;
- `823` : uploads traites depuis `80082380` ;
- `N` : appels ARM directs interceptes ;
- `F` : arguments d'upload invalides ;
- `n` : consultations de `80024A9C` ;
- `s/r` : slot atlas et ressource resolus ;
- `id/i` : identifiant de carte et index du bloc image ;
- `src/p` : source RAM et premier mot du bloc ;
- `e/ra` : derniere entree LoadImage et adresse de retour.

## Test demande

1. Charger le meme quick-state B135.71.
2. Verifier que la premiere carte est toujours `Lampe Antique`, ID 134,
   ATK 400 / DEF 300.
3. Comparer son illustration avec B135.72.
4. Jouer une carte et attendre la nouvelle pioche.
5. Photographier les trois lignes `T73`, `HAND@D60` et `FORCE`.

Si `T73 LI 7F` reste a zero, le chemin original n'a pas atteint le wrapper et
la trace `80024A9C` donnera le prochain point de coupure. Si `7F` augmente mais
que l'image reste fausse, comparer `id/i` et le premier mot source permettra de
distinguer une mauvaise table d'un buffer decompresse incorrect.
