# CY-Connect
Jeu créé par **Atahan**, **Elias** et **Maxime** pour **CY Tech**.

CY-Connect un est jeu basé sur les règles classiques d'un puissance X, à l'exception que le jeu possède certaines fonctionnalités qui rendent le jeu plus dynamique.

## ✅ Règles du jeu
CY-Connect se joue à deux. Les joueurs s'affrontent en utilisant chacun une pièce différente qui les distingue (soit le **X**, soit le **O**). 
Les joueurs jouent chacun leur tour en choisissant une colonne du tableau où mettre leur pièce. Une fois la colonne choisie, la pièce tombe jusqu'à atteindre la position la plus basse disponible dans celle-ci. 
Après chaque lancement d'une pièce, le joueur peut effectuer un pivot de 90° à gauche ou à droite qui fera tourner les pièces autour d'un pivot.

## ✅ Fonctions supplémentaires
Outre les règles classiques d'un puissance X, ce jeu propose d'autres fonctionnalités qui sont les suivantes :

- Pivot : Après avoir lancer sa pièce sur le plateau. Le joueur peut sélectionner la direction dans laquelle le pivot va tourner (soit à droite, soit à gauche). Le pivot choisi aléatoirement une valeur de 3 ou de 5, qui est la taille du pivot. Par la suite, les pièces à l'intérieur de la zone du pivot reste inchangées, tandis que celles à l'extérieur tournent à 90° vers la direction que le joueur a précisé avant (droite ou gauche). Le plateau se voit donc modifiés et les pièces tombe jusqu'à atteindre la position la plus basse diponible dans les colonnes.
- Blocs anti-gravité : au début du programme le joueur peux choisir s'il compte jouer avec des blocs anti-gravité ou non. Ces derniers sont des blocs placés dans chaque coin du plateau qui comme leur noms indiquent, ne subissent pas de gravité. Mais attention ils peuvent être pivoter.
- Sauvegarde : le jeu dispose d'un système de sauvegarde qui permet d'enrengistrer votre partie la où elle s'est arrêté. Vous pouvez utiliser le chiffre '**999**' comme colonne pour sauvegarder le jeu et quitter le programme à tout moment. Votre partie sela alors sauvegardé et dès que vous lancerez le jeu, vous devez répondre oui à la question de si vous voulez contniuer votre partie.

## ✅ Etapes pour compiler et lancer
- Assurer vous d'avoir un compilateur C installé sur votre machine.
- Téléchargez les fichiers sources du jeu.
- Ouvrez une fenêtre de terminal et accédez au répertoire contenant les fichiers source.
- Compilez le programme à l'aide de la commande de compilation suivante :
```bibtex
make
```
- Après avoir compilé le programme, éxécutez le programme en tapant la commande suivante :
```bibtex
./cyconnect
```

## ✅ Commande pour jouer
Au démarrage du jeu, la grille  de jeu est affiché à l'écran. Les joueurs alternent leur tour pour choisir la colonne dans laquelle ils souhaitent placer leur jeton. 

Comment jouer ?
- Le joueur 1 est représenté par les jetons '**X**' de couleur rouge.
- Le joueur 2 est représenté par les jetons '**O**' de couleur bleu.
- Entrez le numéro de colonne dans lequel vous souhaitez placer votre jeton lorsque c'est votre tour.
  
Les joueurs continuent à jouer jusqu'à ce qu'il y ait un gagnant ou que la grille soit pleine. Le jeu affiche le gagnant ou un match nul à la fin de la partie.

Comment sauvegarder sa partie en cours ?

- En tapant la chiffre '**999**' comme colonne, vous pouvez sauvegarder votre partie et le jeu se fermera.

## ✅ Bug et limitation du code
Voici quelques bugs connus et limitations de ce programme :

- Le programme ne gère pas les entrées incorrectes des joueurs lorsqu'ils choisissent une colonne. C'est à dire tout les caractères qui ne sont pas des chiffres.
- Il n'y a pas de fonctionnalité de rejouer automatiquement une partie après la fin d'une partie. Ce cas s'applique si la sauvagarde n'a pas été effectué.
- La rotation du plateau de jeu autour d'un pivot n'est pas implémentée pour toutes les tailles de pivot.
