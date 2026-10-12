# B136.31 — livraison du séquenceur indépendante du rendu

## Problème observé

B136.30 corrige la source du timer2, mais pas son ordonnanceur. Le dispatcher
n'acceptait un IRQ qu'à `80012C50`, l'entrée du service de frame du jeu. Le
callback prenait ensuite les mêmes tranches de 12 ms que le thread principal.
Pendant les updates coûteux, les échéances du timer s'accumulaient dans un seul
bit I_STAT. L'horloge du séquenceur progressait donc à une cadence inférieure à
celle du compteur. Les 6868 retours du log comptent tous les callbacks depuis
le boot ; ils ne signifient pas 6868 avances de la dernière piste musicale.

L'utilisateur a ensuite atteint Simon Muran sans nouveau build. Le second
log confirme une autre commande de script (`8002`, texte ID `501`) et un
nouveau chargement CD terminé (1420 secteurs contre 1199). Il s'agissait donc
ici d'une attente excessivement longue, pas d'un arrêt permanent du CPU.

## Changement

Le timer est livré après `fm_memory_vblank_tick`, avant le service VBlank du
jeu, et à la première frontière du dispatcher où le masque l'autorise.
Ce second point est nécessaire : les captures sont prises dans DrawSync avec
I_MASK nul, et il faut saisir sa réactivation sans attendre la fin de frame.
I_STAT est acquitté à la livraison, donc les deux points ne doublent pas l'IRQ.
Le main update continue au même PC immédiatement après le retour. Son ISR est exécutée intégralement par l'interpréteur MIPS natif, dans
une copie du CPU avec pile `801FF800`. Le thread principal ne change ni PC,
ni registres, ni pile, et ne doit plus atteindre `12C50` pour autoriser un IRQ.
Le service VBlank conserve la gestion native de la fin du SEQ et du script.

Les événements BIOS enregistrés/activés, I_STAT et I_MASK restent nécessaires.
Les callbacks CD/MDEC déjà actifs reportent la livraison. Aucun backlog d'IRQ
ni forçage d'opcode ou de statut musical n'est ajouté. L'ISR reste bornée à
100000 blocs ; un retour anormal arrête explicitement l'exécution au lieu de
laisser silencieusement une garde de réentrance coincée.

Le diagnostic `seq_delivery` compte les callbacks ayant réellement servi le
séquenceur, ceux refusés par ses gardes natives, et le maximum de durée ISR.
L'écran inférieur reste sans console de debug. La sortie audio n'est pas
corrigée par ce changement.

## Vérification

Le mode `host-timer` de `tools/replay_spu_snapshot.py` utilise la fonction de
livraison extraite du source de production, le vrai interpréteur et le vrai
backend mémoire/SPU. Il contrôle le CPU et les 768 octets supérieurs de la pile
principale avant/après chaque IRQ. Les appels de service/statut se font dans
une autre copie du CPU. La capture privée fournit le code et les données du
jeu ; aucun de ces octets n'est ajouté au dépôt.

| Capture | Rejeu | Résultat |
|---|---|---|
| B136.24 menu | callback natif en cours | retour en 291 blocs |
| B136.25 menu | callback natif en cours | retour en 302 blocs |
| B136.27 fin d'intro | livraison hôte + service natif final | 989 IRQs, canal terminé et flag 80 effacé |
| B136.30 fin d'intro | livraison hôte + service natif final | 374 IRQs, canal terminé et flag 80 effacé |
| B136.30 Simon Muran | une livraison hôte | retour en 101 blocs, CPU/pile préservés |

Le test déterministe ajoute 100 IRQs pendant que le PC principal reste à
`80081AEC` : aucune ne doit attendre `12C50`. Il contrôle les callbacks imbriqués,
la préservation du CPU complet, les erreurs et la borne d'exécution. Les tests
existants conservent la vérification BIOS/mask/acquittement et la garde MDEC.

Le rejeu active explicitement timer2 à sa frontière contrôlée : les captures
peuvent avoir I_MASK nul dans DrawSync. Ce n'est pas un rejeu complet d'Azahar,
ni une mesure de FPS ARM. À 60 intervalles/s, 374 intervalles représentent
6,23 s simulées restantes ; ce n'est pas une promesse de durée réelle. La
coalescence I_STAT, le masquage natif et les performances hôte subsistent.

Validation complète : démarrage neuf, Start, menu, nom, intro, puis dialogue
avec Simon Muran. Vérifier `probe=B136.31` et `seq_delivery` dans les fichiers.
