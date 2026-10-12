# B136.46 — réduire les retours du moteur d'affichage au host

B136.45 indique 57–65 milliers de sondes natives par fenêtre de deux secondes,
pour seulement 8–9 milliers de blocs exécutés en lots. La boucle principale
refait les tests de callbacks CD/timer, les gardes et le traçage à chaque
retour natif. La suspension 12CD4 est inactive dans ces fenêtres.

Cette modification admet les blocs résidents [80040350,80042BE0) dans le
chaînage natif existant. Ils couvrent les listes d'objets, leur animation et
la fabrication de paquets. Une chaîne peut passer entre cette région et les
routines de paquets 84018–89D60 déjà admises. Les instructions recompilées
et les accès RAM du jeu restent les mêmes. Ce n'est pas un remplacement GTE.

80042538 reste une frontière obligatoire : le host y suit la durée de vie
des paquets de cartes et leur disponibilité pour la protection existante.
Les autres hooks main.c de la nouvelle région sont des observations et
compteurs ; ils ne sont plus forcément visités à chaque retour interne.
Les diagnostics historiques correspondant à ces visites seront incomplets.
Le rapport compact de performance et la production d'images restent actifs.

La borne existante de 2 ms est contrôlée tous les quatre blocs, avec au plus
64 dispatches pour les régions objets/affichage. Les callbacks host restent
servis entre lots. Un appel compilé indivisible peut dépasser cette borne,
comme avant. Les PC CD/BIOS/VSync/STR, le démarrage 43xxx, les overlays et la
frontière GsSortOt 85D98 restent hors de la nouvelle région. Le watchdog et
les arrêts runtime rendent toujours la main avec leur PC exact.

Validation : le test du vrai chaînage couvre une séquence affichage ->
paquets -> 42538, les deux extrémités de la région, les exclusions, le miss,
le watchdog et le retour après 2 ms. Les checks hôte et les objets ARM sont
vérifiés. Le gain et le comportement du combat complet nécessitent l'essai
Azahar de l'utilisateur, avec PROFILE=1 UNAI=1 et la même sauvegarde.
