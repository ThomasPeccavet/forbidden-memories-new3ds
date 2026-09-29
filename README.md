# Yu-Gi-Oh! Forbidden Memories — New Nintendo 3DS

Projet expérimental de portage/recompilation de **Yu-Gi-Oh! Forbidden Memories**
(version française **PAL SLES-03948**) vers **New Nintendo 3DS**.

> [!IMPORTANT]
> Le port n'est pas encore jouable de bout en bout. Le projet a néanmoins déjà
> exécuté une partie importante du vrai jeu sur le backend 3DS : boot PS1,
> chargements CD, GPU logiciel, menu principal, saisie du nom, dialogues, carte
> et duel dans plusieurs branches de bring-up.
>
> Au **29 septembre 2026**, le travail actif est revenu sur le démarrage fidèle
> afin de supprimer les bypass accumulés et reconstruire la chaîne matérielle
> correcte. Le verrou actuel est maintenant identifié très précisément :
> **synchronisation SPU / DMA4 / événement BIOS avant un ReadN CD**.

## État du projet — 29 septembre 2026

| Partie | État actuel |
| --- | --- |
| Profil PAL France / SLES-03948 | ✅ Vérifié |
| PS-X EXE / Ghidra | ✅ 1546 fonctions exportées, overlays étudiés |
| Runtime PC | ✅ Jusqu'au premier duel |
| Build natif New 3DS | ✅ ARM11 / devkitARM / libctru |
| Code résident recompilé | ✅ |
| Fallback R3000A | ✅ |
| BIOS PAL region | ✅ BFC7FF52 = 0x45 restauré |
| VBlank / service loop | ✅ Chemin startup actif |
| CD-ROM / secteurs | 🟡 Pipeline fonctionnel, nouvelle requête encore bloquée |
| GP0 / GP1 / rasteriseur | ✅ Chemins rendus déjà validés |
| DMA2 / DMA6 | ✅ Modèle existant |
| DMA4 / SPU | 🟡 Modèle minimal ajouté, test matériel logique en attente |
| Événements BIOS | 🟡 Open/Enable/Test fonctionnent ; synchronisation SPU en cours |
| Overlay SU | ✅ Analyse et exécution déjà validées |
| Menu / nouvelle partie / nom | ✅ Atteints dans les branches fonctionnelles |
| Dialogues / carte / duel | ✅ Atteints dans les branches B135 précédentes |
| Performance | 🟡 Encore insuffisante dans plusieurs scènes |
| Audio SPU réel | ❌ Non implémenté |
| XA | ❌ Non implémenté |
| Sauvegarde / memory card | ❌ Non implémentée |

## Verrou actuel : startup CD → SPU → DMA4

Le boot passe correctement l'overlay PAL :

~~~text
801680F4 -> BIOS region BFC7FF52 = 45 ('E')
80168160 -> retour 0
~~~

Le startup entre ensuite dans le second `FUN_80043CD4` et y reste parce que :

~~~text
C460 = 01C00016
C484 = 00000000
~~~

La requête CD active est :

~~~text
remaining = 00002000
buffer    = 801E1639
LBA       = 0003172D
callback  = 80014A4C
flags/cmd = 01400006   ; ReadN
~~~

Le pipeline CD précédent est sain : 62 appels `CdGetSector`, 62 succès, aucun
échec. La nouvelle requête est construite correctement par `800142F8`, mais
`80014478` attend un événement BIOS avant de relancer le ReadN.

L'événement attendu est :

~~~text
handle = F1000000
class  = F0000009
spec   = 00000020
mode   = 00002000
~~~

`TestEvent` est appelé en boucle, mais l'événement n'est jamais READY.

Le diagnostic a ensuite remonté jusqu'au SPU :

~~~text
FUN_80075AFC(3, 801DC000, 0x200)
SPU base       = 1F801C00
DMA4 MADR ptr  = 1F8010C0
DMA4 BCR ptr   = 1F8010C4
DMA4 CHCR ptr  = 1F8010C8
SPU CTRL 1DAA  = 0000
SPU STAT 1DAE  = 0000
~~~

En mode 0, `FUN_80075AFC(3)` attend que les bits `0x30` du contrôle SPU
valent `0x20`. Comme le runtime ne modélisait aucun registre SPU, la routine
timeoutait **avant même de programmer DMA4**.

Le correctif courant ajoute :
- DMA4/SPU au contrôleur DMA ;
- completion DMA4 minimale ;
- bridge completion DMA4 → événement BIOS exact ;
- registres SPU minimaux `1F801DA6/DA8/DAA/DAE` ;
- miroir du mode de transfert attendu par Psy-Q.

**Ce correctif SPU minimal vient d'être intégré et doit encore être testé.**

Voir [docs/B136_STARTUP_CD_SPU_DMA4.md](docs/B136_STARTUP_CD_SPU_DMA4.md).

## Discipline de debug

Le diagnostic se fait désormais via fichiers persistants sur SD, pas uniquement
par captures écran :

~~~text
sdmc:/3ds/fm-new3ds/debug-latest.txt
sdmc:/3ds/fm-new3ds/memory-watch.txt
~~~

Chaque expérimentation importante doit laisser des compteurs ou traces TXT afin
de pouvoir comparer les runs sans perdre l'historique.

## Architecture

~~~text
SLES_039.48 / disc.bin
        |
        v
  PS-X EXE + CD
        |
        v
 CPUState / RAM PS1
        |
        v
 dispatcher hybride
   |             |
 ARM11       R3000A fallback
   \             /
    v           v
 BIOS / IRQ / events
        |
  +-----+------+-------+
  |            |       |
VBlank         CD     DMA
                      / \
                   GPU   SPU
                   DMA2  DMA4
                    |     |
                   GP0   sync
                    |
             rasteriseur SW
                    |
                   VRAM
~~~

## Compiler la branche de diagnostic

Depuis le dossier `3ds` :

~~~sh
git pull
make clean
make PROFILE=1 -j4
~~~

Le profil `PROFILE=1` conserve les diagnostics B135/B136 utilisés pendant le
bring-up.

Pour une reconstruction complète du code généré :

~~~sh
cd ..
bash rebuild_generated_release.sh
make -C 3ds clean
make -C 3ds PROFILE=1 -j4
~~~

PSXRecomp de référence :

~~~text
Unchiga/psxrecomp
1965b2df424da03483a5370340433a862f78f103
~~~

## Disque de test

~~~text
sdmc:/3ds/fm-new3ds/disc.bin
~~~

~~~text
Version        : PAL France / SLES-03948
Format         : BIN brut MODE2/2352
Taille         : 548 427 600 octets
SHA-256        : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
Load           : 0x80010000
Entry          : 0x800128CC
~~~

Aucun dump du jeu ni BIOS Sony n'est distribué par ce dépôt.

## Prochain test

Le prochain run doit vérifier que le modèle SPU permet enfin à
`FUN_80075AFC(3)` de programmer DMA4.

Les compteurs attendus sont notamment :

~~~text
spu_reg_1aa
spu_reg_1ae
dma4_madr_writes
dma4_bcr_writes
dma4_chcr_writes
dma4_last_chcr
dma4_transfers
dma4_event_bridge
req10
c460
post681_43dc8
post681_159f4
~~~

Le premier succès attendu est :

~~~text
dma4_chcr_writes > 0
dma4_transfers    > 0
dma4_event_bridge > 0
~~~

puis la requête `ReadN` à `LBA 0x3172D` doit commencer à progresser.

## Documentation

- [État courant](docs/CURRENT_STATUS.md)
- [Diagnostic B136 startup/CD/SPU/DMA4](docs/B136_STARTUP_CD_SPU_DMA4.md)
- [Plan d'action](docs/ACTION_PLAN.md)
- [Roadmap](docs/ROADMAP.md)
- [Handoff](docs/WORK_HANDOFF.md)
- [Index de la documentation](docs/README.md)

## Données du jeu et licences

**Aucun disque, BIOS PlayStation propriétaire, exécutable original ou contenu
propriétaire du jeu n'est distribué dans ce dépôt.**

Yu-Gi-Oh! et Forbidden Memories appartiennent à leurs ayants droit respectifs.
Ce projet de recherche et de portage n'est pas affilié à Konami.
