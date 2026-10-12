# Audit du rythme après B136.53

9 octobre 2026. Audit uniquement : aucune modification de l'horloge,
des interruptions, de VSync ou du séquenceur. Pas de build B136.54.

## 1. Temps abandonné après une tranche longue : reproduit

`3ds/include/fm_host_clock.h`, `fm_host_clock_due` calcule les ticks à
60 Hz à partir du temps hôte, puis retourne au maximum quatre ticks.
La fraction modulo 1000 est conservée, mais les ticks entiers excédentaires
sont perdus : aucune dette ne les conserve. Si une seule tranche dépasse
250 ms, aucun tick n'est retourné pour cet intervalle.

La même valeur `clock_due` commande, dans `main.c`, l'incrément de `frame`,
les root counters, les callbacks Timer2 et le callback VBlank. Ce plafond
ralentit donc plusieurs horloges du jeu, pas seulement la présentation.

Test hôte exécutant le helper de production sur une minute simulée :

| Intervalle entre appels | Cadence effective | Cadence attendue |
| --- | ---: | ---: |
| 16 ms | 60 Hz | 60 Hz |
| 20 ms | 60 Hz | 60 Hz |
| 50 ms | 60 Hz | 60 Hz |
| 75 ms | 53,33 Hz | 60 Hz |
| 90 ms | 44,44 Hz | 60 Hz |
| 100 ms | 40 Hz | 60 Hz |
| 150 ms | 26,67 Hz | 60 Hz |
| 250 ms | 16 Hz | 60 Hz |
| 251 ms | 0 Hz | 60 Hz |

Ces intervalles sont des scénarios de test, pas des mesures du menu actuel.
Des intervalles de 90 ms produiraient environ 74 % de la cadence attendue.
Des fenêtres historiques ont des max_loop supérieurs à 100 ms, mais cela
ne prouve ni leur fréquence actuelle ni qu'ils expliquent tout le ralenti.

La remise à zéro lors d'une vraie pause/quick-load est une protection utile.
Elle ne doit pas être confondue avec une longue tranche pendant le jeu.
Retirer brutalement le plafond pourrait créer une rafale d'ISR coûteuses
et accentuer la surcharge. Il faut distinguer temps logique et livraison
bornée des callbacks avant de corriger.

## 2. Timer2 et SEQ : échéances fusionnées

La configuration capturée `mode 0A58, cible E000` sélectionne notamment
system/8, reset à la cible et interruptions répétées. Le timer du port
utilise une période `target + 1`, soit une cadence nominale :

`33 868 800 / 8 / (0xE000 + 1) = environ 73,83 Hz`.

`fm_timer_advance` avance le compteur d'un bloc à chaque tick 60 Hz et
ne marque la cible qu'une fois, même si plusieurs périodes sont franchies.
`I_STAT` est un bit d'interruption, sans nombre d'échéances en attente.
`fm_execute_guest_timer_callback` consomme cette interruption une fois.
Son autre point d'appel dans le dispatch ne recrée pas les échéances perdues.

En régime régulier, les seules avances périodiques Timer2 à 60 Hz ne
permettent donc pas de délivrer toutes les échéances nominales à 73,83 Hz.
Le rapport 60/73,83 vaut environ 0,813. Des masquages, gardes CD et des
ticks abandonnés peuvent encore retarder la livraison.

Ce constat concerne d'abord le séquenceur musical et les scripts qui
attendent sa progression. Il ne prouve pas que tous les déplacements ou
animations du jeu sont cadencés par SEQ. Augmenter arbitrairement tous les
ticks/VBlanks n'est pas une correction valable de Timer2.

## 3. VSync : attente mode zéro justifiée

Le helper original présent dans la sauvegarde à `800746B8` a été examiné.
Pour mode zéro, il effectue une première attente basée sur le dernier
compteur synchronisé, puis demande explicitement `compteur courant + 1`
à `80074780..80074790`. `80074830` attend tant que le compteur est inférieur
à sa cible. Le HLE `frame + 1` pour VSync(0) n'est donc pas à lui seul une
preuve d'attente supplémentaire incorrecte.

Le compteur hôte n'est rafraîchi qu'au début de la boucle principale.
Le temps écoulé pendant une tranche n'est visible qu'au tour suivant.
Les tranches budget sont déjà reprises sans `gspWaitForVBlank` lorsqu'aucune
attente VSync/frame n'est active ; les fins d'attente reprennent ensuite
le code dans la même tranche. Le cas supposé « une frame hôte perdue à
chaque budget » n'est pas confirmé par le code actuel.

Pour VSync(n>=2), l'original attend d'abord `dernier_sync + n - 1`, puis
`courant + 1`. Le HLE attend directement `dernier_sync + n` et peut revenir
immédiatement s'il est déjà dépassé. Ces sémantiques diffèrent lors d'un
retard. Les anciennes fenêtres de duel montraient cependant modeN=0 : ce
point n'est pas démontré responsable du ralenti observé. Il faut traiter
ce cas séparément et conserver les modes interrogatifs -1 et 1.

## 4. PAL/NTSC : modèle mixte confirmé

La sauvegarde GPU donne `display_mode=0x9`, avec le bit PAL actif.
L'horloge VBlank reste fixe à 60 Hz ; VSync(1) utilise 15 625 HSync/s PAL.
Timer1 peut avancer de 314 unités par tick pour sa source HSync, soit
18 840 unités/s à 60 ticks/s, au lieu du rythme PAL utilisé par VSync(1).
Le modèle n'est donc pas uniformément PAL.

Un passage isolé de 60 à 50 Hz ne constitue pas une accélération : il
diminue les VBlanks, et ralentirait Timer2 si sa constante 60 restait
inchangée. Il risquerait aussi les synchronisations CD/audio/intro existantes.

## Priorités proposées

1. Séparer le temps logique écoulé du nombre borné de callbacks exécutés,
   en distinguant pause et surcharge pendant le jeu.
2. Donner à Timer2 une cadence indépendante des VBlanks, avec livraison
   aux limites CPU sûres et politique explicite pour les IRQ masquées.
3. Unifier ensuite la cadence PAL/NTSC, VSync et Timer1 ; valider l'intro,
   le menu, SEQ et le duel avant toute publication d'un correctif temporel.

Limite : pas d'exécution du jeu complet dans Azahar/3DS sur cet hôte.
La sauvegarde fournit un état, pas une trace des durées entre mises à jour.
Les anomalies de code sont établies ; leur contribution au ralenti actuel
reste à vérifier. Aucune promesse de gain FPS ou de vitesse globale.
