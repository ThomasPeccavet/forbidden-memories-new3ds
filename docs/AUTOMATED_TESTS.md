# Tests automatisés et discipline de bring-up

Dernière mise à jour : **29 septembre 2026**.

Cette infrastructure réduit les cycles manuels et complète désormais les tests
Azahar/3DS par des traces persistantes sur SD.

## 1. Validation rapide de main.c

~~~sh
python tools/validate_main_c.py 3ds/source/main.c
~~~

Le script vérifie notamment :
- doublons de `case` ;
- définitions static dupliquées ;
- marqueurs de conflit Git ;
- cohérence structurelle de `main.c`.

À lancer avant un build important.

## 2. Suite de checks locale

~~~sh
python tools/run_static_checks.py
~~~

Elle exécute les vérifications ne nécessitant pas le disque complet ni Azahar.

## 3. Validation SU.MRG

~~~sh
python tools/validate_su_layout.py /chemin/vers/disc.bin
~~~

Version rapide :

~~~sh
python tools/validate_su_layout.py /chemin/vers/disc.bin --skip-disc-hash
~~~

Découpage connu de `FUN_8006B350` :

~~~text
+0x00000  0x20000
+0x20000  0x10000
+0x30000  0x01000  -> 0x801DD000
+0x31000  0x08000  -> 0x80180000
+0x39000  0x00800  -> 0x801AF800
~~~

## 4. Build profil de diagnostic

Depuis `3ds` :

~~~sh
git pull
make clean
make PROFILE=1 -j4
~~~

Le profil conserve les compteurs B135/B136.

## 5. Traces persistantes

Deux fichiers sont prioritaires :

~~~text
sdmc:/3ds/fm-new3ds/debug-latest.txt
sdmc:/3ds/fm-new3ds/memory-watch.txt
~~~

### debug-latest.txt

Contient notamment :
- startup checkpoints ;
- C460/C484 ;
- requête CD ;
- compteurs DataReady/CdGetSector ;
- gate TestEvent ;
- état BIOS event ;
- producteurs événement ;
- état DMA4 ;
- état SPU ;
- pointeurs de transfert.

### memory-watch.txt

Journalise les écritures ciblées sur des mots guest critiques.

Le watcher B136 a été filtré pour éviter que les écritures VSync sur `C428`
écrasent les événements intéressants.

## 6. Test B136 actuel

Après le nouveau modèle SPU, contrôler :

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

Critère de premier succès :

~~~text
dma4_chcr_writes > 0
dma4_transfers > 0
dma4_event_bridge > 0
~~~

Puis vérifier la progression du ReadN.

## 7. GitHub Actions

`.github/workflows/static-checks.yml` exécute les checks ne nécessitant ni le
disque du jeu ni devkitPro.

Le disque n'est jamais envoyé en CI.

## 8. Ce qui reste manuel

Azahar ou matériel restent nécessaires pour :
- boot complet ;
- transitions visuelles ;
- pad ;
- timing ;
- vérification du rendu ;
- collecte des TXT du run.

## 9. Règle de validation

Pour chaque changement matériel important :

1. formuler l'hypothèse ;
2. ajouter une trace TXT ;
3. compiler PROFILE ;
4. tester ;
5. comparer les compteurs ;
6. documenter la conclusion ;
7. seulement ensuite modifier le modèle suivant.

Voir [B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).
