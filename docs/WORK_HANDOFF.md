# Handoff pour nouvelle session

Dernière mise à jour : **21 septembre 2026**.

## Objectif

Porter **Yu-Gi-Oh! Forbidden Memories PAL France SLES-03948** sur New Nintendo
3DS avec PSXRecomp, fallback R3000A et runtime libctru.

## Révision projet de référence

~~~text
912036e9355873d652790a97e160819f031724d9
UP TO FIRST CINEMATIC AND CHAT
~~~

## Révision PSXRecomp

~~~text
Unchiga/psxrecomp
1965b2df424da03483a5370340433a862f78f103
~~~

## Données de référence

~~~text
BIN taille  : 548427600
BIN SHA-256 : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
EXE SHA-256 : 57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44
Load        : 0x80010000
Entry       : 0x800128CC
Stack       : 0x801FFFF0
Disc runtime: sdmc:/3ds/fm-new3ds/disc.bin
~~~

## État fonctionnel actuel

Le backend sait maintenant :

- afficher Konami et l'écran titre ;
- charger/exécuter SU ;
- afficher le menu principal ;
- naviguer et valider ;
- lancer une nouvelle partie ;
- afficher la saisie du nom ;
- écrire et valider le nom ;
- poursuivre jusqu'à la première cinématique / aux premiers dialogues.

**Ne plus traiter le menu SU invisible comme verrou principal.**

## Problème actif

Le jeu est extrêmement lent dans le chemin actuel : ordre de grandeur observé de
quelques FPS.

Déjà intégré :

- B105 : LUT RGB555 et mesures de temps ;
- B106 : flush/swap top screen seulement ;
- B107 : profil -O3 / release, y compris shards générés ;
- B108 : instrumentation VSync ;
- B110 : profiler de plages guest.

Le ralentissement persiste. Il faut identifier le hotspot avant de modifier
encore le code.

## Premier objectif de la prochaine session

Obtenir un tableau de coût par frame avec :

~~~text
loop_ms
guest_ms
vblank_callback_ms
software_render_ms
present_ms
wait_vblank_ms
interp_instructions
fallback_calls
gp0_words
primitives
top_guest_range_0
top_guest_range_1
top_guest_range_2
~~~

Puis classer le problème : fallback/interpréteur, boucle guest active, VBlank,
GPU logiciel, copie/present ou autre routine précise.

## Hypothèse à tester en priorité

Chercher une fonction ou boucle qui devrait attendre un événement PS1 mais tourne
actuellement à plein régime parce qu'un bridge/bypass ne reproduit pas correctement
le timing.

## Cinématique

La première cinématique est atteinte mais visuellement incorrecte. Les pistes
déjà ouvertes concernent draw offset/area, display start/mode, RGB24, MDEC et
composition framebuffer.

Ne pas s'y replonger avant une mesure claire des FPS, sauf si le profiler montre
directement MDEC/composition comme hotspot.

## Build release

~~~sh
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
export PATH=$DEVKITARM/bin:$PATH

bash rebuild_generated_release.sh
make -C 3ds clean
make -C 3ds -j4
~~~

Le script cherche aussi automatiquement le compilateur dans les installations
devkitPro courantes sous MSYS/Git Bash.

## Discipline

- ne pas réintroduire d'hypothèses déjà réfutées ;
- profiler avant d'optimiser ;
- conserver les bridges actuels tant qu'ils servent au diagnostic ;
- préférer une modification qui sépare clairement deux hypothèses ;
- après chaque jalon reproductible : build, capture, commit ;
- ne jamais committer BIN, BIOS Sony, EXE extrait ou shards C propriétaires.
