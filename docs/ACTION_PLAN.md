# Plan d'action — New Nintendo 3DS

Dernière mise à jour : **29 septembre 2026**.

## Objectif actif

Faire progresser le startup sans forcer les états guest.

Le verrou courant est :

> **la synchronisation SPU attendue par Psy-Q avant la programmation DMA4, qui
> doit ensuite rendre READY l'événement BIOS attendu par FUN_80014478 et permettre
> la reprise du ReadN à LBA 0x3172D.**

## Phase 1 — Valider le nouveau modèle SPU

Compiler :

~~~sh
git pull
make clean
make PROFILE=1 -j4
~~~

Contrôler dans `debug-latest.txt` :

~~~text
spu_reg_1aa
spu_reg_1ae
dma4_madr_writes
dma4_bcr_writes
dma4_chcr_writes
dma4_last_chcr
dma4_transfers
dma4_event_bridge
~~~

### Succès attendu

~~~text
dma4_chcr_writes > 0
dma4_transfers    > 0
dma4_event_bridge > 0
~~~

Si les stores DMA4 apparaissent, le diagnostic SPU est validé.

## Phase 2 — Vérifier la livraison de l'événement BIOS

Contrôler :

~~~text
bios_test_hits
bios_ev0_ready
gate_777d8_hits
gate_73dc8_hits
~~~

Le comportement recherché est :
1. completion DMA4 ;
2. événement exact F0000009/0x20 rendu READY ;
3. TestEvent retourne succès ;
4. FUN_800777D8 laisse FUN_80014478 continuer.

Ne pas rendre l'événement READY sans cause DMA/SPU.

## Phase 3 — Vérifier la reprise du ReadN

Contrôler :

~~~text
req10
req24
req2c
b34_start
b34_done
b32_calls
b32_ok
b32_fail
~~~

Requête cible :

~~~text
remaining = 0x2000
LBA       = 0x3172D
cmd       = 0x06
~~~

Critère :
- nouveau DataReady ;
- nouveaux CdGetSector ;
- remaining diminue ;
- aucun échec.

## Phase 4 — Sortir du second FUN_80043CD4

Contrôler :

~~~text
c460
c484
post681_43dc8
post681_159f4
post681_2cf60
~~~

Succès :
- les bits bloquants de `C460` disparaissent par le vrai chemin ;
- `FUN_80043DC8` puis `FUN_800159F4` sont atteintes.

## Phase 5 — Nettoyer les probes une fois le startup débloqué

Quand la chaîne est prouvée :
- conserver uniquement les compteurs utiles ;
- supprimer les probes devenus redondants ;
- garder les TXT persistants ;
- documenter chaque bridge restant ;
- ne pas retirer une sonde avant d'avoir une preuve stable du remplacement.

## Phase 6 — Reprendre le chemin fonctionnel

Une fois le startup fidèle rétabli :
1. SU/menu ;
2. nouvelle partie ;
3. saisie du nom ;
4. dialogues ;
5. carte ;
6. premier duel.

Comparer avec les jalons B135 déjà obtenus.

## Phase 7 — Performance

Après rétablissement du chemin :
- profiler code recompilé vs fallback ;
- mesurer boucles de wait ;
- mesurer GPU logiciel / present ;
- réduire les diagnostics de chemin chaud ;
- viser une cadence exploitable avant d'élargir l'émulation.

## Discipline

- une hypothèse à la fois ;
- une trace TXT pour chaque expérience importante ;
- ne pas forcer `C460`, `remaining` ou `ready` ;
- corriger le modèle matériel au niveau le plus bas possible ;
- conserver le comportement guest original ;
- ne pas réinvestiguer un point déjà prouvé sauf régression.

Voir [B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).
