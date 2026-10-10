# B136.30 — cadence du timer SEQ

8 octobre 2026. Suite au test utilisateur B136.29 : `frame=4800`, opcode
`C011`, `seq_irq calls=279 done=279 active=0`, masque SPU `0000007F`.
Les callbacks reviennent, mais le script attend encore la fin du SEQ.

## Défaut de cadence

Le code natif `8004BCE4` configure le root counter 2 avec cible `E000` et
horloge système divisée par huit (`80073E98`, mode `0258`). Le port avançait
ce compteur de 4096 ticks par VBlank hôte. L'horloge PS1 est 33 868 800 Hz ;
`main.c` utilise le VBlank 3DS à 60 Hz. Le delta correspondant est donc
`33868800 / 60 / 8 = 70560`, et non 4096. L'ancienne horloge était 17,23 fois
trop lente. Le SEQ pouvait ainsi laisser plusieurs minutes d'attente après
la fin du texte, donnant l'impression que le jeu était bloqué.

La fréquence système de référence est aussi documentée dans le runtime
PSXRecomp épinglé, `runtime/include/interrupts.h` : 564480 cycles par intervalle
de 60 Hz. Le mode PAL d'affichage du jeu ne change pas le VBlank hôte 3DS.

## Changement

Timer2 avance désormais à 564480 ticks par VBlank pour la source système,
ou 70560 pour la source système/8. Timer0 et timer1 gardent leurs paramètres.
Les lectures COUNT restent sans effet de bord. Une traversée de plusieurs
tours du compteur détecte aussi correctement le passage par la cible.

Les IRQ restent coalescées dans I_STAT, avec respect d'I_MASK et du callback
BIOS enregistré. Aucun backlog de callbacks, saut d'opcode ou drapeau de
fin de SEQ n'est injecté. Le correctif de masque SPU B136.29 et sa protection
de reprise du thread principal sont conservés. Le quickstate reste en version 3.

## Validation et limites

Le mode `timed-sequence` de `tools/replay_spu_snapshot.py` utilise maintenant
`fm_memory_vblank_tick`, le timer sérialisé, l'IRQ timer2 et le séquenceur natif.
La capture peut contenir I_MASK=0 pendant DrawSync ; ce banc d'essai active
explicitement le bit timer2 à sa frontière de scheduler. Les mode/cible/count
sont ceux de la capture. Ce n'est pas un rejeu complet du dispatcher Azahar.

Sur la même capture de fin d'intro B136.27, avec les vrais accès SPU B136.29 :

| Cadence | Interruptions pour finir | Intervalles hôte | Durée simulée à 60 Hz |
|---|---:|---:|---:|
| B136.29 | 989 | 13833 | 230,55 s |
| B136.30 | 989 | 989 | 16,48 s |

Dans les deux cas, le canal termine et le service natif efface lui-même le
drapeau `0x80`. Un maximum d'un IRQ est livré par intervalle dans ce rejeu,
d'où la coalescence lorsque le compteur atteint sa cible plusieurs fois.
Ces durées ne sont pas une promesse de durée réelle dans Azahar : le coût du
rendu et les frontières de livraison du dispatcher peuvent la rallonger.

Les tests host CLEAN et PROFILE contrôlent une seconde de ticks pour les
deux sources, les lectures COUNT stables, la cadence IRQ avec cible E000 et
une traversée de cible après plusieurs tours. Le diagnostic ajoute
`seq_state` (statut, canal terminé, position, délai, flags moteur) et
`seq_timer` (count/mode/target/IRQ/mask), sans lecture MODE destructive.

Retester depuis le démarrage : menu, nom, intro, puis transition vers le jeu.
Le parcours complet reste à confirmer dans Azahar. Aucun rendu audio ou gain
FPS n'est annoncé par cette correction de timer.
