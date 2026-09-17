> [!NOTE]
> **Jalon historique PC.** Cette page documente la première génération/compilation du code français sur PC. Le backend New 3DS utilise maintenant ces objets statiques en ARM11 et un fallback R3000A. Voir [CURRENT_STATUS.md](CURRENT_STATUS.md).

# Base PC — C résident français compilé

Révision choisie : `Unchiga/psxrecomp@1965b2df424da03483a5370340433a862f78f103`.
Ne pas appliquer les adresses SLUS du jeu américain au jeu français.

## Validation historique

- outils PSXRecomp compilés en Release ;
- programme synthétique de contrôle traduit et compilé ;
- EXE français vérifié par SHA-256 : `57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44` ;
- expérience résidente : 719 fonctions, 15 shards, aucune ligne WARNING de génération ;
- shards + dispatch compilés en objets C hôte ;
- borne résidente expérimentale : `0x8D000` depuis `0x80010000`.

Les 719 fonctions ne sont pas un pourcentage de couverture. Le payload complet reste chargé en mémoire ; seule la génération statique est bornée.

## Architecture qui en a découlé

```text
PS1 EXE français
    -> PSXRecomp
    -> shards C résidents
    -> objets natifs
    -> runtime
```

Cette base est désormais réutilisée sur New 3DS : les shards sont cross-compilés en ARM11 puis combinés dans `work/arm-generated-objects/fm-generated-combined.o`.

La stratégie initiale prévoyait de recompiler les overlays séparément. Le backend 3DS a depuis ajouté un **fallback R3000A**, ce qui permet de continuer immédiatement lorsqu'une destination n'existe pas dans le dispatch statique. Les overlays chauds pourront toujours être recompilés ensuite si les mesures le justifient.

## Reproduire la génération

Prérequis : Python 3.11+, Git, CMake 3.20+, compilateur C/C++20.

```sh
python3 tools/bootstrap_pc.py \
  --framework work/upstream-psxrecomp \
  --exe /chemin/vers/SLES_039.48 \
  --jobs 4
```

Le profil français utilise la borne résidente `0x8D000` par défaut. Les sorties générées restent sous `work/` et ne doivent pas être versionnées.

## Références actuelles

- [PC_RUNTIME_BUILD.md](PC_RUNTIME_BUILD.md) — construction du runtime PC.
- [FIRST_MENU.md](FIRST_MENU.md) — premier menu français sur PC.
- [FIRST_DUEL.md](FIRST_DUEL.md) — première partie et premier duel sur PC.
- [NEW3DS_PROTOTYPE.md](NEW3DS_PROTOTYPE.md) — backend 3DS actuel.
- [ACTION_PLAN.md](ACTION_PLAN.md) — prochaines étapes.

## Licences

Le moteur PSXRecomp conserve sa licence et ses notices propres. Aucun code généré du jeu, BIOS propriétaire ou donnée de disque n'est distribué dans ce dépôt.
