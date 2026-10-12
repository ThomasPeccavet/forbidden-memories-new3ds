# B136.51 — RAM en ligne pour le cœur recompilé

## Pourquoi cette expérience

B136.50 apporte peu ou pas de gain visible dans le combat selon l'utilisateur.
Les améliorations locales du renderer ne suffisent donc pas à expliquer ou
résoudre la lenteur globale. B136.48 avait amélioré la fluidité ressentie,
mais associait le build CLEAN et des callbacks RAM plus rapides. B136.51
cherche à supprimer le coût d'appel de ces callbacks dans le cœur natif.

## Modification

`rebuild_generated_release.sh` transforme des copies des shards français
SLES_039.48 dans son dossier de build, puis les compile. Les originaux restent
inchangés. `tools/inline_native_memory.py` remplace uniquement les appels C
`cpu->read/write_word/half/byte` et `psx_cyc_load_word/half/byte(cpu, ...)`.
Commentaires, littéraux, affectations de callbacks et arguments sont conservés.
Un build sans site transformé échoue explicitement, plutôt que de tester
accidentellement l'ancien cœur. Le rebuild annonce le nombre de sites.

`fm_native_memory.h` utilise la même RAM et la même taille que fm_memory_init.
Pour les callbacks standard, une adresse physique dans les 8 Mo des miroirs
RAM est ramenée aux 2 Mo et vérifiée sur toute la largeur. Les helpers alignés
B136.48 gardent leur solution byte par byte pour les pointeurs non alignés.
Les callbacks personnalisés, accès hors RAM et spans incomplets prennent le
chemin d'origine. Les écritures touchant les deux plages de watch restent
sur le callback, même si le même objet généré sert au build PROFILE.

Lorsque PSX_ENABLE_BLOCK_CYCLES est défini, les appels de chargement cyclés
restent les helpers d'origine. Sinon, seules leurs lectures RAM standard
sont spécialisées ; les autres accès appellent toujours le helper original.
Les quatre arguments restent évalués exactement une fois. Les barrières de
store, hooks PGXP et compteurs de cycles qui entourent ces appels ne sont
pas supprimés ou transformés. VSync, cadence SEQ, CD, input et présentation
restent aux réglages actuels. Le changement couvre le cœur résident entier,
pas une réécriture de la logique du combat ni de l'interpréteur des overlays.

## Validation et limites

69 tests hôte passent. Le vrai module mémoire est testé dans quatre
combinaisons CLEAN/PROFILE et comptage détaillé activé/désactivé. Une fixture
avec les formes d'appels générées est compilée avant et après transformation :
résultat et RAM identiques, appels des helpers cyclés préservés lorsqu'activés.
Les tests couvrent quatre alignements de stockage, cinq alias RAM, word/half/
byte, accès non alignés, limites, scratchpad/MMIO/BIOS, override des callbacks,
watch events, réinitialisation sur une autre RAM et RAM absente. Des tests
séparés vérifient la transformation, les arguments et les sources originales.
La CI ARM compile aussi la fixture transformée avec et sans comptage détaillé.

Le ROM, l'ensemble des shards générés locaux de l'utilisateur et Azahar ne
sont pas disponibles pour une validation complète ici. Le gain réel dépend
de la proportion des accès RAM, du compilateur et de la pression sur le cache
d'instructions ; aucune promesse de 30 FPS ne découle des tests de composants.
Tester le build normal PROFILE=0 UNAI=1 et recharger le même combat corrigé.
