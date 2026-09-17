# Yu-Gi-Oh! Forbidden Memories — New Nintendo 3DS

Projet expérimental de portage/recompilation de **Yu-Gi-Oh! Forbidden Memories**
(version française **SLES-03948**) vers **New Nintendo 3DS**.

> [!IMPORTANT]
> Le port New 3DS n'est **pas encore jouable**, mais le projet a dépassé le stade
> du simple prototype graphique : le PS-X EXE français est chargé, du code MIPS
> est recompilé statiquement en ARM11, un fallback R3000A exécute les blocs non
> couverts, plusieurs services BIOS sont émulés et le chemin GPU PS1 est branché
> sur le rasteriseur logiciel.

## État du projet — 17 septembre 2026

| Partie | État actuel |
| --- | --- |
| Profil PAL France / SLES-03948 | ✅ Vérifié |
| Extraction / analyse PS-X EXE | ✅ Fonctionnelle |
| Analyse Ghidra française | ✅ Plusieurs passes + overlays SU étudiés |
| Runtime PC | ✅ Menu, nouvelle partie et premier duel atteints |
| Build native New 3DS | ✅ `.3dsx` ARM11 compilé avec devkitARM/libctru |
| Code résident recompilé ARM11 | ✅ Lié dans le binaire 3DS |
| CPU PS1 / registres / RAM 2 Mio | ✅ Initialisés |
| Dispatch hybride | ✅ ARM recompilé + fallback R3000A |
| Appels BIOS nécessaires au boot | 🟡 HLE partiel, extension au fil du boot |
| GP0 / GP1 PS1 | ✅ Routés vers le bridge GPU |
| Commandes BIOS GPU A0:46..4E | ✅ Bridge présent |
| Rasteriseur PS1 logiciel | ✅ Compilé ARM11 et raccordé |
| Première image réelle du jeu sur 3DS | ❌ Pas encore obtenue |
| I_STAT / I_MASK / VBlank | 🟡 Prochain chantier prioritaire |
| DMA GPU / DMA2 | ❌ À fiabiliser / compléter |
| CD-ROM asynchrone / overlays complets | ❌ À compléter |
| GTE complet | ❌ À compléter |
| XA / SPU / audio | ❌ Non implémentés |
| Sauvegarde | ❌ Non implémentée |
| Test sur New 3DS physique | ❌ Pas encore validé |

Le diagnostic Azahar le plus récent confirme que le fallback R3000A est utilisé,
que le jeu continue après plusieurs appels BIOS et que le bridge GPU reçoit des
mots GP0. Après correction d'une boucle BIOS A0:49, le compteur GP0 est redevenu
cohérent. Le blocage courant est un nouvel appel BIOS **A0:44 (`FlushCache`)** ;
le dernier MMIO observé reste **`0x1F801074` (I_MASK)**.

Voir :
[État courant](docs/CURRENT_STATUS.md) ·
[Plan d'action](docs/ACTION_PLAN.md) ·
[Handoff Work](docs/WORK_HANDOFF.md) ·
[Prototype New 3DS](docs/NEW3DS_PROTOTYPE.md)

## Architecture actuelle

```text
SLES_039.48
    |
    v
PSXRecomp -> C statique -> objets ARM11
    |                       |
    |                       v
    |                 dispatcher natif
    |                       |
    |              cible inconnue ?
    |                  /         \
    |                non         oui
    |                 |           |
    |                 v           v
    |             code ARM   fallback R3000A
    |                             |
    +-----------------------------+
                  |
                  v
             BIOS HLE / MMIO
                  |
        +---------+---------+
        |                   |
       GPU                 CD/IRQ
        |
  gpu_sw_renderer
        |
      VRAM
        |
 écran supérieur 3DS
```

Cette architecture est volontairement hybride. Les fonctions résidentes fiables
peuvent tourner nativement en ARM11 ; les destinations indirectes et futurs
overlays peuvent être exécutés par l'interpréteur R3000A sans imposer une
régénération à chaque adresse manquante.

## Avancement PC vérifié

Le runtime PC expérimental a démarré la version française, atteint le menu
principal, créé une nouvelle partie, parcouru l'introduction et atteint le
premier duel contre Simon Muran. Une carte a été posée et un tour terminé.

<p align="center">
  <img src="research/first-duel/duel.png" width="48%" alt="Premier duel sur le runtime PC">
  <img src="research/first-duel/card-set.png" width="48%" alt="Carte posée pendant le premier duel">
</p>

Ces captures proviennent du runtime PC et restent des jalons historiques ; elles
ne représentent pas encore le rendu New 3DS.

## Prototype New 3DS actuel

Le dossier [`3ds/`](3ds/) contient une application native libctru avec :

- lecture du BIN français MODE2/2352 depuis SD ;
- chargement du PS-X EXE à `0x80010000`, entrée `0x800128CC` ;
- RAM PS1 2 Mio + scratchpad + alias KSEG0/KSEG1 ;
- `CPUState` PSXRecomp et code résident recompilé pour ARM11 ;
- dispatcher statique ;
- fallback R3000A pour les blocs non recompilés ;
- HLE BIOS minimal utilisé par le boot ;
- bridge GPU GP0/GP1 et appels BIOS GPU ;
- rasteriseur logiciel PSXRecomp sur ARM11 ;
- diagnostics CPU, BIOS, MMIO, GPU et interpréteur sur l'écran inférieur.

Le triangle historique de démonstration n'est plus le cœur du chantier : le
jalon actuel est de produire une **VRAM réellement écrite par Forbidden Memories**
puis de la présenter sur l'écran supérieur.

## Compiler le prototype New 3DS

Prérequis : devkitPro `3ds-dev`, Git, Python 3.11+ et la révision PSXRecomp
utilisée par le projet.

```sh
git clone https://github.com/Unchiga/psxrecomp.git work/upstream-psxrecomp
git -C work/upstream-psxrecomp checkout 1965b2df424da03483a5370340433a862f78f103
export PATH=$DEVKITARM/bin:$PATH
make -C 3ds clean
make -C 3ds PSXRECOMP_ROOT=../work/upstream-psxrecomp -j4
```

Sorties attendues :

```text
3ds/fm-new3ds.elf
3ds/fm-new3ds.3dsx
```

Le build New 3DS dépend aussi de l'objet combiné produit à partir du code C
généré dans `work/arm-generated-objects/fm-generated-combined.o`. Voir
[`docs/NEW3DS_PROTOTYPE.md`](docs/NEW3DS_PROTOTYPE.md) pour la procédure détaillée.

## Préparer la SD / Azahar

Le runtime cherche actuellement :

```text
sdmc:/3ds/fm-new3ds/disc.bin
```

Profil supporté :

```text
Version       : PAL France / SLES-03948
Format        : BIN brut MODE2/2352, piste unique
Taille        : 548 427 600 octets
SHA-256       : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
Point d'entrée: 0x800128CC
```

Pour Azahar, placer le fichier dans la SD virtuelle au même chemin. Aucun dump,
BIOS Sony ou contenu propriétaire du jeu n'est distribué par ce dépôt.

## Commandes de diagnostic 3DS

| Bouton | Action |
| --- | --- |
| `A` | RUN / PAUSE |
| `B` | RESET JEU |
| `X` / `Y` | Contrôles d'affichage de diagnostic selon le build |
| `START + SELECT` | Quitter |

L'écran inférieur affiche notamment le PC PS1, les registres, le dernier MMIO,
le résultat du dispatcher, l'état du fallback R3000A, les compteurs GP0, la
position d'affichage VRAM et les arrêts diagnostiques.

## Documentation

Le point d'entrée recommandé est [`docs/README.md`](docs/README.md).
Les documents PC/Ghidra/SU plus anciens sont conservés comme **preuves
historiques datées** ; ils ne décrivent pas tous l'état courant du backend 3DS.

## Priorités immédiates

1. implémenter `A0:44 FlushCache` et poursuivre le boot sans stopper sur les
   appels BIOS simples ;
2. émuler correctement `I_STAT` / `I_MASK` et introduire un VBlank minimal ;
3. fiabiliser DMA2 / linked-list GPU et confirmer une première écriture VRAM ;
4. afficher la VRAM produite par le jeu sur l'écran supérieur ;
5. poursuivre jusqu'au premier overlay dynamique puis au menu ;
6. seulement ensuite élargir CD-ROM, GTE, audio et sauvegardes.

Le plan détaillé et les critères de succès sont dans
[`docs/ACTION_PLAN.md`](docs/ACTION_PLAN.md).

## Données du jeu et licences

**Aucun disque, BIOS PlayStation propriétaire, exécutable original ou contenu
propriétaire du jeu n'est distribué dans ce dépôt.** Les utilisateurs doivent
fournir leur propre copie du jeu lorsqu'un test l'exige.

Le prototype réutilise le rasteriseur de PSXRecomp et libctru. Les notices sont
dans [`3ds/licenses/`](3ds/licenses/).

Yu-Gi-Oh! et Forbidden Memories appartiennent à leurs ayants droit respectifs.
Ce projet de recherche et de portage n'est pas affilié à Konami.
