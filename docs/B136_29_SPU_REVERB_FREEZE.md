# B136.29 — boucle SPU reproduite avec les quickstates

8 octobre 2026. Branche : `fix/b136-spu-dma4-mmio-audit`.

## Cause

B136.27 laisse le séquenceur SEQ sans interruptions périodiques : la fin de
l'intro attend l'effacement du bit `0x80` du moteur audio (`801E0000+40`).
L'opcode `C011` dans `8002F898` reste donc en attente, même après la fin du texte.

B136.28 rétablit le callback natif `8004BBC4`, mais celui-ci atteint une autre
attente dans `8004B6D8` : `80076DB8(1, masque)` programme les registres SPU
`1F801D98/1F801D9A`, puis `800770A8` relit le masque jusqu'à observer le bit.
Le backend ne gérait ni ces écritures SH ni ces lectures LHU. Les écritures
étaient ignorées et les lectures renvoyaient zéro. Cette boucle ne peut pas
sortir, même avec un dispatcher entièrement natif.

Le test antérieur sur un tableau MMIO générique était insuffisant : ce tableau
mémorisait les écritures, contrairement au backend réel. Le rejeu utilise
maintenant **fm_memory.c + fm_interp.c de production**, l'état SPU/timers du
quickstate et les instructions du jeu présentes dans sa RAM.

## Correction

- Ajouter le masque SPU de réverbération, 24 bits, avec accès byte/half/word
  cohérents, aliases physiques/KSEG et remise à zéro à l'initialisation.
- Conserver l'exécution native complète du callback introduite en B136.28.
- Laisser le dispatcher exécuter l'entrée interrompue après le retour du
  callback, avant d'accepter un timer redevenu pending pendant son exécution.
- Sérialiser le nouveau registre. Le quickstate passe en version 3 ; les
  anciennes captures version 2 restent utilisables par l'outil de rejeu,
  mais ne doivent pas être chargées dans le jeu B136.29. Retester depuis un boot.

Aucun opcode du script, drapeau de fin de musique ou état du menu n'est forcé.
Le rendu et le décodage XA/STR ne sont pas modifiés.

## Résultats reproductibles

`tools/replay_spu_snapshot.py <capture> menu|sequence` compile le vrai backend
et l'interpréteur. Il ne rejoue que le chemin sonore, pas toute la boucle Azahar.
Les dépendances GPU/GTE hors sujet font échouer le test si elles sont utilisées.
Les fichiers privés fournissent les instructions ; aucune RAM du jeu n'est
incluse dans le dépôt.

| Capture | Backend B136.28 | Backend B136.29 |
|---|---|---|
| Menu B136.24 | Attente de masque non prise en charge | Retour du callback en 291 blocs |
| Menu B136.25 | Toujours en boucle après 100 000 blocs | Retour du callback en 302 blocs |
| Fin d'intro B136.27 | Boucle SPU dès le 8e callback | SEQ terminé après 989 callbacks ; canal=1, flags moteur=0000 |

Les deux retours menu atteignent la vraie sentinelle `8000FFD0` sauvegardée sur
leur pile ; le masque relu vaut `00000003`. Le statut SEQ final vaut 3 et le
service natif `800463F8` efface lui-même le bit `0x80` attendu par le script.

Les tests host CLEAN/PROFILE ajoutent une boucle MIPS synthétique de
programmation/relecture du masque, des accès mixtes, reset et quick-save/load.
Le test du bridge vérifie aussi qu'un timer pending n'interrompt pas à nouveau
la même entrée restaurée avant qu'elle ait progressé.

Limite : ce rejeu prouve la sortie de ces attentes, pas le parcours complet
menu → nouvelle partie → intro → jeu dans Azahar. Celui-ci reste à confirmer
sur le build B136.29. La sortie audio et la cadence des timers restent des
sujets séparés ; ce correctif n'annonce aucun gain FPS ni son audible.
