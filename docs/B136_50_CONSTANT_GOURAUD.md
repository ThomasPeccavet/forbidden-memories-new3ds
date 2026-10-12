# B136.50 — polygones GT de couleur constante

## Observation

B136.49 n'a pas changé la fluidité ressentie. Dans les quatre listes OT de
la sauvegarde de duel fournie, le parcours identifie 28 triangles GT constants
et 26 quads GT constants, contre 34 GT non constants (88 en tout).
Cela indique un cas fréquent à spécialiser, sans mesurer son coût dans
l'ensemble de la fenêtre de rendu.

## Modification

Dans l'adaptateur Unai, comparer les 24 bits RGB de tous les sommets d'un
paquet 34h/3Ch. S'ils sont identiques, appeler gpuDrawPolyFT avec POLYTYPE_GT
pour conserver le format des positions/UV. Activer la modulation flat lorsque
la couleur n'est pas 808080 ; ce dernier cas est neutre et ne requiert pas
la multiplication des composantes. Les commandes raw restent inchangées.
La transparence, la CLUT, les UV, le clipping et les gardes restent présents.
Les couleurs différentes restent sur gpuDrawPolyGT. Les commandes 4bpp
avec mélange additif conservent également leur driver Gouraud ARM existant :
le driver flat éclairé équivalent est en C, sans bénéfice ARM établi.

Ce chemin évite l'interpolation des trois couleurs et ses mises à jour
par pixel. Il utilise les drivers flat Unai existants, y compris leurs
routines ARM déjà intégrées, sans nouveau code assembleur.

## Validation

Une entrée de référence exclusivement compilée pour le test exécute le
chemin Gouraud précédent. 240 cas comparent toute la VRAM octet par octet :
triangles/quads irréguliers, clipping, trois profondeurs de texture, couleurs
neutres et modulées, quatre modes de mélange, texels transparents et vrais
dégradés qui doivent rester sur le chemin de référence. Les tests sprites
et gardes antérieurs restent présents. La compilation ARM vérifie la liaison.

Le microbenchmark hôte optionnel compare les mêmes paquets constants dans
les deux chemins. Ses temps ne prédisent pas les FPS de la 3DS/Azahar.
Le prochain essai utilise toujours PROFILE=0 UNAI=1 ; la save state corrigée
peut être restaurée. Aucun gain de FPS en jeu n'est encore validé.
