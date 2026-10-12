# B136.52 — échange mémoire du tri

## Observation

La sauvegarde fournie pour le menu avant combat (deck/coffre) contient un
tri de 90 enregistrements de 16 octets. Le PC est à `8008F6D8`, dans le
helper d'échange, avec 13 octets déjà traités. Une capture seule ne permet
pas de mesurer la part de ce tri dans les 4–7 FPS rapportés.

## Modification

Le checkpoint commun reconnaît l'entrée `8008F6C8` et la boucle
`8008F6D8`. Il vérifie les 15 instructions attendues et remplace l'échange
restant par trois copies RAM, puis restitue les registres MIPS et le PC de
retour. Le dispatch reprend dans la même tranche d'exécution, sans attente
VBlank ajoutée. Le qsort et son comparateur restent inchangés.

Le helper accepte seulement les callbacks mémoire standards, des spans RAM
disjoints non surveillés et une taille d'au plus 256 octets. Les alias qui
se chevauchent, limites, callbacks remplacés, instructions modifiées et
indices incohérents conservent l'exécution existante. Le mode de comptage
détaillé `PSX_ENABLE_BLOCK_CYCLES` conserve également la routine existante.
L'écran inférieur reste vide et les horloges/SEQ ne changent pas.

## Validation

- 69 tests hôte et contrôles statiques passent.
- Comparaison avec l'interpréteur MIPS de production : toutes les valeurs
  CPU et les 2 Mio de RAM sont identiques, pour tailles 0 à 256, plusieurs
  alignements et reprises au milieu de boucle.
- Les chemins de repli n'altèrent ni CPU ni RAM.
- La sauvegarde exacte du menu a été rejouée depuis l'octet 13 sur 16 :
  tous les registres et toute la RAM correspondent à la référence MIPS.
- Test séparé de l'intégration au checkpoint commun et de la reprise du PC.

Essai utilisateur : `PROFILE=0 UNAI=1`, puis recharger la même sauvegarde.
Pas de mesure FPS sur 3DS/Azahar disponible ici : le gain reste à vérifier
en jeu, sans garantie de 30 FPS. La sauvegarde utilisateur n'est pas publiée.
