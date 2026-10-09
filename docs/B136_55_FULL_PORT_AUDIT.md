# Audit du port — B136.55

Date : 9 octobre 2026. Référence distante auditée : `aa4693758aaaf6c3530bdf8f341373501ee84be6`, branche `fix/b136-spu-dma4-mmio-audit`.

## Conclusion

Le projet exécute réellement le jeu : code résident recompilé, overlays interprétés, RAM/VRAM PS1, chargements du disque, rendu GP0/GP1, vidéo STR/MDEC et décodage XA. Ce n'est pas une reproduction des menus. Mais ce n'est **pas encore un port complet ni un runtime PS1 fidèle**. Le fonctionnement repose toujours sur des raccords spécifiques à Forbidden Memories, des initialisations HLE et des corrections d'état.

Les deux fonctionnalités réellement manquantes les plus nettes sont **l'audio SPU** et **la sauvegarde carte mémoire**. Les risques transversaux sont les interruptions, les horloges, la cohérence des snapshots et les bridges qui modifient les états du jeu. La performance de l'IA reste une question ouverte : aucun profil de son calcul ne démontre encore une cause précise.

Aucun pourcentage d'achèvement n'est proposé : atteindre un duel ne mesure pas la couverture de la campagne, des overlays et des périphériques.

## Périmètre et limites

Inspection statique du frontend 3DS, de ses modules CPU/mémoire/BIOS/CD/GPU/audio/média, des en-têtes, du pipeline de génération, des workflows et des tests. Les 15 fichiers C/C++ propres au port représentent 46 111 lignes, dont 21 686 dans `main.c`. Inventaire des points d'interception et inspection ciblée de leurs branches, pas preuve formelle de chaque ligne.

Le HEAD distant a été contrôlé. Les arbres local et distant du correctif sont identiques. La version de référence dispose de 72 tests hôte réussis et des vérifications ARM réussies. Ce sont des tests de composants, **pas une exécution complète du jeu**.

Le répertoire privé `work/` et le cœur résident généré complet ne sont pas disponibles ici ; aucun fichier `work/` n'est suivi par Git. La ROM, Azahar et une console physique ne sont pas disponibles pour cet audit. Le runtime PSXRecomp externe, son GTE et chaque fonction générée ne peuvent donc pas être certifiés à partir de ce checkout. Les constats ci-dessous séparent explicitement manque confirmé, divergence confirmée et risque à reproduire.

## 1. État fonctionnel

| Domaine | Ce qui existe | Ce qui manque pour le déclarer complet |
|---|---|---|
| Boot et menus | Chemin testé par l'utilisateur, sélection et nouvelle partie | Boot sans fastboot forcé ; tests depuis démarrage à froid |
| Progression et duel | Intro narrative, dialogues et premier combat atteints | Campagne complète, toutes transitions et overlays |
| CPU | Résident recompilé + R3000A pour code dynamique | Équivalence native/interpréteur, exceptions et load delay |
| CD | BIN brut, ISO9660, callbacks LibCD et transport XA/STR | Erreurs/IRQ/commandes généralisées et chronologie cohérente |
| GPU | Parser, VRAM, DMA2/6, rasteriseur logiciel et Unai partiel | Référence pixel + transitions, masques, dithering, PAL |
| Vidéo | STR, VLC, MDEC, sortie couleur | Cadence, synchronisation audio/vidéo, reprise de snapshot |
| Audio XA | Décodage PCM et soumission NDSP présents | Sortie effective, disponibilité DSP, synchronisation |
| Audio SPU | Quelques registres de synchronisation et séquenceur exécuté | RAM SPU, voix, ADPCM, ADSR, mélange et effets |
| Sauvegarde | Snapshot de debug version 3 | Carte mémoire et sauvegarde/chargement natifs |
| Distribution | Makefile et compilation de composants ARM | Reconstruction fraîche et lien final automatisés |

## 2. Bridges actifs : à inventorier, pas à supprimer en bloc

Un HLE peut rester dans un port final si son contrat observable est fidèle. Exécuter une fonction native dans un contexte CPU isolé est également une méthode valable. Le problème concerne les bypass qui fabriquent une condition de succès ou modifient le déroulement sans contrat suffisamment validé.

| Raccord | Preuve dans le code | Statut et travail |
|---|---|---|
| FASTBOOT 401A4 | `main.c`, vers 13306 : après quatre callbacks et le VSync attendu, réécrit PC/SP/RA et retourne zéro | Actif, retour forcé. Remonter la vraie condition d'attente et remplacer le bypass |
| FASTBOOT 43E3C | `main.c`, vers 13367 : retour forcé si aucun secteur après 300 frames | Filet de sécurité actif. Il peut masquer un échec CD ; transformer en erreur explicite après réparation |
| DIRECT-2DF | `main.c`, vers 13411 : écrit `8009C60D=8`, impose sentinelle et pilotage direct | Fallback actif sous conditions. À retirer après preuve du chemin startup naturel |
| Service VBlank spécifique | `fm_runtime_shim.c`, `fm_runtime_service_vblank_hle`, vers 1266 | Modifie directement `80093EE8` et satisfait `8009C428` par rapport à `8009C424`. Ce n'est pas une chaîne d'exception CPU complète |
| Callback VBlank/Timer isolé | `main.c`, `fm_execute_guest_vblank_callback` et `fm_execute_guest_timer_callback` | Exécute du vrai code, mais ordre, contexte et préemption restent spécifiques au port |
| Fin DMA4 → TestEvent | `fm_memory.c`, vers 2440 ; `fm_runtime_shim.c`, vers 2780 | Completion immédiate sans payload SPU ; READY publié pendant le polling de l'événement exact |
| LibCD init | `main.c`, vers 15183, interception `8007B53C` | Remplit directement files, flags et pointeurs Psy-Q. À valider contre les états observables de la fonction originale |
| Commandes CD/callbacks | `main.c`, `8007A1D4`, `8007BA00`, `fm_b33_schedule_cd_callback` | Une commande en attente, résultat synthétique et livraison frame+1 ; utile mais modèle incomplet |
| Nettoyage chargement B50 | `main.c`, vers 14078 | Déclenche explicitement le vrai finalizer quand les flags ne sont pas nettoyés. Comprendre pourquoi le chemin original ne le déclenche pas |
| Main de duel B135.71 | `fm_runtime_shim.c`, vers 1606–1651 | Scan de chaîne, puis force `8009C4B8=1` si une main existe et gate=0. Pas protégé par PROFILE dans ce bloc |
| Repair OT | `main.c`, `fm_repair_ot_sentinel`, vers 8100 | Répare un lien précis org-4 en FFFFFF. Borné, mais mutation RAM : réparer la cause OTC/lifetime plutôt que maintenir une réparation permanente |
| Récupération couche main B135.64 | `main.c`, vers 15760 | Peut fusionner une couche manquante si état de corrélation et forme reconnus. Activation dépend aussi des producteurs de cet état ; ne pas compter chaque occurrence textuelle comme une activation actuelle |
| Entrées menu/clavier | `main.c`, B81/B102/B103 | Injection adaptée à SU et à la saisie du nom. Valider repeat, fronts, maintien et changement de scène |
| Présentation | `main.c`, vers 17378 et suite | Normalisation des coordonnées, sélection/composition et reseed après quick-load. Vérifier les modes 24 bits et transitions ; ne pas substituer silencieusement une page à GP1 |

Les HLE de VLC, LoadImage, GsSortOt et swap RAM sont une autre catégorie : optimisations candidates à conserver, à condition de tester RAM, VRAM **et registres** contre les chemins de référence et de garder un fallback transactionnel.

## 3. Bridges historiques non actifs dans le boot normal

- `fm_service_vblank_callback_bridge` (ancien B11) n'a pas de site d'appel trouvé dans `main.c` : sa présence ne prouve pas un effet actuel.
- Fin STR forcée : `g_str_intro_skip_pending` est initialisé et réinitialisé à zéro. Les bypass existent encore, mais ne s'arment pas dans le démarrage normal actuel. Un vieux snapshot peut restaurer ce flag.
- L'ancien étirement START B72 est décrit comme retiré. Les compteurs conservés ne constituent pas un bridge.
- Les mots « forced », « fallback » ou « hack » des compteurs ne sont pas un inventaire fiable des mutations actives.

Travail : supprimer progressivement les chemins morts après couverture de tests, et garder un registre unique des HLE/bridges avec raison, condition, effet et test de référence.

## 4. Divergences et erreurs de contrat confirmées

### A. ResetEntryInt est traité deux fois, avec deux comportements

`main.c` vers 14300 court-circuite B0:18, renvoie zéro et continue avant le BIOS HLE central. Dans `fm_runtime_shim.c`, B0:18 mémorise l'ancien hook, efface `g_bios_entry_hook_addr` puis retourne l'ancien hook.

**Le chemin main ne réalise donc pas le contrat du handler central.** Risque : hook conservé et retour incohérent quand un ancien hook existe. Correction : routage unique, puis test avec hook non nul. Aucun lien causal prouvé avec le ralentissement du duel.

### B. Interruptions Timer : I_MASK vérifié, masque CPU absent du chemin

`fm_runtime_take_timer_callback` ne reçoit pas CPUState et consulte seulement I_STAT/I_MASK et l'événement BIOS. Son appelant ne vérifie pas `cop0[12]`. Pourtant EnterCriticalSection/ExitCriticalSection modifient précisément le SR dans le shim.

**La livraison Timer peut contourner la section critique CPU dans ce chemin.** Il faut définir le contrat des callbacks HLE puis respecter le masque global et les conditions d'exception. Ne pas simplement ajouter un test SR sans vérifier l'état initial et la manière dont le boot active les IRQ : cela peut reproduire les freezes historiques.

### C. Interpréteur : différences avec le pipeline R3000A

`fm_interp.c` traite ADD/ADDU ensemble et indique explicitement que l'exception d'overflow est ignorée. Les chargements LB/LH/LW écrivent via `set_reg` immédiatement ; le pipeline load-delay conservé dans CPUState n'est pas reproduit par ces branches comme un load delay matériel.

Divergence confirmée du modèle CPU ; impact sur une fonction précise à démontrer. Les delay slots de branche sont traités et ne doivent pas être confondus avec le load delay. Travail : microtests MIPS pour dépendances immédiates, branche+load, overflow, accès mal alignés, COP0/RFE, puis comparaison interpréteur/résident.

### D. Snapshot non atomique

Le chargement quick-state lit RAM puis VRAM directement dans les buffers vivants. Une lecture incomplète peut donc retourner une erreur après avoir modifié une partie de l'état courant. La sauvegarde écrit directement le fichier final.

Correction : lecture/validation en tampon avant commit ; fichier temporaire + remplacement après écriture complète ; garde de compatibilité de build/ROM. C'est un risque concret d'intégrité, pas une preuve que les snapshots actuels sont corrompus.

## 5. Fonctionnalités réellement absentes

### Audio SPU — chantier majeur

`fm_dma4_try_start` appelle immédiatement `fm_dma4_complete`. Le commentaire et l'implémentation confirment que le payload n'est pas écrit dans une RAM SPU. Seuls quelques registres sont modélisés. `fm_audio.c` reçoit le PCM du décodeur XA ; ce n'est pas un mixer SPU.

Pour obtenir musiques SEQ et effets : RAM SPU 512 Kio, DMA/PIO réels, registres des 24 voix, ADPCM, pitch, ADSR, key-on/off, volume/pan et mélange ; ensuite bruit, modulation, IRQ SPU, réverbération et mélange CD. Le séquenceur exécuté sans ces voix ne produit pas les sons attendus. Distinguer séquenceur lent et absence de sortie audio.

### Carte mémoire — indispensable au port complet

B0:4A/4B/4C reviennent sans implémenter un périphérique carte mémoire. Les initialisations `_bu_init` sont également des no-op. `write` ne sert ici qu'aux descripteurs stdout/stderr.

Il faut couvrir les appels réellement utilisés par le jeu, leur protocole/events, blocs et répertoire de carte, persistance sur SD, erreurs et sauvegarde atomique. Une sauvegarde native doit se recharger après redémarrage et permettre une progression normale. Le quick-state de debug ne remplace pas cela.

## 6. Horloges et callbacks : zone à stabiliser

B136.54 conserve la dette VBlank ; B136.55 découpe Timer2 aux échéances, sans multiplier les VBlank. Le test de 10 s retrouve 738 IRQ pour la configuration cible E000 si chaque échéance est acquittée.

Cela ne transforme pas le runtime en machine cycle-exacte : Timer0/1 restent approximatifs, VBlank reste à 60 Hz alors que le jeu est PAL, VSync mode1 utilise 15 625 HSync/s, et Timer1 HSync utilise 314 pas par tick. Le temps CD progresse également avec le temps hôte ; le code du jeu peut n'effectuer que 15–20 mises à jour/s.

Risques : horloges relatives divergentes sous charge, attentes satisfaites tard, musique/vidéo déphasées. Le service Timer2 en rattrapage reste groupé au début d'une tranche, pas positionné à l'instant exact dans l'exécution guest.

Plan : contrat explicite PAL/VSync/timers/CD/SEQ ; échéances communes ; tests de pause, retard, sections critiques et reprises. Ne pas passer simplement 60 à 50 ni accélérer globalement le temps.

Le callback Timer isolé possède une limite de 100 000 handoffs × 512 instructions : borne finie, mais potentiellement très longue. Le budget principal de 12 ms ne borne pas ce callback de la même manière. Mesurer puis rendre son exécution reprenable ou utiliser un chemin natif validé, sans abandonner une ISR au milieu.

## 7. CD, vidéo et audio XA

Le disque est nécessaire : il fournit les données, overlays, images, sons et vidéos ; son absence n'est pas compensée par le code recompilé. `disc.c` vérifie taille exacte et PVD, mais pas le hash complet à l'ouverture. Un disque de même taille n'est donc pas une preuve de correspondance au profil.

Chaque lecture brute fait fseek/fread d'un secteur ; cela peut coûter lors d'un chargement ou streaming. Ce n'est pas une preuve du coût dominant de l'IA au repos. Tester un cache/prélecture borné seulement après preuve d'un hotspot I/O.

Le CD MMIO de `fm_media_cd_read` fournit un état très réduit. Les résultats LibCD sont construits pour les usages observés, pas un contrôleur complet avec FIFOs/IRQ et erreurs. Les writes directs aux variables Psy-Q restent une dépendance au binaire FR.

STR publie les frames directement dans le ring du jeu aux adresses `800F70xx` : bridge fonctionnel spécifique. Limites explicites : 20 chunks, ordre d'entrée contrôlé, largeur ≤480, hauteur ≤256. XA rejette des paramètres réservés et emphasis. Aucun de ces rejets ne prouve un problème sur les fichiers actuels ; inventorier les variantes réellement utilisées.

Si NDSP échoue, `fm_audio_ready`/`fm_audio_push` laissent progresser les médias sans son. C'est voulu pour éviter un blocage, mais une erreur DSP doit être expliquée à l'utilisateur. Les anciennes traces `dsp=D880A7FA queued=0` ne doivent pas être interprétées comme absence de décodeur XA.

## 8. Snapshots : sauvegarde partielle du système

Le header version3 couvre CPU, mémoire, GPU, BIOS/runtime et quelques flags frontend. Il ne sérialise pas l'ensemble des variables CD/callbacks de main, l'assemblage STR/XA, les buffers NDSP, ni le snapshot MDEC complet.

Charger un état pendant un streaming ou une interruption peut donc restaurer une RAM cohérente avec un périphérique hôte incohérent. Depuis un redémarrage, certains états restent au reset ; dans la même session, certains peuvent rester ceux du futur.

Priorité : schéma explicite de chaque sous-système, ou restriction documentée des snapshots aux points sûrs avec annulation propre des opérations. Tester froid/chaud, pause, changement d'overlay, dialogue, duel et vidéo. Conserver la migration du format actuel, sans prétendre que version3 est un état matériel complet.

## 9. Graphismes et performance

Unai est une expérience partielle : familles 34h–37h, 3Ch–3Fh et 64h–67h ; le reste passe dans les chemins précédents. Masques, texture window et aliasing dangereux ont des fallback. Le dithering est désactivé. Une comparaison entre deux chemins du port n'est pas toujours un oracle PS1 indépendant.

Le présentateur peut normaliser des coordonnées et reseeder une page selon l'état restauré. Tests nécessaires : double-buffer, noir légitime, CLUT, modes 24 bits, superposition et transitions. Les incidents de cartes mal associées et de menus superposés justifient cette couverture.

La main de duel B135.71 scanne jusqu'à 8192 nœuds dans le shim, hors PROFILE pour le bloc actif, et peut forcer le gate de rendu. Cela représente une **piste de coût et de fidélité**, non une mesure du coût dominant actuel. Les tests protègent aujourd'hui ce filet de sécurité : ils devront évoluer au moment de le retirer, pas seulement être contournés.

`main.c` mélange boot, IRQ, CD, HLE, rendu, inputs, snapshots, diagnostics et scheduler. Ses 21 686 lignes rendent l'ordre des interceptions fragile. Extraire ces responsabilités en modules sans changer les comportements est un travail nécessaire de maintenabilité, pas une promesse de FPS.

### IA lente

Pistes distinctes : calculs dans un overlay interprété ; callbacks/IRQ coûtant du temps CPU ; temporisations en frames et mises à jour de jeu insuffisantes ; rasterisation coûteuse avant le tour suivant. Le profil ancien d'une scène ne tranche pas entre elles.

Travail précis : capturer un tour IA fixe, identifier début/fin de décision et début d'action, relever les PC et volumes d'instructions entre ces bornes, distinguer calcul d'attente, puis traduire/optimiser une fonction prouvée. Ne pas changer ses décisions ni supprimer arbitrairement une attente. Aucun gain chiffré sérieux possible avant ce diagnostic.

## 10. Build, tests et documentation

- CI ARM compile des objets et vérifie le raccord Unai ; elle ne lie pas le port complet avec le cœur généré et n'exécute pas la campagne.
- `rebuild_generated_release.sh` sélectionne un dossier généré compatible par parcours trié des chemins. Le commentaire « newest » n'est pas une validation de fraîcheur, de hash ou de profil.
- Un checkout PSXRecomp déjà présent dans bootstrap doit être contrôlé systématiquement contre le commit attendu, pas seulement réutilisé.
- Il manque un manifeste liant ROM/exe/export Ghidra/générateur/runtime/toolchain/flags au binaire final et au snapshot.
- Le workflow lab vise une ancienne branche B135.87 ; il n'est pas la preuve d'une validation automatique de la branche actuelle.
- README/roadmap datés du 29 septembre annoncent XA absent et un verrou boot déjà dépassé selon les essais utilisateur. Les nombreux blocs historiques de CURRENT_STATUS doivent être clairement archivés.

Les 72 tests sont précieux : mémoire/MMIO, DMA, médias, filtres XA/PCM, pixels, cache, horloge, callbacks et transformations. Ils ne certifient ni la campagne ni chaque interception main ni la vitesse réelle sur New3DS. Ajouter des replays depuis données privées et scénarios bout en bout ; ne pas écrire des tests qui confirment uniquement un bridge parce qu'il existe.

## 11. Plan de travail priorisé et critères de sortie

| Priorité | Lot | Critère de sortie |
|---|---|---|
| P0 | Baseline et reproduction | Un boot froid + menu + intro + duel reproductibles, versions/ROM identifiées |
| P0 | Registre des bridges | Chaque interception active classée, condition/effet/test connus |
| P0 | Contrats IRQ/BIOS | ResetEntryInt unique ; tests SR/I_MASK/sections critiques et contexte restauré |
| P1 | Snapshots fiables | État CD/media/MDEC cohérent ou points sûrs explicitement limités ; chargement atomique |
| P1 | Sauvegarde native | Sauver/charger après fermeture sans quick-state, progression persistante |
| P1 | SPU audio réel | Sons et musique SEQ audibles, DMA payload et voix vérifiés |
| P1 | Rythme global et IA | Durées des décisions/animations comparables à une référence ; charge et attentes séparées |
| P2 | CPU/GTE | Microtests et différentiel native/interpréteur ; exceptions nécessaires couvertes |
| P2 | CD généralisé | Erreurs et callbacks corrects, streaming sans mutations Psy-Q arbitraires |
| P2 | GPU/vidéo | Replays pixel/rendu, modes/CLUT/transitions et synchronisation XA/STR |
| P2 | Débridage boot/OT/input | Remplacer un bridge à la fois par son mécanisme réel, sans régression |
| P2 | Build complet | Reconstruction privée depuis checkout propre, manifestée, lien final et smoke test |
| P3 | Campagne/console | Fin du jeu, sauvegardes, overlays et endurance sur New3DS physique |

Pour l'objectif immédiat « jouer correctement », mener en parallèle dans la roadmap : **performance/rythme**, **sauvegarde**, **SPU**. Pour réduire les freezes, traiter d'abord les contrats IRQ et snapshots. La meilleure prochaine correction isolée issue de cet audit est le routage de ResetEntryInt avec son test ; le meilleur prochain diagnostic de performance est le tour IA identifié, pas un nouveau multiplicateur de temps.

## 12. Ce que cet audit ne prétend pas prouver

Ni 100 % de décompilation sémantique, ni compatibilité de chaque instruction, ni absence de bug, ni objectif 30 FPS garanti. Les adresses et règles sont spécifiques à SLES-03948. Un port complet peut conserver des HLE fidèles et continuer de lire un disque fourni par l'utilisateur : supprimer tout HLE ou toute dépendance au BIN n'est pas une condition nécessaire.

Aucune modification d'exécution n'est incluse dans ce rapport. L'objectif est de rendre le travail restant vérifiable et d'éviter de recommencer les mêmes essais sans contrat clair.
