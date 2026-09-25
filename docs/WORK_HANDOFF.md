# Handoff pour nouvelle session

Dernière mise à jour : **25 septembre 2026**.

## Projet

Port de **Yu-Gi-Oh! Forbidden Memories PAL France SLES-03948** vers New Nintendo
3DS avec PSXRecomp, code ARM11 généré, fallback R3000A et libctru.

## Révision PSXRecomp

```text
Unchiga/psxrecomp
1965b2df424da03483a5370340433a862f78f103
```

## Données de référence

```text
BIN taille  : 548427600
BIN SHA-256 : 9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835
EXE SHA-256 : 57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44
Load        : 0x80010000
Entry       : 0x800128CC
Stack       : 0x801FFFF0
Disc runtime: sdmc:/3ds/fm-new3ds/disc.bin
```

## Baseline duel

La lignée **B135.71** est l'oracle fonctionnel actuel.

Fonctionnel :

- menu ;
- nouvelle partie ;
- nom ;
- carte ;
- entrée en duel ;
- main ;
- plusieurs tours ;
- adversaire ;
- rendu 3D.

Limites :

- ~12–15 FPS ;
- ~4 FPS pendant certaines attaques ;
- images de cartes parfois incorrectes ;
- dialogues 2D hors duel absents.

## Résultats B135.74 / 75

- B135.74 CLEAN : aucun gain FPS.
- B135.75 Interpreter Fast Path : aucun gain visible.

Ne pas reprendre ces deux pistes sans nouvelle mesure.

## Enquête dialogue B135.76 → 80

B135.76 corrige plusieurs erreurs de presenter. B135.77 a créé une régression en
confondant draw-page et frontbuffer. B135.78 revient à GP1 autoritaire.

Capture B135.78 :

```text
PRES g:0,0 l:0,0 d:0,0 p:0 nz:0/0
```

Donc la bonne page est choisie mais aucun dialogue n'y a été rendu.

B135.79 :

```text
OBJ79 n:0/5/0/0/0/0/0
WALK79 ... 408bc:0 ...
GP2D79 rect/q/2c/3a:0/0/0/0
```

Ghidra confirme :

- `FUN_800408BC` parcourt `DAT_800F11C2` ;
- `FUN_80041674` parcourt les 7 heads C0..CC via une table de 7 pointeurs ;
- la table se trouve à `0x800923DC..0x800923F4` ;
- C2 correspond à `0x800923E0`.

## Branche à tester

```text
diag/b135.80-c2-indirect
```

B135.80 affiche :

```text
TAB80 c0/c2/c4/cc:...
C2TAB h:... ptr:........ exp:800408BC ent:... r416:...
```

Décision :

- ptr faux → table ;
- ptr correct + ent=0 → dispatcher statique ;
- ptr correct + ent=1 + 408bc=0 → indirect/JALR ;
- 408bc>0 + GPU 0 → interne à 408BC / callbacks / OT.

## Build

```sh
git fetch origin
git switch diag/b135.80-c2-indirect
git pull --ff-only

cd 3ds
make clean
make -j4
```

## Règles de reprise

- ne pas modifier le presenter avant le test B135.80 ;
- ne pas forcer 408BC à chaque frame sans preuve ;
- conserver B135.71 comme référence duel ;
- une hypothèse / une branche ;
- ne pas committer les données propriétaires.
