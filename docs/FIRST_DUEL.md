> [!NOTE]
> **Jalon historique PC + comparaison 3DS.** Le scénario PC reste l'oracle
> fonctionnel. Depuis septembre 2026, le backend New 3DS a lui aussi atteint un
> duel jouable plusieurs tours, mais avec des limites de performance et de rendu.

# Première partie et premières actions de duel

## Runtime PC — référence

Le runtime PC français a validé une nouvelle partie, les dialogues
d'introduction, le duel contre Simon Muran, la pose d'une carte et le passage au
tour adverse.

![Premier duel](../research/first-duel/duel.png)

![Carte posée](../research/first-duel/card-set.png)

![Tour suivant](../research/first-duel/next-turn.png)

Cette séquence reste l'oracle visuel/fonctionnel du port 3DS.

## Backend New 3DS — état au 25 septembre 2026

La lignée B135.71 atteint également un duel jouable :

- main visible ;
- plusieurs tours ;
- adversaire actif ;
- rendu 3D fonctionnel.

Différences encore ouvertes :

- ~12–15 FPS en situation normale ;
- ~4 FPS pendant certaines attaques ;
- certaines images de cartes ne correspondent pas encore au nom/stats ;
- les dialogues 2D avant/après combat ne sont pas rendus.

Le bug dialogue est actuellement localisé en amont du GPU : la liste C2 contient
5 objets mais `FUN_800408BC` n'est pas exécuté.

## Données PC

Le moteur PC utilise le scheduler HLE, le rendu logiciel et le contrôleur
numérique verrouillé. Les scripts et preuves historiques restent dans
`research/first-duel/`.

## Portée

Ce document décrit le comportement attendu du duel. Pour l'état exact du backend
3DS, voir [CURRENT_STATUS.md](CURRENT_STATUS.md).
