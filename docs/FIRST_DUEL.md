# Première partie et premières actions de duel sur PC

Validation du 16 septembre 2026, sur le runtime PC français construit dans ce
dépôt. Une nouvelle partie avec le nom de test AAA a été créée ; les dialogues
d'introduction ont été traversés jusqu'au choix Duel face à Simon Muran.

![Premier duel](../research/first-duel/duel.png)

## Résultats observés

- Le clavier de nom accepte les lettres et le déplacement du curseur.
- Le nom est confirmé, le code du duelliste est annoncé et l'introduction
  affiche les personnages et les dialogues français.
- Le choix Duel conduit à la préparation des cartes, puis au plateau 3D.
- Le joueur reçoit cinq cartes ; les deux compteurs de vie affichent 8000.
- Une carte est sélectionnée, placée face cachée sur un emplacement du terrain,
  puis son étoile gardienne est confirmée.
- Start termine le tour : une carte apparaît côté adverse et une nouvelle main
  est présentée au joueur. Son compteur de pioche passe de 35 à 34.

![Carte posée](../research/first-duel/card-set.png)

![Tour suivant](../research/first-duel/next-turn.png)

Le duel n'a pas été terminé. Les dégâts, les fusions, les récompenses, l'audio,
la sauvegarde puis son rechargement et la New 3DS restent à valider. La présence
du code du duelliste ne prouve pas à elle seule une sauvegarde fonctionnelle.
Le moteur conserve sa prise en charge du code dynamique : cette avancée n'est
pas la preuve d'un port intégralement natif ou d'une recompilation de tous les
overlays. Les compteurs de dispatch ne sont pas un pourcentage de couverture.

## Configuration et entrées

La révision du moteur reste `1965b2df424da03483a5370340433a862f78f103`.
OpenBIOS et le binaire PC sont inchangés par rapport à l'essai du premier menu.
Le scénario réussi utilise le scheduler HLE par défaut, le rendu logiciel,
le mode headless et une manette numérique déclarée explicitement :

```toml
[controller]
p1_mode="digital"
lock_mode=true
```

bootstrap_pc.py ajoute maintenant ce bloc aux configurations françaises qu'il
produit. Pour une ancienne configuration, ajouter le bloc une seule fois.
Le profil numérique a fonctionné ; les premiers essais avec le profil implicite
et d'autres durées d'appui ne constituent pas un comparatif contrôlé permettant
d'attribuer tous les problèmes d'entrée au seul mode analogique.

Les boutons injectés sont actifs à zéro : Start `0xFFF7`, Croix `0xBFFF`,
Rond `0xDFFF`, Droite `0xFFDF`. Les appuis sont généralement de dix frames ;
deux appuis de soixante frames ont servi à saisir AAA et déplacer le curseur.
Les commandes TCP acceptées ne suffisent pas à prouver une action : les
captures et la réponse visuelle du jeu ont été vérifiées séparément.

## Incident d'intégrité du disque

À la reprise, la copie de travail du BIN faisait 511336448 octets au lieu de
548427600, avec l'empreinte
`8c6c7dcb5912cda7245cf6cf9208ddd8bd7e552a634393d78ce55ddd4dd17912`.
La cause de cette modification n'est pas établie. Le démarrage avec cette copie
restait dans OpenBIOS. Un essai de scheduler LLE n'a pas résolu le problème ;
il ne faut pas en tirer de conclusion sur le scheduler avec cette entrée invalide.

Une nouvelle extraction depuis disc.zip a retrouvé l'empreinte attendue :
`9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835`.
Avec cette copie et le scheduler d'origine, le scénario a été rejoué depuis le
début jusqu'au duel. Une image de l'introduction vidéo a aussi été capturée ;
la lecture audiovisuelle complète reste non validée.

probe_pc_boot.py refuse désormais un disque dont la taille ou le SHA-256 ne
correspond pas au BIN français connu. Pour un CUE, il vérifie le fichier BINARY
référencé. Le rejet de la copie altérée et l'acceptation de la nouvelle extraction
ont été testés. Ce probe est volontairement limité à ce BIN/CUE français.

## Rejouer et diagnostiquer

Le script accepte maintenant `--input-script` : une liste JSON d'actions avec
une attente en secondes, un masque de boutons facultatif et une durée d'appui.
La séquence des actions de cette session est dans
[inputs.json](../research/first-duel/inputs.json).

```sh
python tools/probe_pc_boot.py --runtime "<build>/fm-pc" --framework "<moteur>" --config "<game.toml avec controller digital>" --bios "<moteur>/bios/openbios.bin" --disc "<disque vérifié>/disc.cue" --output "work/replay-duel" --input-script research/first-duel/inputs.json
```

Utiliser un nouveau répertoire output. Les durées dépendent de la vitesse du
moteur : cette liste provient d'une session surveillée avec des temps de lecture
supplémentaires entre certaines actions. Elle sert de base de rejeu, et ne doit
pas être considérée comme un test déterministe garantissant le même écran sur
toutes les machines. L'option input-script a fait l'objet d'un essai court de
transport complet ; la partie illustrée a été pilotée par une file d'actions
avec vérification des captures aux points de décision.

Les commandes pause/continue/step sont retirées dans cette révision du moteur.
Le probe n'appelle plus pause ; ses réponses sont des observations successives
sur un processus actif, pas un état CPU/GPU atomique. Les premiers essais
renvoyaient explicitement une erreur de pause : aucune réussite n'en est déduite.

[evidence.json](../research/first-duel/evidence.json) contient les réponses du
scénario vérifié, les empreintes des captures et les limites des vérifications.
Deux dumps RAM de 2 Mio ont été conservés localement pour les prochaines
analyses d'overlays ; seuls leurs tailles et SHA-256 figurent dans le dépôt.
Le disque, les dumps RAM et les fichiers utilisateur du jeu ne sont pas publiés.

Prochain jalon : terminer un duel et valider les règles, les récompenses et un
cycle de sauvegarde/rechargement, puis mesurer les dépendances à remplacer pour
New 3DS. Les captures actuelles établissent un début de partie jouable sur PC.
