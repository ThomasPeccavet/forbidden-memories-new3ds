# B136 — audit SPU/DMA4 sans ROM, 6 octobre 2026

Base examinée : `2a7dff31d93d709dfc87b0322086568b54cb679d`, branche
`diag/b135.90-main-menu-items`. Correctif : `fix/b136-spu-dma4-mmio-audit`.

## Défauts reproduits et corrigés

1. `fm_spu_read_half` était appelée avant sa déclaration. La compilation C11
   du vrai module échoue avec un type implicite incompatible. Ajout des prototypes.
2. `fm_memory_write_half` ne dispatchait aucun registre SPU. Les écritures SH
   à DA6/DA8/DAA étaient comptées comme non mappées, alors que les lectures LH
   et les écritures SW étaient déjà implémentées. Le contrôle restait donc nul
   après un SH de `0x20`, empêchant une boucle qui attend ce mode de progresser.
   Les quatre registres du modèle existant utilisent maintenant le même helper
   pour SH et SW ; le statut reste en lecture seule.
3. Le décodeur DMA reconnaissait le canal 4 pour SB/SH, mais son switch
   d'écriture masquée n'avait aucun cas DMA4. Les writes disparaissaient sans
   effet. Les écritures partielles partagent maintenant le chemin SW, avec
   conservation des octets non écrits et la même gestion de START.
4. `fm_memory_init` réinitialisait DMA2/6 mais pas DMA4/SPU. Une deuxième
   initialisation conservait contrôle, registres et tokens de completion.
   L'état et les diagnostics DMA4/SPU sont maintenant remis à zéro.

## Preuves locales

`python tools/run_static_checks.py` : 36 tests unittest réussis, dont un test
qui compile et exécute le vrai `3ds/source/fm_memory.c` en CLEAN et PROFILE.
Ce test contient cinq scénarios par mode (dix exécutions) :

- SH SPU, alias KSEG1, lectures LH/SW et statut non modifiable ;
- écritures SW SPU et lectures LH cohérentes ;
- SB/SH DMA4, conservation des lanes, START écrit par demi-mot/octet ;
- completion synchrone existante, START clear, DICR/IRQ et consommation unique
  du token exposé au BIOS ;
- réinitialisation après un transfert non encore consommé.

Avant correction, la compilation échouait. Après ajout des seuls prototypes,
les scénarios SH SPU, DMA partiel et reset échouaient dans les deux modes.
Après correction complète, les dix scénarios passent. Les stubs host remplacent
uniquement l'horloge 3DS, le type opaque CPU et les appels GPU hors sujet ;
les registres, les IRQ et la completion testés sont le code de production.
Un appel GPU inattendu fait échouer le test. Aucun disque ni Azahar requis.
Sans compilateur C host, le test est explicitement skipped ; Ubuntu CI fournit cc.

## Événement BIOS : audit, pas validation du jeu

Le chemin actuel `TestEvent` vérifie l'index, used/enabled, la classe F0000009
et le spec 0x20 avant de consommer un token DMA4. Il marque ready, puis retourne
un succès en consommant ready. Le test mémoire prouve la production et la
consommation unique du token, mais n'exécute ni ce handler BIOS ni les callbacks
du jeu. Aucun changement n'est apporté à ce bridge dans cette passe.

Limites observées à traiter séparément avec une trace :

- la completion DMA4 reste synchrone et ne copie pas les données vers une RAM
  SPU ; DPCR, requête SPU et modes DMA ne sont pas complètement modélisés ;
- le bridge est déclenché au polling TestEvent, pas au moment de la completion ;
  il ne filtre pas le mode 0x2000 et n'est pas partagé avec WaitEvent ;
- quick-load efface les tokens DMA4 en attente : un état pris entre completion
  et TestEvent peut donc perdre ce signal. Le format quick-state n'est pas changé.

Ces limites ne sont pas corrigées arbitrairement pour masquer le blocage.
Les corrections présentes réparent le transport MMIO du modèle déjà intégré.
Elles ne prouvent pas encore que le startup du jeu passe.

## Prochain essai avec le PC

Compiler cette branche : `make -C 3ds PROFILE=1 -j2`. Le labo pointe encore
sur la branche de base ; il ne testera pas ce correctif tant que sa ref n'est
pas changée ou que cette branche n'est pas intégrée.

Partir d'un démarrage à froid, sans quick-load. Collecter un nouveau
`debug-latest.txt` et vérifier dans l'ordre :

1. mode de transfert SPU observable ;
2. écritures MADR/BCR/CHCR DMA4 ;
3. `dma4_transfers > 0` et `dma4_event_bridge > 0` ;
4. progression du ReadN à LBA 0x3172D ;
5. `post681_43dc8 > 0`, puis `post681_159f4 > 0`.

Si une étape échoue, conserver la trace et corriger son producteur. Aucun
forçage de C460, req10 ou ready n'est ajouté. Aucun gain FPS n'est revendiqué.
