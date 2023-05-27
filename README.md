# CY-Connect
Jeu créé par **Atahan Ozsolak**, **Elias Chekhab** et **Maxime Darcherif** pour **CY Tech**.

(Jeu intégralement en anglais)

**CY-Connect** un est jeu basé sur les règles classiques d'un puissance X, avec certaines fonctionnalités supplémentaires qui rendent le jeu plus dynamique.


## ✅ Règles du jeu
>(Si vous ne connaissez pas les règles du puissance 4, même si c'est peu probable, nous vous invitons à cliquer sur [ce lien](https://fr.wikipedia.org/wiki/Puissance_4) 🙂)


**CY-Connect** se joue à deux. Les joueurs s'affrontent en utilisant chacun une pièce différente qui les distingue (soit le **X**, soit le **O**). 

Les joueurs jouent chacun leur tour en choisissant une **colonne** du tableau où mettre leur pièce. Une fois la colonne choisie, la pièce tombe sous l'effet de la gravité jusqu'à atteindre la position la plus basse disponible dans celle-ci.

Après chaque lancement d'une pièce, le joueur peut effectuer une rotation à 90° dans le sens horaire ou antihoraire d'une portion du plateau de jeu autour d'un **pivot** sélectionné par ce joueur.

## ✅ Fonctions supplémentaires
Outre les règles classiques d'un puissance X, ce jeu propose d'autres fonctionnalités qui sont les suivantes :

- **Condition de victoire** : au début d'une nouvelle partie, vous pourrez choisir le nombre de **cases à aligner** pour gagner.
- **Pivot** : Après avoir choisi la colonne où il joue, le joueur peut sélectionner la **taille** (3x3 ou 5x5), la **position** du pivot central et le **sens** dans lequel les cases vont tourner (soit à droite, soit à gauche, de 90°). 
    > Pour entrer les bonnes coordonnées de position, c'est simple : on entre d'abord le numéro de ligne souhaité (en comptant à partir de 1) puis le numéro de colonne (qui correspond aux numéros de colonne affichés en bas). 
    Attention : Le carré sélectionné ne peut pas être vide, et ne peut pas dépasser du plateau de jeu.
    Ensuite, on choisit le sens : horaire ou antihoraire. Après cela, la gravité s'applique et c'est au tour du joueur suivant. 

    Cette fonctionnalité peut être désactivée au lancement du jeu.
- **Blocs anti-gravité** : au début d'une nouvelle partie, le joueur peut choisir s'il compte jouer avec ou sans des blocs anti-gravité (**+**). Ces derniers sont des blocs placés dans chaque coin du plateau et qui, comme leur nom l'indique, ne subissent pas de gravité. Cependant, ils peuvent subir l'action des pivots.
- **Sauvegarde** : le jeu dispose d'un système de sauvegarde qui permet d'enrengistrer votre partie la où elle s'est arrêtée. Vous pouvez utiliser le chiffre '**999**' lors du choix de colonne pour sauvegarder le jeu et quitter le programme. Votre partie sela alors sauvegardée et dès que vous relancerez le jeu, vous pourrez restaurer la partie sauvegardée ou en lancer une nouvelle.
    >Il n'est pas possible de sauvegarder le jeu durant le choix des paramètres du pivot, uniquement lors du choix de colonne.

## ✅ Etapes pour compiler et lancer le jeu
- Assurez vous d'avoir `gcc` installé sur votre ordinateur.
- Téléchargez les fichiers source du jeu sur [ce dépot **Github**](https://github.com/Eraguzy/power-5-pivot).
- Ouvrez le terminal et accédez au répertoire contenant les fichiers source.
- Compilez le programme à l'aide de la commande de compilation suivante :
```bibtex
make
```
- Après avoir compilé le programme, toujours dans le bon répertoire, exécutez le programme en entrant la commande suivante :
```bibtex
./cyconnect
```

## ✅ Bugs et limitations du code

- Il n'est pas possible de rejouer au jeu : une fois une partie terminée, il faut relancer le programme avec la commande
```bibtex
./cyconnect
```
- Un seul fichier de sauvegarde `savegame.txt` peut être créé. En crééant une nouvelle sauvegarde, vous écraserez l'ancienne.
- Il n'y a pas d'animation montrant la pièce chuter dans sa colonne : on voit directement à quelle position finale la pièce va se trouver.