# B136.56 — BIOS/IRQ et snapshots cohérents

Cette modification traite les contrats BIOS/IRQ et les quick-states. Elle ne constitue pas un port complet de la PS1 : SPU, carte mémoire, exception vectorielle complète et plusieurs bridges restent des travaux distincts. Elle ne promet pas de gain de FPS.

## Changements

- `ResetEntryInt` utilise uniquement le handler BIOS central. Il restitue l'ancien hook, puis le supprime ; le raccourci de `main.c` qui renvoyait systématiquement zéro est supprimé.
- Les livraisons HLE timer, VBlank et DMA vérifient IEC et IM2 dans COP0 SR. Les callbacks timer/VBlank respectent aussi les masques périphériques. Les événements masqués restent en attente. Le VBlank différé est coalescé et repris après démasquage, sans injection récursive pendant un callback CD/DMA.
- L'entrée HLE du PS-X EXE initialise SR à `0x401`, correspondant à l'état après démarrage BIOS, plutôt qu'à zéro. Cela évite de rendre le boot silencieusement incapable de recevoir des IRQ.
- Les callbacks CD, DataReady, cleanup, tick CD et MDEC préservent le CPU entier, dont COP0, GTE, HI/LO et le pipeline. Les callbacks timer et VBlank utilisent déjà un CPU isolé ; IEC est désormais désactivé à leur entrée. Les fonctions de mémoire restent des pointeurs host et ne sont jamais écrites dans un fichier.
- Les callbacks LibCD demeurent une abstraction de bibliothèque : leur progression n'est pas assimilée à une émulation complète du registre d'interruption du contrôleur CD. L'éligibilité CPU est vérifiée pour la completion et DataReady. Les bridges SPU/TestEvent existants sont conservés avec un contrôle des masques.
- Le format v4 ajoute le secteur CD courant, les curseurs et fractions de transport, callbacks CD en attente, phases de boot, attentes VSync, buffers STR, prédicteurs XA, filtres/volume CD, FIFOs/tables MDEC, DMA MDEC et événements DMA4 en attente, ainsi que les buffers PCM en file.
- Une demande de sauvegarde faite pendant un callback attend automatiquement sa fin. Les callbacks actifs et leurs piles host ne sont pas sérialisés.
- Le fichier est lu entièrement, puis son format, schéma, identité du disque, taille, CRC et états internes sont vérifiés avant la restauration. MDEC prépare ses allocations et son parsing avant de remplacer ses anciens FIFOs. Une erreur de lecture/validation/allocation laisse le jeu courant intact.
- Une écriture passe par `.tmp`, puis une rotation récupérable `.bak`. Le fichier précédent est conservé jusqu'à la fin de l'écriture. Une interruption entre les renommages permet de récupérer `.bak` si le fichier principal manque. Ce n'est pas une garantie de durabilité matérielle face à une coupure électrique du stockage FAT.
- Le temps passé dans les entrées/sorties de sauvegarde est une pause explicite : il ne crée pas de rattrapage accéléré de l'horloge ou du transport CD.
- SELECT+X/Y n'injecte plus Triangle/Carré dans les bridges menu/clavier. L'écran inférieur reste vide ; les résultats sont écrits seulement lors d'une opération dans `snapshot-status.txt`.

## Format et compatibilité

Le chemin reste `sdmc:/3ds/fm-new3ds/quickstate-b135.bin` ; seuls les nouveaux fichiers utilisent v4. L'enveloppe contient version, schéma, build, identité du disque et CRC32 du contenu. L'identité utilise quatre secteurs bruts du disque de référence FR ; il s'agit d'une empreinte échantillonnée, pas d'un hash cryptographique du disque complet. Un schéma incompatible est rejeté explicitement, même si le numéro de version est identique.

Les saves v3 sont importées comme **partielles**, uniquement hors streaming vidéo et sans requête CD encore à lire. Une v3 ne contient pas les FIFOs, callbacks et contextes nécessaires à une reprise de chargement ou de vidéo fiable. Le résultat `-7` les refuse dans ces cas. Après un import v3 réussi, créer immédiatement une nouvelle save v4. Une v3 n'avait aucun CRC : son intégrité historique ne peut pas être certifiée rétroactivement.

Les buffers PCM sont réinjectés dans NDSP dans leur ordre. Le buffer en cours de lecture reprend à son début, car le curseur matériel du DSP n'est pas sérialisé. Cela peut répéter au maximum un buffer XA (environ 53 à 213 ms selon le format). Si le DSP est indisponible, le décodage et la vidéo continuent comme auparavant. Ce correctif ne fournit pas le mixeur SPU manquant.

Le presenter est reconstruit depuis la VRAM restaurée. Son ancienne image composite et son historique de pages sont invalidés. Les compteurs de performance ne font pas partie du contrat de reprise.

## Tests automatiques

`python tools/run_static_checks.py` exécute la validation du dispatcher et les tests host. Les nouveaux scénarios exécutent les fonctions de production :

| Contrat | Vérification |
|---|---|
| BIOS Hook/Reset | Restitution de l'ancien hook, suppression, second Reset retournant zéro. |
| Sections critiques | IEC/IM2 et I_MASK fermés : VBlank conservé, compteur inchangé ; après ouverture : service unique et préservation des autres IRQ. |
| Callbacks timer/DMA/CD | Déférés si masqués ou imbriqués, restauration du contexte, borne d'exécution conservée. |
| MDEC | FIFO d'entrée partiel et sortie partiellement consommée rejoués ; parsing invalide ne modifiant aucun état vivant. |
| Médias | Reprise d'une demi-image STR et conservation des prédicteurs XA. |
| DMA | Callback en attente après reset/restauration, livré une seule fois. |
| Audio | Reconstruction ordonnée des buffers en file et du buffer marqué en lecture. |
| Fichier | CRC erroné, mauvaise identité/schéma, troncature et écriture échouée ; fichier précédent préservé et rotation interrompue récupérée. |
| Quick-state | Save différée, restauration CPU/RAM/VRAM/CD/attente VSync ; erreur interne à CRC valide sans mutation ; import v3 idle et rejet v3 pendant chargement. |

La CI compile les objets ARM du port, y compris le nouveau module snapshot et le frontend Unai. Le binaire complet et le comportement dans Azahar nécessitent les fichiers de jeu/générés présents sur le PC de l'utilisateur.

## Vérification dans Azahar

Fermer Azahar et copier l'ancienne save avant compilation. Utiliser la build clean Unai, sans mesures FPS obligatoires.

1. **BIOS/IRQ et entrée EXE** : démarrer normalement depuis Konami, passer le titre avec START, naviguer dans le menu et ouvrir une nouvelle partie. Les boutons doivent répondre ; l'intro doit rejoindre le jeu. Les masques et la valeur retournée par Reset sont vérifiés automatiquement, pas visuellement.
2. **Import de l'ancienne save** : SELECT+Y dans une scène idle, puis lire `snapshot-status.txt`. Attendre `action=load result=0 format=v3-partial`. Si `-7`, revenir à une scène idle via un démarrage normal et créer une save v4.
3. **Save v4 en duel** : SELECT+X, avancer de quelques actions, SELECT+Y. Attendre le retour aux mêmes cartes/LP et tour. Le fichier de statut doit afficher `action=load result=0 format=v4`.
4. **Reprise à froid** : fermer et relancer Azahar, puis SELECT+Y. Même position, mêmes cartes, contrôles fonctionnels. Comparer aussi un menu/deck/coffre pour vérifier la reconstruction de l'image.
5. **Streaming** : sauvegarder pendant la vidéo d'introduction, attendre sa progression, recharger ; vérifier que les images reprennent au bon endroit et continuent jusqu'au titre. Répéter pendant l'intro après le nom. Une save prise pendant un callback est différée jusqu'à sa fin ; `result=1` peut apparaître brièvement avant `0`.
6. **Fichier invalide** : test facultatif décrit ci-dessous. Le jeu courant doit continuer après SELECT+Y ; ne pas tester en supprimant l'unique copie de sauvegarde.

Résultats : `0` succès ; `1` save différée ; `-2` fichier absent/ouverture impossible ; `-3` taille/I/O ; `-4` format/identité/schéma ou renommage ; `-5` lecture/CRC ; `-6` allocation ; `-7` v3 partielle impropre à la reprise ; `-8` état interne invalide ; `-9` empreinte disque non disponible.

### Pull, compilation et lancement (PowerShell)

```powershell
Set-Location "C:\Users\MAO\Documents\forbidden-memories-new3ds"
$testSd = Join-Path $env:APPDATA "Azahar\sdmc\3ds\fm-new3ds"
if (Test-Path "$testSd\quickstate-b135.bin") {
    Copy-Item "$testSd\quickstate-b135.bin" "$testSd\quickstate-before-b13656.bin"
}
git pull --ff-only origin fix/b136-spu-dma4-mmio-audit
if ($LASTEXITCODE -ne 0) { throw "Pull échoué." }
& "C:\devkitPro\msys2\usr\bin\bash.exe" -lc 'cd /c/Users/MAO/Documents/forbidden-memories-new3ds && export DEVKITPRO=/opt/devkitpro && export DEVKITARM=/opt/devkitpro/devkitARM && export PATH=/opt/devkitpro/devkitARM/bin:/opt/devkitpro/tools/bin:$PATH && make -C 3ds PROFILE=0 UNAI=1 -j2'
if ($LASTEXITCODE -ne 0) { throw "Compilation échouée." }
$testApp = (Resolve-Path ".\3ds\fm-new3ds-unai.3dsx").Path
$testAzahar = Join-Path $env:LOCALAPPDATA "Programs\Azahar\azahar.exe"
Start-Process -FilePath $testAzahar -ArgumentList "`"$testApp`""
```

Après chaque SELECT+X/Y :

```powershell
Get-Content "$testSd\snapshot-status.txt"
```

### Test facultatif de rejet (sans perdre la save)

Pendant que le jeu tourne, avec une save v4 réussie :

```powershell
$qsPath = Join-Path $testSd "quickstate-b135.bin"
$goodPath = Join-Path $testSd "quickstate-b13656-good.bin"
Copy-Item $qsPath $goodPath
$qsBytes = [IO.File]::ReadAllBytes($qsPath)
$qsBytes[$qsBytes.Length - 1] = $qsBytes[$qsBytes.Length - 1] -bxor 1
[IO.File]::WriteAllBytes($qsPath, $qsBytes)
```

Appuyer SELECT+Y : le jeu courant doit rester à sa position et répondre. Le statut doit afficher `result=-5`. Restaurer ensuite le bon fichier **avant toute nouvelle sauvegarde** :

```powershell
Copy-Item $goodPath $qsPath -Force
```
