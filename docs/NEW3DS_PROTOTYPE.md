# Prototype natif New 3DS — état du 29 septembre 2026

Le prototype a déjà exécuté de nombreux écrans réels du jeu dans les séries B135,
mais le travail courant se concentre sur un démarrage plus fidèle et moins
dépendant des bypass.

## Backend actuel

- libctru / ARM11 ;
- BIN MODE2/2352 depuis SD ;
- PS-X EXE à `0x80010000` ;
- RAM PS1 2 Mio + scratchpad + alias KSEG ;
- code résident PSXRecomp ;
- dispatcher natif ;
- fallback R3000A ;
- BIOS HLE partiel ;
- événements BIOS Open/Enable/Test ;
- VBlank / IRQ de bring-up ;
- CD sector reader + requêtes async ;
- GPU GP0/GP1 ;
- DMA2 GPU ;
- DMA6 OTC ;
- DMA4 SPU minimal ;
- SPU contrôle/status minimal ;
- rasteriseur logiciel ;
- overlays dynamiques en RAM guest ;
- diagnostics persistants TXT sur SD.

## Architecture actuelle

~~~text
EXE + CD
   |
   v
CPUState / RAM
   |
   +--> code ARM11 recompilé
   |
   +--> fallback R3000A
   |
   v
BIOS / events / IRQ
   |
   +--> CD
   |
   +--> DMA
   |     +--> DMA2 GPU --> GP0 --> rasteriseur --> VRAM
   |     +--> DMA4 SPU --> event sync
   |     +--> DMA6 OTC
   |
   +--> SPU MMIO minimal
~~~

## État historique validé

Dans différentes branches B135, le backend a déjà atteint :
- Konami ;
- écran titre ;
- menu principal ;
- nouvelle partie ;
- saisie du nom ;
- dialogues ;
- carte ;
- duel.

Ces jalons restent importants comme référence fonctionnelle.

## Verrou actuel

Le startup courant bloque avant le chargement SU final.

Chaîne :

~~~text
FUN_80043CD4
 -> FUN_80014478
 -> FUN_800777D8
 -> TestEvent(F1000000)
 -> event F0000009/0x20
 -> SPU sync
 -> DMA4
 -> ReadN
~~~

La cause racine immédiate est documentée ici :
[B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).

## SPU minimal

Le runtime ne modélisait jusque-là aucun registre SPU utile à Psy-Q.

Ajout courant :

~~~text
1F801DA6 transfer address
1F801DA8 transfer data
1F801DAA control
1F801DAE status
~~~

Le but n'est pas encore de produire de l'audio. Le modèle sert uniquement à
reproduire les transitions de contrôle nécessaires aux wait loops du jeu et à la
programmation DMA4.

## DMA4 minimal

Ajout :

~~~text
1F8010C0 MADR
1F8010C4 BCR
1F8010C8 CHCR
~~~

Avec :
- START ;
- completion synchrone de bring-up ;
- flag DICR canal 4 ;
- compteur de completion ;
- bridge vers l'événement BIOS exact.

## Diagnostics

Référence :

~~~text
sdmc:/3ds/fm-new3ds/debug-latest.txt
sdmc:/3ds/fm-new3ds/memory-watch.txt
~~~

La règle est désormais de préférer les traces persistantes aux captures écran
pour tout diagnostic d'état interne.

## Build profil

Depuis `3ds` :

~~~sh
git pull
make clean
make PROFILE=1 -j4
~~~

Pour reconstruire aussi les shards générés :

~~~sh
cd ..
bash rebuild_generated_release.sh
make -C 3ds clean
make -C 3ds PROFILE=1 -j4
~~~

## Limites

- modèle SPU minimal non encore validé ;
- audio absent ;
- XA absent ;
- plusieurs bridges de bring-up subsistent ;
- performance encore insuffisante dans certaines scènes ;
- sauvegarde absente ;
- pas de validation complète New 3DS physique.

Voir [CURRENT_STATUS.md](CURRENT_STATUS.md) et [ACTION_PLAN.md](ACTION_PLAN.md).
