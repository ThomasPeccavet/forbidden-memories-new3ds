# Tests automatisés de bring-up

Dernière mise à jour : **25 septembre 2026**.

## Checks statiques

```sh
python tools/validate_main_c.py 3ds/source/main.c
python tools/run_static_checks.py
```

Le validateur vérifie notamment :

- doublons de `case` ;
- définitions static dupliquées ;
- marqueur BUILD ;
- vrais marqueurs de conflit Git.

Le faux positif sur les séparateurs décoratifs `=======` a été corrigé.

## CI GitHub

`.github/workflows/static-checks.yml` exécute les checks ne nécessitant ni
devkitPro ni le disque.

Les branches récentes ajoutent des tests de régression pour :

- B135.74 PROFILE/CLEAN ;
- B135.75 fast path interpréteur ;
- B135.76 presenter post-duel ;
- B135.77 draw-page priority ;
- B135.78 arbitration conservatrice ;
- B135.79 dialogue pipeline ;
- B135.80 table C2 / indirect dispatch.

Ces tests valident la structure du correctif et les invariants importants ; ils
ne remplacent pas le test Azahar.

## SU.MRG

```sh
python tools/validate_su_layout.py /chemin/vers/disc.bin
```

Le disque n'est jamais envoyé en CI.

## Ce qui reste manuel

Azahar reste nécessaire pour :

- transitions visibles ;
- dialogues ;
- duel ;
- entrées pad ;
- save-states ;
- performance réelle ;
- bugs dépendant de RAM/VRAM complète.

Le test manuel actuellement prioritaire est B135.80 sur le premier villageois.
