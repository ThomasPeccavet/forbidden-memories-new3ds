# B136.53 — cache des sprites neutres

B136.52 n'a pas apporté de gain perceptible selon l'utilisateur. La capture
du menu deck/coffre contient 477 sprites, dont 440 de couleur neutre et
80 tuiles de fond 32×32. Le coût du tri n'a pas été démontré dominant.

## Chemin optimisé

Le frontend Unai utilise un cache direct de 128 entrées, environ 1,6 Mio
de stockage statique, pour les sprites palettés 4/8 bpp opaques au sens
GP0 (sans mélange), raw ou neutres. Chaque entrée contient les octets
source, la palette et les pixels décodés. Une texture entièrement non
transparente utilise des copies de lignes ; sinon les texels nuls préservent
le destination. Le bit15 des couleurs est conservé.

Le cache accepte au maximum 128×64 pixels et 4096 pixels, sans wrapping UV.
Le clipping et les offsets suivent Unai. Les gardes du frontend concernant
les fenêtres de texture, masques, aliasing et limites VRAM restent actives.
Modulation, mélange, 16 bpp et cas hors limites utilisent Unai existant.

Chaque hit exige une comparaison exacte des octets source de toutes les
lignes utilisées et de la palette entière (16 ou 256 couleurs). Toute
modification invalide l'entrée, y compris les uploads, copies, changements
de palette et quick-load au même pointeur VRAM. Aucun hash de contenu ni
événement d'invalidation supposé complet n'est utilisé.

Pas de modification du rythme VSync, SEQ, CD, associations carte/image ou
de l'écran inférieur.

## Validation et limites

Comparaison de toute la VRAM avec le chemin Unai sans cache sur 400 cas
4/8 bpp, raw/neutre, alignements et clipping variés, hits répétés et mutations
de texture/palette. Cas supplémentaires : texels transparents, bit15,
lignes entièrement opaques, modulation, mélange et wrapping en repli.

Un benchmark hôte de sprite répété 32×32 a montré environ 1,3–1,4× sur le
chemin transparent testé. C'est une mesure du dessin sur hôte x86, pas une
prédiction de FPS 3DS/Azahar. Le gain total du menu reste à tester avec
`PROFILE=0 UNAI=1` ; aucune garantie de 30 FPS.

Rejeu hôte supplémentaire des 477 sprites extraits de la sauvegarde privée :
100 passages prennent 16,87 ms sans cache et 8,72 ms avec cache (environ
1,93×). Toute la VRAM finale est identique. Les sprites hors périmètre
restent sur Unai ; 17 374 hits et 1 326 misses sont observés. Ce rejeu mesure
seulement ces commandes de dessin, pas l'exécution du jeu ni ses FPS, et
n'inclut pas les autres primitives du menu. La sauvegarde n'est pas publiée.
