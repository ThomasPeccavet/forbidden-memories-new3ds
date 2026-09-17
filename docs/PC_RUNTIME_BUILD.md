> [!NOTE]
> **Jalon historique PC.** Cette page documente la construction du runtime PC qui a ensuite atteint le menu et le premier duel. Le backend New 3DS est désormais le chantier principal ; voir [CURRENT_STATUS.md](CURRENT_STATUS.md).

# Construction du moteur PC français

Cette cible assemble les shards français, le runtime PSXRecomp et OpenBIOS. Elle reste utile comme référence fonctionnelle et banc de comparaison, mais ce n'est pas la cible New 3DS.

## Résultat historique

Le 15 septembre 2026, la cible `fm-pc` a été compilée et liée sous Linux avec GCC/G++ 13.3, CMake 4.4.3 et SDL3 3.4.10. Les objets français et le backend OpenBIOS sont inclus dans le lien.

Le runtime a ensuite été utilisé avec le BIN français vérifié pour atteindre :

- l'écran titre ;
- le menu principal ;
- une nouvelle partie ;
- l'introduction ;
- le premier duel contre Simon Muran.

Les preuves associées sont dans `research/first-menu/` et `research/first-duel/`.

## Préparation

Exécuter d'abord `tools/bootstrap_pc.py --exe <SLES_039.48>` puis générer OpenBIOS avec la révision du moteur :

```sh
cd work/psxrecomp
PSXRECOMP_BIOS_BUILD=recompiler/build-pc bash tools/regen_bios.sh --config bios/OpenBIOS.toml
```

Révision moteur :

```text
1965b2df424da03483a5370340433a862f78f103
```

## Configuration et compilation

```sh
cmake -S pc -B work/pc-runtime \
  -DCMAKE_BUILD_TYPE=Release \
  -DPSXRECOMP_ROOT="<chemin absolu du moteur>" \
  -DFM_GENERATED_DIR="<chemin absolu du run>/generated" \
  -DFM_GAME_CONFIG="<chemin absolu du run>/game.toml" \
  -DBUILD_TESTING=OFF \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5

cmake --build work/pc-runtime --config Release --target fm-pc --parallel 4
```

## Lancement avec les ressources originales

```sh
work/pc-runtime/fm-pc \
  --game "<run>/game.toml" \
  --bios "<moteur>/bios/openbios.bin" \
  --disc "<jeu>/disc.cue" \
  --headless \
  --renderer software
```

Empreinte BIN attendue :

```text
9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
548 427 600 octets
```

## Rôle actuel du runtime PC

Le runtime PC sert maintenant de **référence comportementale** : si le backend New 3DS diverge pendant le boot, le menu ou le duel, on peut comparer les traces et écrans avec cette cible connue.

Le chantier de production est décrit dans [NEW3DS_PROTOTYPE.md](NEW3DS_PROTOTYPE.md) et [ACTION_PLAN.md](ACTION_PLAN.md).
