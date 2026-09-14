# Résultat du sondage SU

Source : research/su-probe/20260914T191332Z-c4ce3241/report.json.

## Constats

- Le mot initial à 8001002c vaut 80180000, comme celui à 80010008.
- Les deux blocs de 32768 octets ont des empreintes distinctes, mais leurs
  extraits de 256 octets et ceux à +0x390 sont identiques.
- Le début comprend 0x33 et des adresses dans la plage 80180000.
  À +0x1c : mot 0x3c022e8b (lui v0,0x2e8b), suivi d'instructions cohérentes.
- À +0x390 : d8ffbd27 = addiu sp,sp,-40 ; 1000b0af = sw s0,16(sp).
  Ce prologue remplace précisément le contenu invalide analysé précédemment
  à 80180390. Forte preuve de code MIPS dans le segment extrait.
- L'association à un overlay chargé à 80180000 est très fortement appuyée
  par les appels résidents, le pointeur de destination et le code retrouvé.
  Son exécution effective reste à observer ; aucune capture RAM n'est disponible.
- Les bases initiales à 800eb198 sont nulles : ne pas les interpréter comme les
  valeurs effectives de lecture du disque après initialisation.

## Table des états

Les 17 premiers mots à 80091f7c sont des pointeurs dans le code résident.
Le suivant est 01030103 : ne pas créer arbitrairement 32 fonctions avec le
masque 0x1f. Cette frontière probable reste à vérifier dans le Listing.
Sur les 17 chemins de fichiers par adresse consultés, seuls 8002d354.c et
8002dbe0.c sont présents ; 15 renvoient 404. Cela ne prouve pas que leurs octets
n'apparaissent dans aucune autre fonction exportée. La seconde passe les
déclare explicitement comme points d'entrée.

## Nouvelle passe groupée

Les scripts tools/run_su_ghidra.py et tools/ghidra/PrepareSU.java créent deux
projets neufs. Chaque projet importe le payload français complet, remplace
uniquement [80180000,80188000) par un candidat vérifié par SHA-256, puis ajoute
les points d'entrée de démarrage, les 17 états et les trois appels SU connus.

Ce sont des instantanés statiques construits pour l'analyse. Ils ne prétendent
pas reproduire toute la RAM à un instant du jeu. Les autres overlays sont
toujours absents. Les deux variantes ne sont pas supposées correspondre à des
langues particulières.

Depuis le dépôt cloné mis à jour :

```bat
py -3 tools\run_su_ghidra.py --ghidra "C:\Dev\ghidra" --probe-dir "research\su-probe\20260914T191332Z-c4ce3241" --payload "CHEMIN_COMPLET_VERS_PAYLOAD.bin"
```

Les deux candidats BIN doivent être présents dans le dossier du sondage local.
Ils sont exclus de Git : utiliser le dossier où probe_su_overlay.py a réellement
été exécuté s'il diffère de celui du clone.

Résultats texte : research/su-ghidra/<date>, à envoyer par commit et push.
Projets Ghidra : work/su-ghidra/<date>, restent locaux.
Le fichier run-summary.json indique le résultat de chaque exécution.
Les compteurs COMPLETE ne garantissent pas l'absence de halt_baddata.

Validation : empreintes et extraits du rapport inspectés ; scripts relus mais
non exécutés faute d'environnement local. Leur premier lancement reste à
valider. La nouvelle analyse n'est pas encore une recompilation New 3DS.
