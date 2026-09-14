# Première lecture de l'export Ghidra français

Source : research/ghidra-fr/export, exécution 20260914T181943Z-c81e28dd.
Analyse statique du pseudo-C uniquement ; aucun essai sur PS1 ou New 3DS.

## Résultat vérifié

COMPLETE.txt indique 1546 fonctions reconnues et 4 échecs. Les quatre lignes
failed de functions.tsv sont :

| Adresse | Erreur |
|---|---|
| 80100000 | Flow exceeded maximum allowable instructions |
| 8013b004 | Flow exceeded maximum allowable instructions |
| 80140000 | Flow exceeded maximum allowable instructions |
| 80146258 | Flow exceeded maximum allowable instructions |

Ces lignes déclarent toutes un corps de 68 octets. Leur cause n'est pas établie.
Augmenter la limite du décompilateur sans vérifier les octets serait prématuré.

Attention : 1542 exports réussis ne signifient pas 1542 fonctions exploitables.
Les exports 8018001c.c et 80180390.c contiennent un avertissement de mauvaise
instruction et uniquement halt_baddata(). Ils illustrent une sortie acceptée
par le décompilateur malgré un code non exploitable. Ce constat porte sur les
fichiers examinés, pas sur un audit exhaustif des 1542 fichiers.

## Chemin observé depuis le démarrage

Sources : fichiers .c portant les adresses ci-dessous dans l'export.

| Adresse | Observation | Interprétation et limites |
|---|---|---|
| 80012a44 | Initialisations, puis appel de 80044084, résultat transmis à 8002d62c, puis 8002df60 | Point de départ confirmé pour poursuivre l'analyse |
| 80044084 | Boucles, appels à 8018001c, 80180390 et 80180e48 ; traitement des retours -1/-2 | Séquence préalable à la boucle principale ; écran titre non confirmé |
| 8002d62c | Switch sur le résultat ; affecte 8009c60a et des variables associées | Sélection d'un état ; noms des modes non identifiés |
| 8002df60 | Boucle infinie ; appel indirect via 80091f7c indexé par (8009c60a & 0x1f) | Répartiteur d'états, candidat pour la boucle principale |
| 80012c50 | Appelle 80012f70, 80012cb8, 80012d60 et 8003cea4 | Service récurrent dans plusieurs boucles ; cadence et rôle exacts à établir |
| 800158f4 | Appelle 8001569c puis 800158b4 | Initialisation puis attente d'un indicateur ; ne suffit pas à identifier un chargement |

8002df60 traite également les bits 0x80 et 0x40 de 8009c60a. Le masque 0x1f
permet 32 indices, mais ne prouve pas que la table possède 32 entrées valides.
Le contenu de la table n'est pas présent dans les fonctions examinées.

## Hypothèses à ne pas transformer en certitudes

Les appels vers 0x80180000 alors que le contenu importé est invalide peuvent
correspondre à du code chargé dynamiquement (overlay). D'autres causes restent
possibles : mauvais découpage code/données, transformation du code ou contexte
d'analyse incomplet. Le fichier d'archive contenant ce code n'est pas identifié.

Autre anomalie : 80013058 est déclarée avec un paramètre dans son export, mais
l'appel dans 80012a44 est rendu sans argument. Les prototypes inférés ne doivent
pas être repris tels quels dans une recompilation ; vérifier les registres et
les instructions autour des appels.

## Prochaines actions techniques

1. Relever les mots de la table 0x80091f7c dans le programme Ghidra ou le payload
   et vérifier les destinations, sans supposer 32 entrées valides.
2. Identifier les écritures/chargements vers 0x80180000 et le chemin exécuté
   avant les trois appels de 80044084.
3. Examiner les octets et les références des quatre fonctions en échec.
4. Étendre le bilan d'export pour distinguer réussite API, avertissements,
   halt_baddata, appels indirects non résolus et code effectivement exploitable.
5. Cartographier les états avec des observations en exécution avant de leur
   donner des noms comme titre, campagne ou duel.

Aucun fichier du pseudo-C original n'a été renommé ou corrigé sur la seule
base de ces hypothèses. Le portage New 3DS n'est pas encore commencé.
