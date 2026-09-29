# Analyse française — observations vérifiées

Dernière mise à jour : **29 septembre 2026**.

Source principale : `profiles/SLES-03948.json`, analyses Ghidra, runtime PC,
backend New 3DS et traces B135/B136.

| Paramètre | Valeur |
| --- | --- |
| Programme de démarrage | SLES_039.48 |
| Taille du programme | 1 902 592 octets |
| Charge utile hors en-tête | 1 900 544 octets |
| Chargement | `0x80010000` |
| Fin exclusive | `0x801E0000` |
| Point d'entrée | `0x800128CC` |
| Pile | `0x801FFFF0` |
| GP | `0x8009C298` |
| SHA-256 EXE | `57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44` |
| SHA-256 BIN | `9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835` |

## Code résident et overlays

Le code résident français est recompilé en ARM11. Les destinations dynamiques et
overlays restent exécutables via fallback R3000A.

Une même adresse `0x801xxxxx` peut contenir différentes images au cours du jeu.
Toute recompilation d'overlay doit donc être liée au contenu réellement chargé,
pas seulement à l'adresse.

## Runtime PC

Le runtime PC reste l'oracle fonctionnel historique :
- menu principal ;
- nouvelle partie ;
- introduction ;
- premier duel contre Simon Muran ;
- carte posée ;
- tour terminé.

## Backend New 3DS — faits récents

Le backend a déjà atteint plusieurs de ces jalons dans les séries B135.

Le travail B136 a ensuite reconstruit le startup bas niveau.

### Région BIOS PAL

Le code overlay lit :

~~~text
BFC7FF52
~~~

et compare à :

~~~text
0x45 ('E')
~~~

Le runtime fournit maintenant cette valeur correctement.

### Requête CD actuelle

Requête bloquée :

~~~text
LBA       = 0x3172D
remaining = 0x2000
buffer    = 0x801E1639
cmd       = 0x06
callback  = 0x80014A4C
~~~

Le pipeline précédent a produit 62 lectures secteur réussies sans échec.

### Événement BIOS

Handle :

~~~text
F1000000
~~~

Métadonnées :

~~~text
class=F0000009
spec=00000020
mode=00002000
~~~

Le jeu le teste via `TestEvent` mais il restait non READY.

### SPU / DMA4

`FUN_80075AFC(3)` est réellement appelée et les pointeurs DMA4 correspondent
bien aux registres PS1 :

~~~text
1F8010C0
1F8010C4
1F8010C8
~~~

Mais la routine attend d'abord l'état SPU :

~~~text
(SPU+0x1AA) & 0x30 == 0x20
~~~

Trace avant modèle SPU :

~~~text
spu_base=1F801C00
spu_mode=0
spu_reg_1aa=0000
spu_reg_1ae=0000
~~~

Ce wait explique directement pourquoi aucun store DMA4 n'était encore observé.

## Matériel actuellement modélisé

### GPU
- GP0 ;
- GP1 ;
- DMA2 ;
- DMA6 OTC ;
- rasteriseur logiciel ;
- VRAM.

### CD
- lecture sectors MODE2/2352 ;
- requêtes async de bring-up ;
- DataReady/CdGetSector ;
- plusieurs callbacks réels.

### BIOS
- jump tables partielles ;
- événements ;
- VBlank minimal ;
- pad.

### SPU
Modèle de synchronisation minimal uniquement :
- transfer address ;
- transfer data ;
- control ;
- status ;
- DMA4 minimal.

Aucun mixage audio réel n'est encore implémenté.

## Archives

Ont été inventoriés :
- SU.MRG ;
- SD_SE.DAT ;
- SD_BGM.DAT ;
- WA_MRG.MRG ;
- MODEL.MRG ;
- MASTER.XA ;
- MOVIE.STR.

Les flux XA/STR demanderont un chemin spécifique.

## Prudence

Ne jamais :
- appliquer un delta uniforme entre symboles US/FR ;
- considérer une adresse overlay comme une fonction permanente ;
- interpréter un bridge de bring-up comme comportement matériel définitif ;
- forcer un état guest lorsqu'une chaîne matérielle peut être reconstruite.

## Documents liés

- [CURRENT_STATUS.md](CURRENT_STATUS.md)
- [B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md)
- [ACTION_PLAN.md](ACTION_PLAN.md)
- [SU_LOADING_TRACE.md](SU_LOADING_TRACE.md)
- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)
