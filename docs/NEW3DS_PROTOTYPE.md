# Prototype natif New 3DS — état du 17 septembre 2026

Le prototype n'est pas encore un jeu jouable, mais il exécute désormais réellement le code français avec une architecture hybride ARM11 + R3000A.

## Ce que fait le backend 3DS

- application native libctru ;
- accélération New 3DS ;
- lecture du BIN français MODE2/2352 depuis SD ;
- chargement du PS-X EXE à `0x80010000` ;
- CPUState PSXRecomp, RAM 2 Mio, scratchpad et alias KSEG ;
- code résident généré par PSXRecomp et recompilé pour ARM11 ;
- dispatcher statique ;
- fallback R3000A pour les blocs inconnus ;
- HLE BIOS partiel ;
- bridge GP0/GP1 et wrappers BIOS GPU ;
- rasteriseur logiciel PSXRecomp compilé pour ARM11 ;
- diagnostics CPU/BIOS/MMIO/GPU/interpréteur sur l'écran inférieur.

## Architecture

```text
EXE français
   |
   v
CPUState + RAM PS1
   |
   v
Dispatcher ARM11
   |\
   | \ adresse inconnue
   |  v
   |  R3000A fallback
   |  |
   +--+
      |
      v
 BIOS HLE / MMIO
      |
      +--> GPU GP0/GP1 --> software renderer --> VRAM --> écran supérieur
      |
      +--> IRQ/CD/etc. à compléter
```

Le fallback R3000A a déjà été observé en fonctionnement dans Azahar : une destination non recompilée est exécutée par basic block puis le contrôle revient au dispatcher.

## GPU

`fm_gpu.c` parse déjà des commandes GP0 : environnement de dessin, polygones, lignes, rectangles/sprites, transferts CPU→VRAM, VRAM→VRAM et listes liées BIOS.

Les accès `0x1F801810` et `0x1F801814` sont routés depuis `fm_memory.c` vers GP0/GP1. Les appels BIOS GPU A0:46..4E passent par `fm_gpu_bios_call`.

Un bug de retour BIOS GPU a été corrigé : les handlers remettent maintenant `cpu->pc` à `$ra`. Avant correction, A0:49 se répétait et gonflait artificiellement le compteur GP0 à environ 90 000 mots ; après correction, le même stade du boot montre environ 4 mots GP0.

Le dernier test affiche encore `Frame VRAM = NON` : aucune image réelle du jeu n'est encore présentée.

## BIOS / kernel

Le shim couvre actuellement les services nécessaires déjà rencontrés :

```text
A0:72  _96_remove
A0:9F  SetMem
B0:18  ResetEntryInt
B0:19  HookEntryInt
B0:35  write
B0:56  GetC0Table
B0:57  GetB0Table
B0:5B  ChangeClearPAD
C0:02  SysEnqIntRP
C0:03  SysDeqIntRP
C0:0A  ChangeClearRCnt
A0:46..4E GPU family
```

Le prochain appel observé est `A0:44 FlushCache`.

## MMIO / IRQ

Le dernier MMIO observé est `0x1F801074`, soit `I_MASK`. `I_STAT`/`I_MASK` et un VBlank minimal sont donc les prochains éléments kernel/hardware prioritaires.

## Compilation

Prérequis : devkitPro `3ds-dev`, Git, Python 3.11+ et PSXRecomp épinglé à :

```text
1965b2df424da03483a5370340433a862f78f103
```

Depuis la racine :

```sh
git clone https://github.com/Unchiga/psxrecomp.git work/upstream-psxrecomp
git -C work/upstream-psxrecomp checkout 1965b2df424da03483a5370340433a862f78f103
export PATH=$DEVKITARM/bin:$PATH
make -C 3ds clean
make -C 3ds PSXRECOMP_ROOT=../work/upstream-psxrecomp -j4
```

Le build utilise aussi :

```text
work/arm-generated-objects/fm-generated-combined.o
```

qui doit être généré localement à partir des shards français et ne doit pas être versionné.

Sorties :

```text
3ds/fm-new3ds.elf
3ds/fm-new3ds.3dsx
```

## Azahar

Le disque est attendu à :

```text
sdmc:/3ds/fm-new3ds/disc.bin
```

Commandes principales :

| Bouton | Action |
| --- | --- |
| A | RUN / PAUSE |
| B | RESET JEU |
| START + SELECT | Quitter |

L'écran inférieur affiche le dernier PC, les registres, le dernier MMIO, le résultat du dispatcher, l'état du fallback R3000A et les compteurs GPU.

## Limites actuelles

- aucune image réelle de Forbidden Memories sur l'écran supérieur ;
- IRQ/VBlank incomplets ;
- DMA GPU à fiabiliser ;
- contrôleur CD asynchrone incomplet ;
- GTE complet absent ;
- audio/SPU/XA absents ;
- sauvegarde absente ;
- pas encore de validation sur New 3DS physique.

Voir [CURRENT_STATUS.md](CURRENT_STATUS.md) et [ACTION_PLAN.md](ACTION_PLAN.md) pour la suite.
