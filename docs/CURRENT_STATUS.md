# État courant — New Nintendo 3DS

Dernière mise à jour : **17 septembre 2026**.

## Résumé

Le port New 3DS exécute désormais la version française avec une architecture hybride : code résident recompilé en ARM11 lorsque disponible, fallback R3000A pour les blocs inconnus, HLE BIOS partiel et bridge GPU PS1 vers le rasteriseur logiciel.

Le jeu n'est pas encore visible à l'écran supérieur, mais le boot avance réellement dans Azahar et ne dépend plus d'une régénération des seeds à chaque appel indirect.

## Ce qui fonctionne

- chargement du BIN français SLES-03948 depuis la SD virtuelle ;
- chargement du PS-X EXE en RAM PS1 ;
- CPUState PSXRecomp, registres, RAM 2 Mio, scratchpad et alias KSEG0/KSEG1 ;
- code C généré recompilé en ARM11 et lié dans `fm-new3ds.elf` ;
- dispatcher statique ;
- fallback R3000A par basic block ;
- plusieurs appels BIOS HLE nécessaires au démarrage ;
- appels BIOS GPU A0:46..4E routés vers `fm_gpu.c` ;
- GP0/GP1 MMIO routés vers le bridge GPU ;
- rasteriseur logiciel PSXRecomp compilé sur ARM11 ;
- diagnostics temps réel sur écran inférieur.

## BIOS déjà couvert dans le shim

Couverture actuelle utilisée pendant le boot :

- A0:72 `_96_remove` ;
- A0:9F `SetMem` ;
- B0:18 `ResetEntryInt` ;
- B0:19 `HookEntryInt` ;
- B0:35 `write` ;
- B0:56 `GetC0Table` ;
- B0:57 `GetB0Table` ;
- B0:5B `ChangeClearPAD` ;
- C0:02 `SysEnqIntRP` ;
- C0:03 `SysDeqIntRP` ;
- C0:0A `ChangeClearRCnt` ;
- famille GPU A0:46..4E via `fm_gpu_bios_call`.

Cette liste n'est pas un objectif de couverture exhaustive : chaque service doit être implémenté seulement avec la sémantique nécessaire et vérifiable.

## Dernier état observé dans Azahar

Après ajout de `B0:56/GetC0Table`, le boot atteint désormais :

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

Le point courant est donc **A0:44 `FlushCache`**, tandis que le dernier MMIO observé est `0x1F801074` (**I_MASK**).

## Progrès GPU récent

Une boucle artificielle sur A0:49 avait fait monter le compteur GP0 à environ 90 000 mots. La cause était l'absence de retour vers `$ra` dans les handlers BIOS GPU. Après correction, le compteur retombe à **4 mots** au même stade du boot, ce qui confirme que le jeu poursuit désormais son chemin au lieu de répéter le même appel.

Le bridge GPU sait déjà parser de nombreuses commandes GP0 : polygones, lignes, rectangles, transferts VRAM, environnement de dessin et linked lists BIOS. La condition `Frame VRAM` reste toutefois à NON dans le dernier test : aucune écriture réellement visible n'a encore été confirmée.

## Verrous immédiats

1. implémenter A0:44 `FlushCache` comme service HLE minimal correct ;
2. ajouter un modèle cohérent de `I_STAT` / `I_MASK` ;
3. injecter un VBlank minimal et vérifier les attentes IRQ ;
4. fiabiliser DMA2 / linked-list GPU hors des seuls wrappers BIOS ;
5. confirmer la première écriture VRAM ;
6. présenter la vraie zone d'affichage PS1 sur l'écran supérieur ;
7. poursuivre vers les premiers overlays `0x801xxxxx` réellement chargés.

## Ce qui n'est pas encore validé

- menu New 3DS rendu par le jeu ;
- contrôleur CD asynchrone complet ;
- GTE complet ;
- audio SPU/XA ;
- sauvegarde ;
- performance sur matériel physique ;
- duel jouable sur New 3DS.

Le runtime PC reste la preuve fonctionnelle de référence pour le menu, l'introduction et le premier duel ; le backend 3DS reste un chantier distinct.
