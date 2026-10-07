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

## Essai utilisateur du 7 octobre et sonde vidéo B136.7

Le cold boot après correction a franchi le blocage précédent : 214 DMA4,
2 livraisons via le bridge, 491 lectures CD réussies et zéro échec, req10=0,
C460=0, post681_43dc8=1 et post681_159f4=2. L'événement ready=0 après TestEvent
est compatible avec sa consommation. Cela valide la progression observée,
pas le pipeline audio ni la suppression de tous les bridges.

Observation visuelle : logo Konami, noir, titre/menu brièvement visible puis
noir. La cause vidéo reste inconnue. B136.7 ajoute uniquement des diagnostics
PROFILE, au rythme existant d'une collecte toutes les 120 frames hôte :

- `debug-latest.txt` : vrais registres GPU via quick-save en lecture seule,
  draw-area/offset, parser, page GP1, latch, compteurs du cycle de vie du menu,
  hashes et occupation échantillonnée des pages ;
- `video-watch.txt` : historique borné aux 16 dernières collectes, réécrit
  à chaque collecte ; aucun état du jeu ni choix de framebuffer n'est modifié.

Indices des pages : 0=(0,0), 1=(320,0), 2=(0,256), 3=(320,256),
4=vue exacte GP1 si bornée, 5=composite hôte si latch valide.
`nz` compte des pixels RGB non nuls sur une grille 8x8 (maximum 1200) ;
un zéro est une observation échantillonnée, pas une preuve que chaque pixel
est noir. Le mode RGB24 devra être interprété séparément.

Prochain essai : même branche PROFILE, démarrage à froid, laisser l'écran
devenir noir et attendre 10 secondes pour rafraîchir les TXT. Envoyer les
deux fichiers. Comparer image GPU, composite hôte et activité du menu avant
de choisir un correctif de rendu.

## B136.8 : trace du verrou de rendu et du fondu

Le second essai atteint menu_init=1, menu_update=634, menu_destroy=0.
La page GP1 reste (0,0), son échantillon est noir ; la page (320,256)
conserve des pixels sans preuve qu'elle soit le framebuffer à afficher.
La file CD est vide. C4B8=0 empêche la soumission des ordering tables dans
la fonction originale 80012D60. Cela explique un mécanisme possible du noir,
sans identifier encore pourquoi le verrou reste fermé.

`change_pc` dans c4b8-diag est un contexte observé, pas nécessairement
l'instruction ayant écrit. B136.8 recentre le journal borné
`memory-watch.txt` sur C4B8 et EB248..EB250 (état du fondu). En PROFILE,
les stores interprétés concernés passent par le même callback mémoire et
portent le PC réel du store, y compris dans un delay slot. Le bridge hôte
de fondu est marqué PC=0. Les stores générés utilisent leur instrumentation
existante. Aucun verrou ou choix de page n'est forcé.

Le dump vidéo expose aussi les octets du fondu, les compteurs de paquets
et DMA2. Les compteurs fill/draw/copy/upload de c4b8-diag étaient toujours
zéro car le snapshot ne les copiait pas : cette omission est corrigée,
sans changer le rendu. Le journal ne conserve que les 96 derniers changements.

Essai : cold boot PROFILE, attendre dix secondes après le noir, fermer
Azahar, envoyer memory-watch.txt et les 80 dernières lignes de debug-latest.txt.

## B136.9 : corruption du verrou par le résultat CD

La trace utilisateur termine par current=target=FF, flags=10, puis C4B8
est remis à zéro. Les stores attribués à 80014924/8007C5E8/8007C6B8 sont
en réalité des écritures HLE portant un ancien PC guest : le bridge utilisait
8009C4B4 comme scratch et effaçait 16 octets. Il écrasait ainsi C4B8 et
les couleurs C4B9..C4C3, pendant et après les fondus. Cette attribution
rectifie l'hypothèse du paragraphe B136.8 sur les writers.

B136.9 place le résultat dans le vrai tampon sync LibCD 800F7130 (déjà
attendu par les consommateurs guest), initialise seulement ses 8 octets
et conserve le tampon ready 800F7138 adjacent. Les callbacks reçoivent ce
même tampon ; la copie redondante vers lui est supprimée. Aucun forçage
du verrou et aucun changement du bridge de fondu n'est ajouté.

Le test host compile le writer C de production et vérifie les réponses
Pause/GetlocL ainsi que des sentinelles sur le CdlLOC, le verrou, les couleurs
et le tampon ready. La version antérieure échoue sur ces assertions.
Le résultat visuel nécessite encore un cold boot Azahar.

## Prochain essai avec le PC

### B136.11 : correction du diagnostic titre et retrait B75

L'essai B136.10 reste à 8006A53C/8006A54C/80078B58 avec title=80/80,
str=0/0, menu_init=0. Après START : menu_init=1 et title=00/81. Le STR
précède donc l'écran interactif SU. Le désarmement automatique était une
régression ; le premier flux non pris en charge est à nouveau terminé
automatiquement, comme en B136.9. Pas de rétablissement du saut vers état 8.

L'overlay variant_0 8018001C initialise les 11 entrées sans bit 0x40.
80180390 garde ces entrées cachées tant que le prompt 8018478C reste visible,
puis START masque le prompt et lance l'animation. B75, lui, intervenait
après 24 updates et posait 0x40, les positions finales et c5=0 sans tester
le prompt. Il pouvait afficher simultanément les deux états. B136.11
supprime intégralement cette mutation et ses compteurs devenus inutiles.

Les traces vidéo ajoutent prompt/items (visibilité selon flags & C0), c4/c5
dans debug-latest, pour vérifier avant et après START. Les 37 tests host
passent ; l'essai réel reste requis. Le STR/MDEC complet est toujours absent.

### B136.10 : transition titre et fin de fondu natives

B136.9 confirme le rendu continu (gate=1, 7178 paquets draw). Le premier
flux STR était automatiquement terminé car skip_pending démarrait à 1,
même sans START. La demande démarre maintenant à 0 et n'est armée que par
un front physique START pendant un flux actif. Le raccourci B73 qui écrivait
directement les états menu est retiré ; 35EB0/44084 gardent leur nettoyage.

La trace montre aussi des pas de fondu alternant guest/host et des fins à
zéro consommées par le host sans appel 15C28. Le bridge n'implémentait pas
tous les chemins du fondu. Le service guest 15400/1522C étant actif, le host
observe seulement les octets et ne les modifie plus. Cette suppression
cible une cause plausible des fonds superposés ; le résultat visuel n'est
pas encore validé. Le STR/MDEC complet reste hors périmètre de cette passe.

video-watch ajoute title=C6A0/C7A8, str=done/skip_count, pad=edge et
fade=current/target/flags. Essai cold boot : attendre 10 secondes sans START,
puis appuyer une fois et vérifier la transition et les deux fonds.

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


## B136.12 : diagnostic de l'introduction après le nom

L'essai B136.11 confirme le titre seul avant START et items=01F après START,
puis destruction normale du menu. Après le nom, le GPU continue et C460
reste 00080410. La capture montre une boîte de dialogue vide et des pixels
corrompus dans la scène. Les derniers octets de fondu sont FF/FF/00 :
pas de second bridge de fondu réintroduit.

Le dump startup montrait une requête fixe 800EB1B8. Le nouveau fichier
intro-diag.txt suit le pointeur réel 8009C2A8 utilisé par 80013B44, avec
bornes RAM avant lecture des champs. Il persiste aussi le traceur texte
existant (script, objet, glyphes, compteurs generated/outer), la tête CC,
le contexte STR et les compteurs MDEC. Cadence 120 frames PROFILE, réécriture
bornée en taille, aucun changement des flags ou du pipeline guest.

La cause du texte et de la scène corrompus reste à déterminer. Les vidéos
STR/MDEC ne sont pas complètement prises en charge ; cela ne permet pas
d'attribuer automatiquement à MDEC le défaut de texte.

## B136.13 : ordering de completion CD

Trace : req_type=04, flags=00080410, sync=02/cmd=09, reading=0,
716 DataReady terminées, file LibCD vide. Le script est état 84, ptr=801C0025,
glyph_write=800EC390. Ceci cible le démarrage du transport XA plutôt qu'une
lecture de secteurs en échec (716 réussies, zéro échec).

80014478 appelle 7B78C(Pause,1413C), puis pose busy=400. Le callback
1413C passe la phase à 2 et efface busy. La livraison immédiate du bridge
pouvait inverser cet ordre : effacer, puis reposer busy. De plus, son ancien
test cb_active intervenait après l'écriture des métadonnées actives, ce qui
pouvait écraser le contexte si le callback démarrait une autre commande.

B136.13 sépare pending/actif, retourne immédiatement l'acceptation au caller,
puis publie Complete et le vrai callback à partir de la frame suivante.
La livraison se fait hors tick CD/DataReady/cleanup, et conserve le contexte
interrompu courant et le GP de l'émetteur pour le callback. PC/RA/GPR et
HI/LO sont restaurés au retour. Aucun flag busy, remaining ou script n'est
forcé. La completion de ReadN garde l'armement DataReady existant.

Le test host compile les fonctions de production : pas de callback inline,
pas de Complete anticipé, reprise au PC de livraison, préservation de RA/GP/
HI/LO, commande suivante pendant le callback sans corruption et refus d'une
commande si pending est déjà occupé. Total 38 tests. Retester le cold boot,
le titre et la nouvelle partie ; transport/audio XA et STR/MDEC restent
incomplets, donc le résultat de la scène et du texte reste à vérifier.

## B136.14 : wrapper ReadS et position XA

Le test B136.13 confirme phase 06, flags C001, position 4D8C, fin 31834,
GetlocL répété (commande 10), script 0A et toujours aucun texte visible.
Le pseudo-C 8007BA34 montre que 7BA00 construit Pause/SetMode/Setloc/ReadS.
L'interception ne traitait que Setloc/ReadN/Pause : ReadS confirmait une
lecture jamais démarrée et le wrapper ne cherchait pas son CdlLOC.

Backend unique fm_cd_apply_command pour main/IRQ et ancien fallback.
Le mode du wrapper est explicite ; ses paramètres fournissent la position.
Les effets n'interviennent qu'après acceptation (refus pending sans effets).
ReadS démarre un transport silencieux, distinct de la lecture DataReady.
La position progresse selon osGetTime, 75 ou 150 secteurs/s selon mode bit7,
avec fraction milliseconde, et GetlocL livre la position BCD courante.
Pause/Stop/Init et retour à ReadN l'arrêtent ; reset nettoie tout l'état.
Le tick pause hôte actualise l'horloge sans avancer ni rattraper la pause.
Le transport ne décode aucun secteur XA/PCM et ne touche pas aux flags du
jeu, au remaining, à la fin XA ou au script. Le rendu STR/MDEC reste incomplet.

Le test C du backend vérifie seek/mode ReadS, fraction, 75/150 secteurs/s,
requêtes de position répétées sans accélération, conversion GetlocL BCD,
pause hôte, Pause CD, transition vers ReadN, et refus sans effets. Total
38 tests host. Retester nouvelle partie/nom et collecter intro-diag après
10 secondes ; cette vérification n'annonce pas le texte corrigé en jeu.

## B136.15 : XA audio et STR/MDEC

Validation utilisateur B136.14 : le texte apparaît. Flags CD zéro, position
3185C > fin 31834. Transport/attente script ne sont plus le verrou observé.

- disc.c fournit les 2352 octets bruts validés et garde l'API 2048 compatible.
- fm_xa.c décode 18 groupes XA, 4/8 bits, mono/stéréo, 37800/18900 Hz,
  saturation signée et historique par canal ; changement de canal réinitialise
  l'historique. Formats réservés/emphase et buffers trop courts sont refusés.
- fm_audio.c possède 16 buffers linéaires NDSP stéréo PCM16, reprend seulement
  FREE/DONE, flush cache avant queue, pause hôte et état DSP observable.
- fm_media.c parcourt les secteurs sans saut, filtre XA, applique la matrice
  CdlMix, reconstitue les frames STR et remplit le ring natif (2/3, wrap 1).
  Une frame incomplète ou un ring occupé n'est jamais publié/écrasé.
- MDEC est repris de PSXRecomp 1965b2d avec licence/provenance préservées.
  DMA0/1, CHCR busy, DICR, attentes FIFO et callback DMA1 sont raccordés.
  Le callback restaure PC/GPR/HI/LO et attend la fin des autres callbacks.
- Désarmement du skip premier STR : le lecteur natif doit lire la vraie vidéo.

46 tests host passent, dont oracle FFmpeg indépendant byte-exact sur PCM
synthétique non nul, codecs/groupes, filtrage/matrice vers NDSP, buffers DSP,
secteurs Form2 complets, ring plein/wrap/frame complète, MDEC gris RGB16/RGB24
via MMIO/DMA et interruption différée. L'oracle est optionnel si FFmpeg absent.
CI compile aussi les quatre nouveaux objets de production ARM.

Limites explicites : XA seulement pour la sortie audio actuelle (voix SPU
non mixées), conversion de fréquence NDSP au lieu du zigzag PS1, emphase
refusée, savestates média non intégrés. Les fixtures ne prouvent pas la
lecture du flux FR ni la vitesse de décodage sur 3DS. Essai utilisateur
nécessaire depuis le boot puis nouvelle partie/nom ; collecter intro-diag
et video-watch pour distinguer secteur, frame, VLC, MDEC, présentation et DSP.

## B136.16 : débit des transferts STR / MDEC / GPU

Vidéo d'ouverture validée par l'utilisateur sur B136.15, mais 5–10 FPS.
Le compteur `mdec_in=155`, `out=3060` et environ 9 millions de mots GP0
montrent l'importance du chemin des uploads. Ce n'est pas une mesure du
bottleneck : B136.16 ajoute la durée réelle et le temps de décodage MDEC.

- STR : memcpy RAM borné après réservation de toute la frame ; marqueurs,
  disposition et backpressure conservés.
- DMA0/1 : bursts contigus bornés à la RAM et au FIFO ; chemin par mot pour
  les transferts inversés, MADR/CHCR/DICR/callback de fin identiques.
- FIFO sortie MDEC : memcpy des mots disponibles, conservation du dernier
  mot partiel, compteur et événement OUTPUT_DRAINED uniques.
- GP0 : commandes conservées ; payload A0 copié par ligne avec l'API bulk
  du renderer, qui maintient le dirty-state et le miroir supersamplé.
  Dernier pixel impair, commandes après upload et wrap VRAM testés contre
  le vrai chemin de production par mot, avec bursts de tailles variables.
- Codec IDCT/RLE/quantification et timing CD inchangés. Aucun frame-skip.

47 tests host. Le benchmark upload synthétique (100 frames / 20 stripes
24x256) montre ~24 ms par mot, ~3 ms par bloc sur l'hôte. Gain de FPS à
vérifier sous Azahar ; `movie_perf` distingue cadence couleur MDEC et coût
codec. Sortie sonore et animation après le nom restent à traiter ensuite.
