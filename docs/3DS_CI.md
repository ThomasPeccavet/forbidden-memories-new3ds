# Vérification devkitARM sur GitHub Actions

Le workflow `.github/workflows/3ds-compile.yml` utilise l'image officielle
`devkitpro/devkitarm:20260610`, récupère PSXRecomp à la révision épinglée du
README, puis compile les objets C du profil 3DS. Il n'a besoin ni de l'ISO,
ni du BIOS, ni des sources générées du jeu. Il vérifie donc les erreurs du
compilateur ARM dans `main.c`, `fm_runtime_shim.c` et les autres sources.

Il ne lie pas encore le `.3dsx` : `rebuild_generated_release.sh` requiert la
génération française conservée localement dans
`work/pc-bootstrap/<horodatage>/generated`. Le dépôt public ne contient pas
ces fichiers. Pour préparer un build complet sans recopier toutes les
générations, compresser seulement la plus récente :

```sh
tar -czf generated-20260923.tar.gz \
  -C work/pc-bootstrap/20260923T090528Z-bc3035e4 generated
```

Partager cette archive dans la conversation pour examiner sa structure et
choisir un stockage privé adapté au build complet. Ne pas l'ajouter au dépôt
public par défaut.
