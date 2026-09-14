# Analyse française — observations vérifiées

Source : disque fourni par Thomas, inventorié dans `profiles/SLES-03948.json`.
Les empreintes identifient cette copie ; elles ne certifient pas l'authenticité
commerciale du dump.

| Paramètre | Valeur |
|---|---|
| Programme de démarrage | SLES_039.48 |
| Taille du programme | 1 902 592 octets |
| Charge utile, hors en-tête PS-X EXE | 1 900 544 octets |
| Chargement | 0x80010000 |
| Fin exclusive | 0x801E0000 |
| Point d'entrée | 0x800128CC |
| Pile dans l'en-tête | 0x801FFFF0 |
| GP établi par le démarrage | 0x8009C298 |

Le démarrage efface [0x8009C408, 0x800FFC30), établit la pile à
0x801FFFF8 d'après la valeur initiale en 0x8009C2A0 et appelle 0x80012A44.
Cette dernière adresse est un candidat pour l'initialisation principale,
pas un nom de fonction original retrouvé.

Les archives SU.MRG, SD_SE.DAT, SD_BGM.DAT, WA_MRG.MRG, MODEL.MRG,
MASTER.XA et MOVIE.STR sont inventoriées. Leur contenu n'est pas encore décodé.
Les flux XA/STR peuvent utiliser des secteurs Form 2 : leur extraction exige
un traitement spécifique. Le script n'extrait pas ces archives.

## Réutilisation des travaux PC

[Configuration du projet PC](https://github.com/Unchiga/YuGiOhForbiddenMemoriesRecomp/blob/main/game.toml) :
SLUS-01411, entrée 0x800129D8. Le delta observé de 0x10C au point d'entrée
ne prouve pas un décalage uniforme. Ne pas réutiliser les adresses américaines,
retirer la validation du disque ou appliquer ce delta globalement.

## Limites de la première analyse automatisée

L'analyse Ghidra fournie est une première passe statique : elle ne couvre pas
nécessairement les overlays, les destinations d'appels indirects, les tables de
saut ou tous les chemins du jeu. Les résultats doivent être confrontés au
comportement PS1. Le contexte GP mérite une validation spécifique ; le script
n'applique pas sa valeur globalement aux zones non identifiées.

API utilisées :
- https://ghidra.re/ghidra_docs/api/ghidra/app/script/GhidraScript.html
- https://ghidra.re/ghidra_docs/api/ghidra/app/decompiler/DecompInterface.html

Les scripts Ghidra sont préparés mais n'ont pas encore été exécutés. La présence
de `COMPLETE.txt` signifie que l'export a terminé, pas que toutes les fonctions
ont été décompilées : consulter la colonne status de functions.tsv.
