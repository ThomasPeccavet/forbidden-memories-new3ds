> [!NOTE]
> **Analyse historique d'overlay.** Cette page décrit la cartographie statique de
> SU.MRG. Le verrou actif du 29 septembre 2026 se situe désormais plus tôt dans
> le startup, dans la chaîne CD / événement BIOS / SPU / DMA4. Voir
> [B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).

# Piste SU.MRG et chargement par étapes

Analyse statique des exports `research/ghidra-fr/export/pseudo-c`.

## Chemin startup vers SU

`80012A44` appelle `80043E3C(0)`.

La fonction :
- initialise plusieurs états ;
- prépare une première requête avec `80014D38` ;
- exécute l'overlay `801680F4 / 80168160` ;
- poursuit plusieurs initialisations ;
- passe par un second `80043CD4` ;
- puis doit atteindre `80043DC8`, `800159F4`, `8002CF60` et enfin
  `8006B560`.

Le diagnostic B136 a confirmé que le startup courant s'arrête **avant**
`8006B560`, dans le second `80043CD4`.

## Première requête historique

`80043E3C` appelle notamment :

~~~text
FUN_80014D38(0,0,0x2503,0x25,FUN_800438D4,0,0)
~~~

`80014D38` passe la requête à `800138B4`, puis `8001385C`.

Le pipeline récurrent reste :

~~~text
80012C50
 -> 80012F70
 -> 80014978
 -> 80014478
~~~

## Chargement SU par FUN_8006B350

Une fois le startup libéré, `8006B560` configure une requête associée à :

~~~text
M:\mrg\SU\SU.mrg
~~~

`8006B350` découpe ensuite le chargement :

| Index | Taille | Destination |
| --- | ---: | --- |
| 0 | 0x20000 | tampon DAT_8009C4B0, mode 2 |
| 1 | 0x10000 | même tampon, mode 2 |
| 2 | 0x1000 | 0x801DD000, mode 1 |
| 3 | 0x8000 | PTR_DAT_8001002C, mode 1 |
| 4 | 0x800 | 0x801AF800, mode 1 |

Somme :

~~~text
0x39800 = 0x73 * 0x800
~~~

La zone `PTR_DAT_8001002C` a été observée vers `0x80180000`, utilisée par des
images overlay dynamiques.

## Ce qui a déjà été confirmé

Les passes précédentes ont prouvé que :
- le bloc `0x80180000` contient du code MIPS cohérent ;
- SU contient bien le chemin menu ;
- les overlays dynamiques peuvent être exécutés via fallback R3000A ;
- le menu et les écrans suivants ont déjà été atteints dans les branches B135.

Voir :
- [SU_PROBE_RESULTS.md](SU_PROBE_RESULTS.md)
- [SU_MENU_ANALYSIS.md](SU_MENU_ANALYSIS.md)

## Verrou actuel avant SU

La requête actuellement bloquée n'est pas encore le chargement SU final.

Elle est :

~~~text
LBA       = 0x3172D
remaining = 0x2000
cmd       = ReadN
~~~

Elle dépend d'une synchronisation SPU/DMA4 et d'un événement BIOS
`F0000009/0x20`.

Le prochain objectif est donc de libérer cette chaîne avant de réinvestiguer
SU lui-même.

## Conséquence

Ne pas considérer SU comme cassé tant que le startup B136 n'a pas repassé :

~~~text
post681_43dc8
post681_159f4
...
8006B560
~~~

La priorité actuelle est documentée dans :
[B136_STARTUP_CD_SPU_DMA4.md](B136_STARTUP_CD_SPU_DMA4.md).
