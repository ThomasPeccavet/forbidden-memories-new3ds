# Menu SU retrouvé — seconde passe

Source : research/su-ghidra/20260914T192136Z-c0a29453.
Analyse des exports de variant_0, comparaison des trois fonctions principales
avec variant_1. Aucun essai console ; pas de recompilation native.

## Validation

Les deux exécutions retournent 0, export_completed=true, functions=1582,
failed=1. L'échec restant est 80100000 : Flow exceeded maximum allowable
instructions. Les compteurs ne constituent pas un indicateur de couverture.
Le changement de 1546 à 1582 mêle nouveaux points d'entrée et nouvelles
interprétations du code, et ne mesure pas 36 fonctions correctes ajoutées.

Les exports 8018001c, 80180390 et 80180e48 sont identiques textuellement entre
les deux variantes. Cela ne prouve pas que les blocs de 32 Ko sont identiques :
leurs empreintes diffèrent et le reste n'a pas été comparé intégralement.

## Cycle d'un menu

| Adresse | Nom de travail proposé | Éléments observés |
|---|---|---|
| 8018001c | su_menu_init | 3 objets d'interface, 11 objets de choix, index initial modulo 11, inscription du callback 80180b4c à 8009c898 |
| 80180390 | su_menu_update | Navigation entre choix, deux groupes 0–4 et 5–10, transitions, sous-dialogues, retour d'un index ou -1/-2 |
| 80180da4 | su_menu_begin_transition | Position cible centrale 0xa0 ou hors écran -0xa0/0x1e0, compteur 0x10 pour chaque objet |
| 80180e48 | su_menu_destroy | Libération des objets et remise à zéro du callback 8009c898 |

Ces noms restent descriptifs et ne remplacent pas les symboles du dump.
Le libellé exact de chaque option n'est pas encore identifié.
Les 11 objets ne signifient pas 11 options visibles simultanément :
le code sépare la navigation en groupes de 5 et 6.

Le retour 0xffffffff (-1) indique généralement que le traitement continue.
Le retour 0xfffffffe (-2) apparaît lorsque le compteur d'inactivité dépasse
2999 dans une branche de présentation. Ce seuil n'est pas converti en secondes :
la cadence et les unités demandent une validation.
La touche attendue dans cette branche est représentée par le masque 0x800 ;
le nom physique du bouton n'est pas confirmé ici.

Les choix 1, 2, 3 et 10 ouvrent des traitements particuliers via
8003faf8/8003fb34, 80040038, 8003fffc et 8003fba0/8003fa30.
Leurs significations produit (sauvegarde, échange, etc.) ne sont pas attribuées.

## Lien avec le code résident

L'entrée 8 de la table 80091f7c pointe à 8002d75c.
Son premier passage :
1. pose le bit 0x40 de 8009c60a ;
2. appelle 8006b560 puis attend avec 80013700 ;
3. initialise le menu avec 8018001c(8009c60c,8009c60e).
Les passages suivants appellent 80180390.
Un résultat positif ou nul entraîne le nettoyage par 80180e48, puis
8002d62c(resultat), qui sélectionne le nouvel état. 8009c60d est fixé à 8.

Cela relie le bloc extrait de SU.MRG à une interface de sélection appelée
au démarrage et depuis l'état 8. Le chemin 80044084 utilise lui aussi ces
trois fonctions, mais traite -2 en recommençant sa séquence.

## Table des états résidents

Indices en décimal. Les entrées ci-dessous sont désormais exportées.
Les rôles non identifiés gardent une description technique.

| État | Adresse | Chemin observé |
|---:|---|---|
| 0 | 8002cfdc | Initialisation 800303ec puis traitement 80031388 |
| 1 | 8002d354 | Initialisation 8005622c/80056540, traitement 80056620 ou 8005cd90 ; piste présentation de modèles |
| 2 | 8002d038 | 8002ff64 puis 80030228/8002fca4 |
| 3 | 8002d0bc | Sous-états 0,1,2 ; 80032824, 8001798c, 80024444 puis transition |
| 4 | 8002d2b4 | 8002c1ac puis 8002bc38 |
| 5 | 8002d4ac | Chargement 8003c3c4 puis appels 8016866c/80168fcc |
| 6 | 8002d5cc | Chargement 8003bcb4 puis appel 80169024 |
| 7 | 8002d544 | 80032824 puis 800340e8 ; retour à l'état mémorisé |
| 8 | 8002d75c | Menu SU : chargement, création, mise à jour, destruction |
| 9 | 8002d800 | Chargement 8003bef4 puis 80168344/80169a1c |
| 10 | 8002d858 | Chargement 8003c1b8 puis 80169e64/8016a160 |
| 11 | 8002d89c | Chargement 8003c90c puis 801686ac/80168e1c |
| 12 | 8002d8f4 | 8003cae0, 8003cb44, 8003cc58 ; retour possible au menu 8 |
| 13 | 8002d988 | Fonction vide dans cet export |
| 14 | 8002d990 | 80032754 puis appels 801820c0/80182408/80184210 |
| 15 | 8002dbe0 | Sous-états et présentation via 8005622c/80056540/8005cda4 |
| 16 | 8002de14 | Initialise deux valeurs à 8000 puis appels 80181050/80181408/80181f88 |

Les adresses dynamiques réutilisées ne doivent pas être nommées globalement :
un état qui charge un autre bloc peut appeler un contenu différent à la même
adresse. En particulier l'état 14 appelle d'abord 80032754. Ne pas interpréter
ses appels à 80182xxx à partir du seul instantané SU sans vérifier ce chargement.

## Limites techniques importantes

- Les états 9, 10 et 11 contiennent unaff_gp. Avec le GP observé au démarrage
  8009c298, +0x372 correspond à 8009c60a et +0x375 à 8009c60d.
  C'est une correspondance calculée, pas une nouvelle capture du registre.
- Le découpage des fonctions est imparfait : functions.tsv déclare 144 octets
  pour 80180390 alors que le pseudo-C parcourt une logique plus étendue.
- Une fonction 80180004 est créée dans la zone d'en-tête/pointeurs observée.
  Elle ne doit pas être considérée comme une fonction valide sans vérification.
- L'absence de halt_baddata dans les trois fonctions étudiées ne valide pas
  tous les exports. Les autres overlays demeurent à extraire.

## Suite autonome possible avec ces exports

Identifier les traitements des choix et les ressources graphiques du menu,
examiner les chargements associés aux états 5/6/9/10/11/14, puis définir des
instantanés séparés pour chaque bloc. Préférer une extraction groupée après
cartographie des requêtes, plutôt qu'une nouvelle manipulation par fonction.
