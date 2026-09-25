# Plan d'action — New Nintendo 3DS

Dernière mise à jour : **25 septembre 2026**.

## Objectif actif

Le port sait entrer en duel et jouer plusieurs tours, mais les dialogues 2D
avant/après combat ne sont plus rendus.

Le prochain objectif est :

> **rétablir la chaîne C2 de rendu du dialogue sans patch spécifique à un écran,
> puis revenir au profiling global du duel.**

## Phase 1 — Tester B135.80

Sur le premier villageois, relever :

```text
TAB80 c0/c2/c4/cc:...
C2TAB h:... ptr:........ exp:800408BC ent:... r416:...
```

Interprétation :

- `ptr != 800408BC` → table de fonctions C2 incorrecte ou mal chargée ;
- `ptr = 800408BC`, `ent=0` → target absent du dispatcher compilé ;
- `ptr = 800408BC`, `ent=1`, `408bc=0` → dispatch indirect/JALR défectueux ;
- `408bc>0` mais GP2D reste à 0 → problème interne à 408BC / callbacks / sortie OT.

## Phase 2 — Corriger la cause, pas le symptôme

La correction devra être placée au bon niveau :

- reconstruction de la table si elle est réellement corrompue ;
- ajout de seed/entry si la fonction statique manque ;
- correction du dispatch indirect si le pointeur est bon ;
- correction d'un callback précis seulement si la trace le prouve.

Éviter de forcer `FUN_800408BC` à chaque frame sans comprendre
`FUN_80041674`.

## Phase 3 — Valider les dialogues

Scénario minimal :

1. nouvelle partie ;
2. carte ;
3. parler au premier villageois ;
4. personnage et texte visibles ;
5. entrer dans le duel ;
6. finir le duel ;
7. parler au personnage suivant ;
8. texte/personnage visibles.

Critère : aucune dépendance à un save-state ancien.

## Phase 4 — Revenir à la performance duel

Les essais déjà réfutés :

- B135.74 : suppression diagnostics chauds → aucun gain ;
- B135.75 : fast path interpréteur → aucun gain visible.

La prochaine mesure doit séparer :

- code ARM recompilé ;
- fallback R3000A ;
- rasteriseur logiciel ;
- DMA / OT / soumission ;
- présentation ;
- waits ;
- routines guest répétées.

Ne pas optimiser avant d'avoir identifié le budget dominant.

## Phase 5 — Images de cartes

Une fois le dialogue stable :

- tracer ID logique de carte ;
- adresse/offset asset ;
- CLUT / tpage ;
- relation nom/stats/image ;
- comparer au runtime PC.

## Phase 6 — Réduire la dette B135

Pour B135.64 / 66 / 71 :

1. documenter condition et effet ;
2. remonter au code PS1 qui devrait produire l'état ;
3. remplacer progressivement le safety net par le comportement natif ;
4. vérifier le duel après chaque retrait.

## Discipline

- une hypothèse par branche ;
- un test discriminant avant un correctif ;
- conserver B135.71 comme oracle ;
- ne pas rebasculer vers les heuristiques de framebuffer déjà réfutées ;
- ne jamais committer BIN, BIOS Sony, EXE extrait ni données propriétaires ;
- captures + compteurs + commit pour chaque jalon.
