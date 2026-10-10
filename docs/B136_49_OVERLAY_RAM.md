# B136.49 — mémoire des overlays et scratchpad

B136.48 a amélioré la fluidité ressentie en combat. Le build conseillé avait
également changé de PROFILE=1 à PROFILE=0 : impossible d'attribuer le gain
à la seule optimisation des callbacks mémoire.

## Suite

Les helpers 16/32 bits de B136.48 sont déplacés dans fm_ram_access.h et
réutilisés par fm_interp.c pour les données et les instructions. L'ancien
memcpy de l'interpréteur ne communiquait pas explicitement l'alignement
à GCC ARM11 ; le nouveau chemin le vérifie puis le fournit au compilateur.
La lecture non alignée reste effectuée par octets, sans accès ARM invalide.

Les six callbacks byte/half/word passent par un accès direct au scratchpad
avant les tests timers/SPU/DMA. Le contrôle de largeur conserve les rejets
d'accès traversant sa limite de 1 Ko. Le chemin RAM byte passe également
avant les tests SPU/CD ; ces plages ne se recouvrent pas.

## Vérification

Les tests exécutent le module mémoire et l'interpréteur réels en PROFILE=0
et PROFILE=1 : programme MIPS avec LW/SW/LHU/SH/LBU/SB, quatre alignements
du tampon hôte, aliases scratchpad, adresses alignées et non alignées,
derniers octets valides et dépassement de limite. Les tests RAM/MMIO de
B136.48 et les autres tests restent requis.

Aucun changement d'horloge, aucune image sautée. Le build de comparaison
reste PROFILE=0 UNAI=1 ; la quickstate de combat corrigée est réutilisable.
Le gain FPS n'est pas chiffré avant validation du jeu dans Azahar.
