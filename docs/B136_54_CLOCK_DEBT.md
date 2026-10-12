# B136.54 — conserver les ticks pendant les tranches longues

Premier correctif issu de l'audit temporel B136.53. Il cible la perte de
temps PS1 pendant la surcharge ; il ne remplace pas Timer2 et ne change
pas les règles VSync, la cadence nominale 60 Hz ou le mode PAL.

## Avant / après

L'ancien helper plafonnait chaque livraison à quatre ticks et supprimait
les ticks entiers restants. Au-delà de 250 ms, il supprimait tout
l'intervalle, sans distinguer une pause d'un bloc guest long.

Le helper conserve maintenant une dette de ticks en 64 bits et la fraction
de milliseconde. Chaque passage en livre au maximum huit ; le reste est
conservé pour les passages suivants. Les tranches longues ne sont plus
assimilées automatiquement à des pauses. Le calcul ne tronque plus un
intervalle à 32 bits avant de calculer les ticks.

Le scheduler ne fait pas de `gspWaitForVBlank` tant qu'une dette reste
présente, même si le thread principal attend VSync ou son compteur de frame.
Le thread du jeu continue de recevoir ses tranches habituelles : aucun
tri, dessin ou appel CD n'est supprimé pour vider la dette.

Le runtime conserve ses fonctions de callback et ses gardes de réentrance.
Les ticks rattrapés empruntent la même chaîne VBlank/root counters/SEQ que
les ticks normaux. Timer2 conserve donc sa fusion d'échéances identifiée
dans l'audit : la cadence 73,83 Hz n'est pas corrigée dans ce build.

## Pause et chargement

La pause tactile arrête l'avancement de l'horloge ; la reprise établit
une nouvelle référence temporelle. Les hooks APT suspension/restauration
et veille/réveil demandent une remise à zéro dans la boucle principale.
Le callback APT ne modifie pas lui-même les compteurs guest. Le quick-load
conserve sa remise à zéro explicite de l'horloge, et un retour en arrière
du temps hôte remet également fraction et dette à zéro.

## Validation

Tests compilant le helper de production :

- Intervalles de 1 à 500 ms, y compris 75/90/100/150/250/251 ms :
  600 ticks pour dix secondes après livraison de la dette, aucun tick perdu.
- Mille tranches consécutives de 90 ms : 5400 ticks, soit 60 Hz, sans
  vidage supplémentaire. L'ancien code délivrait environ 44,44 Hz.
- Bloc de 400 ms : 24 ticks livrés en trois lots de huit, sans perte.
- Pas de sommeil hôte supplémentaire avec dette et VSync en attente.
- Temps de callback ajouté, timestamps au-delà de 32 bits, pause/reprise,
  quick-load, retour en arrière du temps et notifications APT.
- La boucle de livraison reste avant l'exécution guest, après les entrées.

Le diagnostic PROFILE ajoute `clock_debt pending=... batch_limit=8`.
L'écran inférieur reste vide. Essai utilisateur : `PROFILE=0 UNAI=1`.

## Limites de l'essai

La conservation de la dette n'équivaut pas à une capacité CPU illimitée.
Si le port produit durablement plus de travail que l'hôte ne peut en
traiter, la dette peut croître et l'horloge rester en retard. Le plafond
de huit évite une rafale sans limite de callbacks dans un seul passage ;
il ne constitue pas une garantie de rattrapage sous surcharge permanente.

Des boutons peuvent traverser plusieurs callbacks pendant un rattrapage,
comme c'était déjà possible avec les anciens lots de quatre. Le code du
pad reste inchangé. Vérifier les transitions Start, la navigation deck/coffre,
l'intro, les animations du duel et la pause/reprise sur Azahar/3DS.

Pas d'essai complet du jeu sur cet hôte. Le gain vise la vitesse temporelle
dans les situations où des ticks étaient abandonnés, pas une promesse de FPS.
