# B136 — Startup CD / événement BIOS / SPU / DMA4

Dernière mise à jour : **29 septembre 2026**.

## But

Documenter le verrou de démarrage actuellement observé sur la branche :

~~~text
diag/b135.90-main-menu-items
~~~

Le principe de cette série B136 est de **remplacer les suppositions par des
preuves persistantes écrites sur SD**, puis de corriger la chaîne matérielle au
niveau le plus bas possible.

Fichiers de diagnostic :

~~~text
sdmc:/3ds/fm-new3ds/debug-latest.txt
sdmc:/3ds/fm-new3ds/memory-watch.txt
~~~

## 1. Entrée startup confirmée

Le chemin PAL Europe est maintenant correct.

Overlay :

~~~text
801680F4  3C03BFC8
801680F8  9063FF52
801680FC  24020045
80168100  1062001A
~~~

Le byte BIOS lu à `BFC7FF52` doit être `0x45` ('E').

Trace confirmée :

~~~text
bios_region_bfc7ff52=45
ov68160_enter=1
ov68160_return=1
ov68160_v0=00000000
ov68160_ret0=1
~~~

La boucle overlay n'est donc plus le verrou.

## 2. Startup bloqué dans le second FUN_80043CD4

Le chemin de `FUN_80043E3C(0)` a été reconstruit statiquement.

Après le premier overlay, le code atteint le second :

~~~text
FUN_80043CD4(0xB4)
~~~

mais n'atteint pas encore :

~~~text
DAT_8009C44B = 1
FUN_80043DC8(1,0)
FUN_800159F4()
~~~

Trace type :

~~~text
post681_43cd4=2
post681_43dc8=0
post681_159f4=0
~~~

La condition de sortie de `80043CD4` dépend notamment de :

~~~text
(DAT_8009C460 & 0x02000030) == 0
DAT_8009C484 == 0
~~~

Or le run bloqué conserve :

~~~text
C460 = 01C00016
C484 = 00000000
~~~

Le bit `0x10` interdit la sortie.

## 3. Requête CD bloquée identifiée

La requête active située à `DAT_800EB1B8` contient :

~~~text
req+0x10 remaining = 00002000
req+0x18 buffer    = 801E1639
req+0x1C total     = 00002000
req+0x20 callback  = 80014A4C
req+0x24 LBA       = 0003172D
req+0x2C flags/cmd = 01400006
req+0x34 context   = 801E1650
req+0x40 state     = 00000002
~~~

La commande basse `0x06` correspond au ReadN attendu par la chaîne CD.

Important : le pipeline CD précédent fonctionne.

Trace confirmée :

~~~text
b34_start=62
b34_done=62
b32_calls=62
b32_ok=62
b32_fail=0
b32_lba=00000D98
~~~

Le problème n'est donc pas « le lecteur CD ne lit rien ».

## 4. Le memory watch a identifié le créateur exact

Le watcher a suivi les écritures de la requête.

Séquence décisive :

~~~text
seq=60 pc=8001431C req+0x10 = 00002000
seq=61 pc=80014324 req+0x18 = 801E1639
seq=62 pc=80014320 req+0x24 = 0003172D
seq=63 pc=80014328 req+0x2C = 01400006
seq=65 pc=800143C8 C460     = 01400016
seq=66 pc=800148B0 C460     = 01C00016
seq=67 pc=800148D0 req+0x40 = 00000001
~~~

Conclusion :

> La requête est correctement recopiée/réarmée par `FUN_800142F8`.
> Le blocage est après sa création, dans la transition interne de
> `FUN_80014478`.

## 5. Gate FUN_800777D8 / TestEvent

`80014478` appelle `FUN_800777D8(0)`.

Trace :

~~~text
gate_777d8_hits > 0
gate_777d8_a0=00000000
gate_777d8_ra=800148FC

gate_73dc8_hits > 0
gate_73dc8_a0=F1000000
gate_73dc8_ra=80077828
~~~

Les wrappers consécutifs autour de `80073D98..80073DE8` correspondent à la
famille BIOS événement :

~~~text
OpenEvent
CloseEvent
WaitEvent
TestEvent
EnableEvent
DisableEvent
~~~

`80073DC8` correspond donc à `TestEvent`.

## 6. Événement BIOS attendu

L'événement existe réellement dans le HLE :

~~~text
handle = F1000000
used   = 1
enabled= 1
ready  = 0
class  = F0000009
spec   = 00000020
mode   = 00002000
func   = 00000000
~~~

Trace :

~~~text
bios_test_hits > 0
bios_deliver_hits=0
~~~

Le jeu teste donc correctement un événement valide, mais personne ne le rend
READY.

## 7. Producteurs possibles

Deux chemins candidats ont été tracés :

~~~text
FUN_80077108
FUN_800772A8
FUN_80075998
FUN_80076098
~~~

Résultat :

~~~text
producer_77108_hits=0
producer_772a8_hits=0
producer_75998_hits=0
producer_76098_hits=0
~~~

Cela a permis de remonter plus haut dans la chaîne SPU.

## 8. Callback DMA canal 4

`FUN_800760A8` enregistre un callback via `FUN_80074938(4, callback)`.

Le canal 4 est le **DMA SPU**.

Le runtime ne modélisait historiquement que :

~~~text
DMA2 = GPU
DMA6 = OTC
~~~

Un modèle DMA4 minimal a donc été ajouté :

~~~text
MADR 1F8010C0
BCR  1F8010C4
CHCR 1F8010C8
~~~

avec :
- START ;
- fin synchrone de bring-up ;
- clear BUSY ;
- flag DICR canal 4 ;
- compteur de completion ;
- bridge vers l'événement BIOS exact.

Mais les premiers tests après ajout ont montré :

~~~text
dma4_transfers=0
dma4_madr_writes=0
dma4_bcr_writes=0
dma4_chcr_writes=0
~~~

Donc DMA4 n'était pas encore programmé.

## 9. FUN_80075AFC est bien exécutée

Une sonde a prouvé :

~~~text
spu_75afc_hits=63
spu_75afc_a0=00000003
spu_75afc_a1=801DC000
spu_75afc_a2=00000200
spu_75afc_ra=80075DD4
~~~

Et les pointeurs globaux sont corrects :

~~~text
spu_ptr_madr=1F8010C0
spu_ptr_bcr =1F8010C4
spu_ptr_chcr=1F8010C8
~~~

À ce stade il aurait été tentant de conclure à un store MMIO recompilé perdu.
Cette hypothèse a été **mise en attente** après lecture du pseudo-code complet.

## 10. Vrai verrou : précondition SPU avant DMA4

Le pseudo-code de `FUN_80075AFC(param_1=3)` montre qu'avant d'écrire les trois
registres DMA4, la routine attend que le contrôle SPU soit dans le bon mode.

Pour `DAT_80094008 == 0` :

~~~text
(SPU + 0x1AA) & 0x30 == 0x20
~~~

Pour le mode 1 :

~~~text
(SPU + 0x1AA) & 0x30 == 0x30
~~~

Trace réelle :

~~~text
spu_base=1F801C00
spu_mode=00000000
spu_reg_1a6=0000
spu_reg_1aa=0000
spu_reg_1ae=0000
~~~

Conclusion :

> Le runtime ne modélisait pas le SPU. `80075AFC(3)` boucle jusqu'au timeout
> avant même les stores DMA4.

C'est la cause immédiate prouvée de :

~~~text
dma4_*_writes = 0
dma4_transfers = 0
bios_event.ready = 0
ReadN 0x3172D bloqué
second 80043CD4 bloqué
~~~

## 11. Correctif courant

Le dernier correctif ajoute un modèle SPU minimal ciblé sur les registres utilisés
par Psy-Q :

~~~text
1F801DA6  transfer address
1F801DA8  transfer data
1F801DAA  control
1F801DAE  status
~~~

Le modèle ne cherche pas encore à produire du son.

But :
- mémoriser les accès ;
- refléter les bits de mode de transfert `0x20/0x30` ;
- laisser les wait loops Psy-Q observer un périphérique prêt ;
- permettre ensuite à `80075AFC(3)` de programmer DMA4.

Quick-state étendu pour conserver cet état.

Dernier commit fonctionnel de la série documentaire :

~~~text
34e84d19ee619f11f561116a18a950e71f2d30c2
fix: persist minimal SPU state
~~~

Le test de ce correctif est **encore à faire**.

## 12. Prochain test attendu

Build :

~~~sh
git pull
make clean
make PROFILE=1 -j4
~~~

Vérifier dans `debug-latest.txt` :

~~~text
spu_reg_1aa=
spu_reg_1ae=

dma4_madr_writes=
dma4_bcr_writes=
dma4_chcr_writes=
dma4_last_chcr=
dma4_transfers=
dma4_event_bridge=

req10=
c460=
post681_43dc8=
post681_159f4=
~~~

Première validation recherchée :

~~~text
dma4_chcr_writes > 0
dma4_transfers    > 0
dma4_event_bridge > 0
~~~

Puis :

~~~text
req10 < 00002000
~~~

ou passage complet de la requête, suivi de :

~~~text
post681_43dc8 > 0
post681_159f4 > 0
~~~

## 13. Ce qu'il ne faut pas faire

Ne pas :
- forcer `C460` à zéro ;
- forcer `remaining` à zéro ;
- marquer l'événement BIOS READY sans cause matérielle ;
- bypasser `80043CD4` ;
- réintroduire B50 comme solution permanente ;
- conclure à un bug du recompilateur tant que le test SPU minimal n'a pas été fait.

Ces approches masqueraient la chaîne réelle et rendraient la suite moins fiable.

## 14. Méthode

La méthode retenue pour la suite est :

1. un verrou observé ;
2. une sonde TXT ;
3. une preuve ;
4. remonter d'un niveau ;
5. corriger le modèle matériel le plus bas possible ;
6. conserver le comportement guest original.

Cette approche doit rester la règle pour CD, SPU, DMA, IRQ, GPU et overlays.
