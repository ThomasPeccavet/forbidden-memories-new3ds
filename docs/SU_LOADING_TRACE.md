# Piste SU.MRG et chargement par étapes

Analyse statique des exports research/ghidra-fr/export/pseudo-c. Aucun essai
Ghidra, extraction du disque ou test console effectué pendant cette passe.

## Chemin suivi

80012a44 appelle 80043e3c(0), qui appelle notamment 8006b560 puis attend via
80013700. 8006b560 configure 80014d38 avec : mode 1, symbole de chaîne
s_M__mrgSU_SU_mrg_800117fc, position DAT_8009c44b * 0x88, longueur 0x73,
callback 8006b350. Le nom exact de la chaîne n'est pas exporté : seul son
symbole apparaît dans le pseudo-C.

80014d38 passe la requête à 800138b4, qui appelle 8001385c. Cette dernière
convertit les longueurs négatives en octets avec un facteur 0x800, et les
positions positives par un décalage de 11 bits. Le champ +0x24 ajoute la base
DAT_800eb198[mode & 0xf]. L'association au fichier SU.MRG est une hypothèse
fortement appuyée par le symbole, mais la base doit être vérifiée.

80012c50 -> 80012f70 -> 80014978 -> 80014478 assure le traitement récurrent.
Dans 80014478, DAT_800eb1d8 est invoquée avec le contexte 800eb1b8 et un index
qui est incrémenté. 800138b4 stocke précisément le callback au champ +0x20,
soit 800eb1d8 pour ce contexte. Cela relie la requête aux étapes ci-dessous.

## Étapes de 8006b350

Offsets dans la structure de requête, en octets : +8/+0xc adresses ; +0x1c
taille du segment ; +0x46 mode de traitement. Interprétation du transfert
encore à confirmer dans ses routines de bas niveau.

| Index | Taille | Destination indiquée |
|---|---|---|
| 0 | 0x20000 | Tampon DAT_8009c4b0, mode 2 |
| 1 | 0x10000 | Même tampon, mode 2 |
| 2 | 0x1000 | 0x801dd000, mode 1 |
| 3 | 0x8000 | PTR_DAT_8001002c, mode 1 |
| 4 | 0x800 | 0x801af800, mode 1 |

Somme : 0x39800 = 0x73 * 0x800, exactement la taille de la requête.
La capture de références fournie par Thomas identifie PTR_DAT_8001002c comme
pointant à 0x80180000. À confirmer par lecture du mot dans le programme.
Sous hypothèse de consommation séquentielle, l'étape 3 commence à +0x31000
au sein de la requête. Pour les variantes 0 et 1, les offsets candidats dans
SU.MRG sont respectivement 0x31000 et 0x75000. La sélection 0/1 est un sondage,
pas une liste exhaustive de variantes ni une attribution linguistique.

Cette correspondance est une piste de code dynamique, pas encore une preuve :
il faut examiner les octets et confirmer la consommation séquentielle. La
zone 0x80180000 apparaît également dans le traitement de modèles.

## Autres observations

8008a208 convertit des offsets en mots en adresses à partir de la base du bloc
et pose le bit 0 du champ +4. Cela confirme une relocation de données, sans
identifier à lui seul un format standard ou une fonction du SDK.

80043dc8 utilise une autre requête : position param_1*0x6e+0x1962, callback
80043658. Ce callback emploie PTR_DAT_800101e0/1e4/1e8 ; leurs valeurs restent
à relever avant toute interprétation de la mémoire concernée.

## Sondage groupé à exécuter une fois

Mettre à jour le dépôt cloné avec Pull origin, puis, depuis sa racine :

```bat
py -3 tools\probe_su_overlay.py "CHEMIN_COMPLET_VERS_LE_BIN"
```

L'outil contrôle la taille et le SHA-256 du disque français, lit les tables
initiales de l'exécutable, extrait deux segments candidats de SU.MRG et écrit
research/su-probe/<date>/report.json. Il ne lance pas Ghidra et ne modifie pas
le disque. Les deux .bin extraits restent locaux, ignorés par Git.

Envoyer uniquement report.json via GitHub Desktop (commit puis push). Il
contient les pointeurs, 32 mots bruts autour de la table d'états (sans garantir
32 entrées valides), les bases initiales des sources, des empreintes et des
extraits hexadécimaux des segments candidats.

Validation : code relu, mais non exécuté dans cette session dépourvue de
terminal. L'extraction et les hypothèses d'offset attendent cette vérification.
Les bases à 800eb198 peuvent être initialisées à l'exécution : leurs octets
initiaux seuls ne prouvent pas la configuration effective.
