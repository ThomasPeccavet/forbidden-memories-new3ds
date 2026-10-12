# B136.47 — sélection des miniatures de cartes

## Cause

La sauvegarde de duel fournie associe les cinq cartes 411, 282, 202, 336 et
198 aux bonnes positions du cache compact 8015C424. Leurs blocs de 0x580
octets sont copiés sans différence dans le cache de deck 8018C2D8, puis
vers les bons pixels et palettes en VRAM. Les miniatures extraites de la VRAM
reproduisent celles de la capture : le problème précède le rendu Unai.

800247F0 trie les IDs et demande une plage continue du premier au dernier.
Le callback 800246A8 active le bit 0x200000 de C460 pour sauter les cartes
absentes. 80013B44 décrémente le nombre d'octets restants dans tous les cas,
mais n'appelle pas 8007E968 (CdGetSector) pour ces secteurs ignorés.
L'ancien pont avançait uniquement lors de cet appel : le secteur physique
et le rang de miniature divergeaient après le premier trou dans la liste.

## Correction

Au début de chaque callback DataReady, réserver le LBA courant et avancer
le curseur une fois. CdGetSector utilise ce LBA pendant le callback sans
nouvelle avance. Les appels hors de ce callback conservent leur chemin
existant. Une nouvelle requête réinitialise le curseur, y compris lorsqu'elle
réutilise le même pointeur, LBA et nombre d'octets.

## Validation et limites

Le test hôte exécute la fonction de production sur la liste des 50 IDs de
la sauvegarde, avec les secteurs intermédiaires ignorés. Il vérifie les cinq
cartes de la main, les lectures continues, le dernier fragment et les
réutilisations de requête. Les contrôles statiques et la compilation ARM
sont nécessaires ; cela ne remplace pas une validation des illustrations
avec le disque réel dans Azahar.

Ce changement ne répare pas les octets déjà chargés dans une quickstate.
Recharger un duel par le jeu ou démarrer une nouvelle partie sans restaurer
l'ancienne quickstate. Aucun gain de FPS n'est annoncé pour ce correctif.
