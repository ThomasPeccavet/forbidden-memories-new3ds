# Handoff pour nouvelle session

Dernière mise à jour : **29 septembre 2026**.

## Objectif

Porter **Yu-Gi-Oh! Forbidden Memories PAL France SLES-03948** sur New Nintendo
3DS avec code PSXRecomp ARM11, fallback R3000A et runtime libctru.

## Branche active

~~~text
diag/b135.90-main-menu-items
~~~

## PSXRecomp

~~~text
Unchiga/psxrecomp
1965b2df424da03483a5370340433a862f78f103
~~~

## Données de référence

~~~text
BIN taille  : 548427600
BIN SHA-256 : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
Load        : 0x80010000
Entry       : 0x800128CC
Stack       : 0x801FFFF0
Disc runtime: sdmc:/3ds/fm-new3ds/disc.bin
~~~

## État fonctionnel historique

Des branches B135 ont déjà permis :
- menu principal ;
- nouvelle partie ;
- saisie/validation du nom ;
- dialogues ;
- carte ;
- duel ;
- plusieurs tours.

Le travail courant repart volontairement plus bas pour restaurer un startup plus
fidèle et supprimer les forçages de state.

## Verrou actif

Le startup est bloqué dans le second `FUN_80043CD4`.

État :

~~~text
c460=01C00016
c484=00000000
post681_43cd4=2
post681_43dc8=0
post681_159f4=0
~~~

Requête CD :

~~~text
remaining=00002000
buffer=801E1639
LBA=0003172D
cmd=01400006
callback=80014A4C
~~~

Le pipeline CD précédent est prouvé sain :

~~~text
b32_calls=62
b32_ok=62
b32_fail=0
b34_start=62
b34_done=62
~~~

## Gate identifiée

`80014478` attend :

~~~text
FUN_800777D8(0)
 -> FUN_80073DC8(F1000000)
 -> TestEvent
~~~

Événement :

~~~text
class=F0000009
spec=00000020
mode=00002000
used=1
enabled=1
ready=0
~~~

## Cause racine immédiate

Le transfert SPU atteint bien :

~~~text
FUN_80075AFC(3, 801DC000, 0x200)
~~~

et les pointeurs DMA sont corrects :

~~~text
1F8010C0
1F8010C4
1F8010C8
~~~

Mais la routine attend avant les stores :

~~~text
(SPU+0x1AA) & 0x30 == 0x20
~~~

Trace avant correctif :

~~~text
spu_base=1F801C00
spu_mode=0
spu_reg_1aa=0000
spu_reg_1ae=0000
dma4_*_writes=0
~~~

Le runtime ne modélisait pas le SPU.

## Dernier correctif

Ajout d'un modèle SPU minimal :
- 1F801DA6 transfer address ;
- 1F801DA8 transfer data ;
- 1F801DAA control ;
- 1F801DAE status ;
- synchronisation bits 0x20/0x30 ;
- sauvegarde quick-state.

Un DMA4 minimal avait déjà été ajouté juste avant.

Dernier commit fonctionnel avant documentation :

~~~text
34e84d19ee619f11f561116a18a950e71f2d30c2
~~~

**Ce correctif n'a pas encore été testé.**

## Premier test de la prochaine session

Depuis `3ds` :

~~~sh
git pull
make clean
make PROFILE=1 -j4
~~~

Envoyer ensuite `debug-latest.txt`.

Lignes prioritaires :

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

## Résultat recherché

Étape 1 :

~~~text
dma4_chcr_writes > 0
dma4_transfers > 0
dma4_event_bridge > 0
~~~

Étape 2 :
- TestEvent réussit ;
- `80014478` continue ;
- le ReadN `0x3172D` démarre ;
- `req10` diminue.

Étape 3 :

~~~text
post681_43dc8 > 0
post681_159f4 > 0
~~~

## À ne pas faire

Ne pas :
- forcer C460 à 0 ;
- forcer req10 à 0 ;
- rendre l'événement READY arbitrairement ;
- bypasser 80043CD4 ;
- conclure à un bug du recompilateur sans nouvelle preuve.

## Méthode

Toujours préférer :
1. sonde TXT ;
2. preuve ;
3. remontée d'un niveau ;
4. correction du modèle matériel ;
5. re-test.

Document complet :
[B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).
