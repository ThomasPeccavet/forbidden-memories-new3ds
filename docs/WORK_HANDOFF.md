# Handoff pour ChatGPT Work / nouvelle session

Dernière mise à jour : **19 septembre 2026**.

## Objectif

Porter **Yu-Gi-Oh! Forbidden Memories PAL France SLES-03948** sur New Nintendo
3DS avec PSXRecomp, fallback R3000A et runtime libctru.

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

## Fichiers importants

```text
3ds/source/main.c
3ds/source/fm_cpu.c
3ds/source/fm_memory.c
3ds/source/fm_runtime_shim.c
3ds/source/fm_interp.c
3ds/source/fm_gpu.c
3ds/source/disc.c
3ds/source/platform.c
docs/CURRENT_STATUS.md
docs/ACTION_PLAN.md
```

## État fonctionnel actuel

Le backend 3DS/Azahar sait maintenant :

- afficher Konami ;
- afficher l'écran titre ;
- lire START ;
- poursuivre les lectures CD ;
- charger l'overlay SU ;
- exécuter le menu principal en RAM.

Adresses clés :

```text
SU init       : 8018001C
SU update     : 80180390
SU draw cb    : 80180B4C
callback slot : 8009C898
menu objects  : 80184794...
selection     : 801847C0
entrance flag : 801847C5
```

## Dernier test B75

```text
MENU I/U/D : 1/148/0
CB         : 80180B4C
draw       : 147
bridge     : 1
objects    : 11
C0         : 0
C5         : 1 -> 0
O0         : flags 00D8, x=160, target=160, timer=0
O4         : flags 00D8, x=160, timer=0
O5         : flags 0088, x=160, timer=0
GP0        : ~301k words
display    : 0,0
```

**Visuellement, l'écran reste le titre.**

Conclusion : ne plus investiguer START, le chargement SU ou l'animation d'entrée
en premier. Ils sont déjà validés.

## Prochain objectif technique

Construire une trace B76 ciblée sur la chaîne de rendu :

1. compteur GP0 à l'entrée/sortie de `80041674` ;
2. compteur GP0 à l'entrée/sortie de `80180B4C` ;
3. heads/tails des listes de layer, surtout layer 2 ;
4. vérifier que les 11 objets SU appartiennent à la chaîne layer 2 ;
5. afficher les derniers opcodes/coords de la trace GPU ;
6. détecter si d'anciens objets du titre sont toujours rendus après le menu.

Le résultat doit classifier le bug :

- objets non visités ;
- objets visités sans GP0 ;
- GP0 hors écran / mauvais texture state ;
- menu recouvert.

## Discipline

- ne pas réintroduire d'hypothèses déjà réfutées ;
- conserver les bridges actuels tant qu'ils servent à avancer, mais noter qu'ils
  sont temporaires ;
- préférer un diagnostic qui sépare clairement deux hypothèses ;
- après chaque jalon reproductible : build, capture, puis commit ;
- ne jamais committer BIN, BIOS Sony, EXE extrait ou shards C propriétaires.
