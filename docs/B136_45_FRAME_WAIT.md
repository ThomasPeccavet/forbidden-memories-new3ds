# B136.45 — attente 80012CD4

La boucle charge `lbu v1,0x18c(gp)` et `lw v0,0x190(gp)`, puis revient à
80012CD4 tant que `(int32_t)frame_done < (int32_t)(uint8_t)frame_target`.
Les adresses attendues sont 8009C428 et 8009C424. Le compteur -1 attend donc
même une cible 0. Les six instructions et le GP sont vérifiés à chaque arrêt.

Le checkpoint effectue son service VBlank habituel **avant** cette lecture.
Lorsque la condition attend encore, une sonde explicitement désignée comme
principale retourne FRAME_WAIT. Le host suspend sa tranche et garde le PC
exact. Au prochain passage, le même checkpoint sert les IRQ pendantes et
réévalue la condition. Les sondes isolées de callbacks ne sont pas désignées.
Aucun compteur, registre général, pile ou horloge n'est modifié par ce test.
Le marqueur host est remis à zéro au quick-load et à la reprise d'une sonde.
Une fin de budget ne force plus une reprise immédiate pendant FRAME_WAIT.

`frame_wait` contient des deltas par fenêtre : stops (retours FRAME_WAIT),
resumes (sondes qui repartent), active (marqueur host), target_probes et
`target_probe_us` (temps complet de toutes les sondes entrées à 12CB8/12CD4).
Le temps de ces sondes inclut leur travail normal : ce n'est pas un calcul
de temps CPU économisé. Les arrêts internes issus d'une autre entrée sont
comptés dans stops, mais pas dans target_probe_us.

Validation : tests hôte du checkpoint réel et du rapport de fenêtres ;
gardes code/GP, compteur signé, égalité, contexte inchangé, VBlank avant
suspension, priorité sur le watchdog et exclusion des autres CPUs.
La compilation ARM est vérifiée par CI. Ni le combat complet ni les FPS
Azahar ne peuvent être validés dans cet environnement.

Comparer le même combat avec B136.44, au repos puis pendant une animation,
20 secondes par situation. Garder PROFILE=1 UNAI=1. Examiner new_images_fps,
pre_guest_input, frame_wait et dma2_nested_ms. Aucun objectif de 30 FPS
n'est garanti par cette seule suppression d'attente active.
