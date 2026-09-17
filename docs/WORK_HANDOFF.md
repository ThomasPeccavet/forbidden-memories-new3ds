# Handoff pour ChatGPT Work / nouvelle session

Ce document condense le contexte nécessaire pour reprendre le chantier sans relire toute l'historique.

## Objectif

Porter **Yu-Gi-Oh! Forbidden Memories PAL France SLES-03948** sur **New Nintendo 3DS** en utilisant PSXRecomp pour le code résident, un fallback R3000A pour le code non couvert et un runtime 3DS natif libctru.

## Révision PSXRecomp

```text
Unchiga/psxrecomp
1965b2df424da03483a5370340433a862f78f103
```

Ne pas changer cette révision sans raison explicite : tout le code généré et les hypothèses actuelles s'y réfèrent.

## Fichiers importants

```text
3ds/Makefile
3ds/include/fm_cpu.h
3ds/include/fm_memory.h
3ds/include/fm_runtime_shim.h
3ds/include/fm_interp.h
3ds/include/fm_gpu.h
3ds/source/main.c
3ds/source/fm_cpu.c
3ds/source/fm_memory.c
3ds/source/fm_runtime_shim.c
3ds/source/fm_interp.c
3ds/source/fm_gpu.c
3ds/source/disc.c
3ds/source/platform.c
tools/bootstrap_pc.py
```

Objet généré local attendu par le build 3DS :

```text
work/arm-generated-objects/fm-generated-combined.o
```

Le code C généré du jeu et cet objet ne doivent pas être commités.

## Données du jeu

```text
SLES        : SLES-03948
BIN taille  : 548427600
BIN SHA-256 : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
EXE SHA-256 : 57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44
Load        : 0x80010000
Entry       : 0x800128CC
Stack       : 0x801FFFF0
```

Chemin runtime actuel :

```text
sdmc:/3ds/fm-new3ds/disc.bin
```

## Architecture d'exécution

1. `disc.c` charge le PS-X EXE dans une RAM PS1 de 2 Mio.
2. `fm_cpu.c` initialise `CPUState`.
3. le dispatcher PSXRecomp tente le code ARM11 statique ;
4. si l'adresse n'est pas connue, `fm_interp.c` exécute un basic block R3000A ;
5. le nouveau PC revient vers le dispatcher ;
6. les vecteurs BIOS A0/B0/C0 passent par `fm_runtime_shim.c` ;
7. les ports GPU et appels BIOS GPU passent par `fm_gpu.c` ;
8. le rasteriseur logiciel PSXRecomp écrit dans une VRAM 1024x512 RGB555 ;
9. `main.c` présente la VRAM / les diagnostics avec libctru.

## HLE BIOS déjà implémenté

- A0:72 `_96_remove`
- A0:9F `SetMem`
- B0:18 `ResetEntryInt`
- B0:19 `HookEntryInt`
- B0:35 `write`
- B0:56 `GetC0Table`
- B0:57 `GetB0Table`
- B0:5B `ChangeClearPAD`
- C0:02 `SysEnqIntRP`
- C0:03 `SysDeqIntRP`
- C0:0A `ChangeClearRCnt`
- A0:46..4E via `fm_gpu_bios_call`

Le shim prépare également `C0[6] = 0x00000C80` quand les tables BIOS sont demandées.

## Bug GPU récemment corrigé

Les handlers BIOS GPU exécutaient leur service puis retournaient `1` sans remettre `cpu->pc` à `$ra`. Le jeu restait donc sur A0:49 et envoyait artificiellement environ 90 000 mots GP0.

La correction applique après chaque appel GPU reconnu :

```c
cpu->pc = cpu->gpr[31];
cpu->gpr[0] = 0;
```

Après correction, le même stade du boot montre environ **4 mots GP0**, preuve que le chemin continue normalement.

## Dernier état observé

```text
PC          : 000000A0
RA          : 80089B38
A0          : 00000001
A1          : 800FF444
A2          : 00000000
T1          : 00000044
RUN         : NON
Stop ARM    : RETURN
Dispatch    : 000000A0 / 1
R3000A      : utilisé
Stop interp : BLOCK
GP0 words   : 4
Frame VRAM  : NON
Display XY  : 0,0
GPUSTAT     : 1C802000
Static miss : OUI
Last MMIO   : 1F801074
```

Interprétation immédiate : le prochain service BIOS est **A0:44 `FlushCache`**. Le dernier MMIO `0x1F801074` est **I_MASK**.

## Prochaine séquence de travail

1. ajouter A0:44 `FlushCache` avec retour propre vers `$ra` ;
2. relancer Azahar et noter le prochain arrêt ;
3. implémenter I_STAT `0x1F801070` et I_MASK `0x1F801074` ;
4. générer un VBlank minimal ;
5. ajouter diagnostics détaillés GPU ;
6. vérifier DMA2 / linked-list ;
7. atteindre `Frame VRAM = OUI` ;
8. afficher la vraie VRAM à la place de la primitive de démonstration.

Voir `docs/ACTION_PLAN.md` pour les étapes suivantes.

## Commandes build

```sh
export PATH=$DEVKITARM/bin:$PATH
make -C 3ds clean
make -C 3ds PSXRECOMP_ROOT=../work/upstream-psxrecomp -j4
```

Sorties :

```text
3ds/fm-new3ds.elf
3ds/fm-new3ds.3dsx
```

## Discipline de validation

- Azahar est actuellement le banc de test principal ;
- le matériel New 3DS physique n'est pas encore validé ;
- ne pas considérer une absence de crash comme une émulation correcte ;
- ne pas transformer un appel GTE/CD/IRQ inconnu en no-op sans preuve ;
- conserver les valeurs PC/RA/A0-A3/T1/Last MMIO à chaque blocage ;
- commit/push après chaque jalon qui compile et produit un diagnostic reproductible.
