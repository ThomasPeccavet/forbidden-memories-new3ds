# État courant — New Nintendo 3DS

Dernière mise à jour : **21 septembre 2026**.

## Résumé

Le backend New 3DS/Azahar a dépassé le jalon du menu principal. Le jeu affiche
désormais le menu français, accepte la navigation et la validation, lance une
nouvelle partie, permet de saisir puis valider le nom du joueur et progresse
jusqu'à la première cinématique / aux premiers dialogues.

Le verrou actif est maintenant :

> **la performance : le chemin fonctionnel actuel tourne à seulement quelques FPS
> dans les tests récents.**

La première cinématique atteinte présente également encore un rendu incorrect,
mais ce défaut vient après le problème de cadence : avant de continuer à patcher
les transitions, il faut comprendre où le temps d'exécution est réellement perdu.

## Révision de référence

~~~text
912036e9355873d652790a97e160819f031724d9
UP TO FIRST CINEMATIC AND CHAT
~~~

Cette révision inclut le chemin fonctionnel jusqu'à la première cinématique ainsi
que plusieurs étapes de profiling/optimisation B100+.

## Chemin actuellement validé

- PS-X EXE chargé à 0x80010000 ;
- entrée guest 0x800128CC ;
- code résident ARM11 + fallback R3000A ;
- BIOS, VBlank, pad et IRQ suffisants pour progresser ;
- lectures CD réelles et file async suffisantes pour le chemin observé ;
- GTE/helpers nécessaires au chemin courant ;
- DMA2 / GPU waits bridgés pour les cas observés ;
- GP0/GP1 et rasteriseur logiciel actifs ;
- logo Konami et écran titre affichés ;
- SU.mrg chargé et exécuté ;
- menu principal affiché ;
- navigation et validation fonctionnelles ;
- « Nlle partie » atteinte ;
- saisie du nom affichée ;
- écriture et validation du nom fonctionnelles ;
- première cinématique / premiers dialogues atteints.

## Ce qui a changé depuis B75

B75 avait prouvé que le menu SU existait mais restait invisible. Depuis :

- le chemin de rendu a été corrigé suffisamment pour afficher le menu ;
- la navigation du menu est utilisable ;
- la transition nouvelle partie fonctionne ;
- l'écran de nom est fonctionnel ;
- le nom peut être écrit puis validé ;
- le jeu poursuit son exécution après validation ;
- le chemin atteint désormais la première cinématique / les premiers dialogues.

Le problème de menu invisible ne doit donc plus être réinvestigué comme priorité.

## Performance — problème principal

Des pistes ont déjà été intégrées :

### B105 — présentation

- mesure du temps guest/rendu/VBlank/boucle ;
- LUT RGB555 → BGR888 ;
- suppression du memset complet à chaque frame.

### B106 — présentation 3DS

- flush/swap uniquement du framebuffer supérieur ;
- séparation du coût avant présentation, présentation et attente VBlank.

### B107 — profil release

- -O3 ;
- NDEBUG ;
- PSX_NO_DEBUG_TOOLS ;
- -fomit-frame-pointer ;
- reconstruction des shards PSXRecomp en release.

### B108 / B110 — timing et hotspots

- instrumentation du VSync guest ;
- statistiques de boucle ;
- mesure de plages guest ;
- classement des plages les plus coûteuses.

Malgré ces optimisations, le ralentissement reste visible. Cela indique que la
cause principale est probablement ailleurs que dans la simple conversion du
framebuffer.

## Hypothèses à départager

1. trop de temps passé dans le fallback R3000A ;
2. une fonction guest / un callback exécuté anormalement souvent ;
3. un wait PS1 bypassé de manière à créer une boucle active ;
4. trop de travail GPU logiciel par frame ;
5. coût important de copie/composition VRAM ;
6. mauvais modèle VBlank/VSync provoquant plusieurs frames logiques par frame hôte ;
7. bridge CD/DMA/GPU au timing incorrect ;
8. instrumentation encore trop présente sur le chemin chaud.

## Prochaine instrumentation

Mesurer au minimum :

- durée totale d'une frame hôte ;
- durée passée dans le dispatcher ;
- nombre d'instructions interprétées ;
- nombre et durée des fallbacks R3000A ;
- top 5 des plages PC guest par temps cumulé ;
- temps du VBlank callback ;
- temps du rendu logiciel ;
- temps de copie/present ;
- temps réellement passé à attendre VBlank ;
- nombre de commandes GP0 / primitives par frame.

Critère de succès :

> pouvoir attribuer au moins 80 % du temps d'une frame à un ou deux composants
> précis avant toute nouvelle optimisation.

## Cinématique

La première cinématique est atteinte, mais son rendu n'est pas encore correct.
Les travaux récents indiquent notamment des besoins autour du draw offset / draw
area PS1, de la page framebuffer, du mode d'affichage, de RGB24/MDEC et de la
composition de surfaces.

Cette partie doit être reprise juste après le diagnostic FPS afin d'éviter de
confondre défaut de rendu et défaut de timing.

## Ce qui reste non validé

- cadence fluide/acceptable ;
- cinématique fidèle ;
- progression stable jusqu'au premier duel sur 3DS ;
- émulation CD/IRQ/DMA générale sans bridges de bring-up ;
- GTE complet ;
- audio SPU/XA ;
- memory card / sauvegarde ;
- performance et stabilité sur New 3DS physique.

Le runtime PC reste la référence fonctionnelle.
