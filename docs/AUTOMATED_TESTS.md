# Tests automatisés de bring-up

Cette infrastructure sert à réduire les cycles manuels Azahar pendant le portage
New Nintendo 3DS.

## 1. Validation rapide de main.c

Commande :

```sh
python tools/validate_main_c.py 3ds/source/main.c
```

Le script vérifie notamment :

- doublons de `case` dans `fm_trace_dispatch` ;
- définitions `static` dupliquées ;
- présence d'un marqueur `BUILD Bxx` ;
- marqueurs de conflit Git.

C'est le test à lancer avant chaque compilation 3DS.

## 2. Validation SU.MRG directement depuis disc.bin

Commande :

```sh
python tools/validate_su_layout.py /chemin/vers/disc.bin
```

Pour éviter de recalculer le SHA-256 du disque pendant les itérations rapides :

```sh
python tools/validate_su_layout.py /chemin/vers/disc.bin --skip-disc-hash
```

Le script vérifie la version française via `profiles/SLES-03948.json` et inspecte
le découpage observé dans `FUN_8006B350` :

```text
+0x00000  0x20000  scratch/buffer
+0x20000  0x10000  scratch/buffer
+0x30000  0x01000  0x801DD000
+0x31000  0x08000  0x80180000
+0x39000  0x00800  0x801AF800
```

Il affiche pour chaque bloc :

- offset relatif ;
- LBA absolu ;
- SHA-256 ;
- nombre d'octets non nuls ;
- 16 premiers octets ;
- quatre premiers mots 32 bits.

Pour le build B76, la ligne essentielle est `resource_tail`. Le mapping attendu
est :

```text
offset relatif : 0x39000
secteur relatif: 0x72
LBA absolu     : 954 + 0x72 = 1068
destination    : 0x801AF800
```

Un `resource_tail_nonzero: PASS` confirme que l'hypothèse B76 peut être testée
contre de vraies données au lieu d'être une supposition purement dynamique.

## 3. Suite de checks locale

```sh
python tools/run_static_checks.py
```

Elle exécute :

- compilation syntaxique des scripts Python ;
- validation de `main.c` ;
- tests unitaires du lecteur MODE2/2352 ;
- test du calcul `0x39000 / 0x800 = 0x72`.

## 4. GitHub Actions

`.github/workflows/static-checks.yml` exécute automatiquement les checks ne
nécessitant ni le disque du jeu ni devkitPro.

Le disque n'est volontairement jamais envoyé en CI.

## 5. Ce qui reste manuel

Azahar reste nécessaire pour valider :

- le rendu final ;
- les transitions réellement visibles ;
- les interactions pad ;
- les bugs dépendant d'un état complet RAM/VRAM.

L'objectif suivant est d'ajouter un **snapshot/replay GPU** afin de pouvoir
rejouer un état graphique capturé sans refaire tout le boot.
