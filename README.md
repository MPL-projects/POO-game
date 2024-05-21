# POO Game

## Auteurs du projet
- HAMADY Marie 
- LE LAY Louis
- TEIXEIRA Pierre 

## Bibliothèques et outils externes utilisés
- SDL2
- SDL2_mixer
- SDL2_image
- SDL2_ttf
- nlohmann_json

## Instructions de compilation et d'installation

1. Téléchargez les bibliothèques nécessaires en utilisant les commandes suivantes :
    ```sh
    sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-_image-dev libsdl2-mixer-dev
    sudo apt install nlohmann-json3-dev
    ```

2. Clonez le dépôt Git du jeu :
    ```sh
    git clone <url-du-dépôt>
    ```

3. Accédez au répertoire du projet :
    ```sh
    cd path/to/the/repository
    ```

4. Compilez le jeu en utilisant `make` :
    ```sh
    make
    ```

5. Lancez le jeu :
    ```sh
    ./main
    ```

## Manuel d'utilisation

### But du jeu
Deux joueurs, sur un même pc, se battent sur un jeu type 8 bits. Le but étant que l'un des joueurs perde tous ses points de vie.

### Comment jouer

- **Touches par défaut :**
  - **Joueur 1 :**
    - Déplacement : 
		- Haut : `Z`
		- Bas : `S`
		- Droite : `D`
		- Gauche : `Q`
    - Attaque : `E`
    - Parer : `R`
  - **Joueur 2 :**
    - Déplacement : Flèches directionnelles
    - Attaque : `M`
    - Parer : `Ù`

- **Avec des manettes :**
  - Deux possibilités, soit :
	- Un joueur manette, un joueur clavier.
	- Deux joueurs manettes.

### Règles du jeu
- Chaque joueur commence avec 50 points de vie (PV).
- Chaque attaque inflige 10 PV de dégâts à l'adversaire.
- Les PV de chaque joueur sont affichés par des barres de point de vie.
- Lorsqu'un joueur n'a plus de PV, il meurt et le jeu propose de relancer une partie.

### Options du menu initial
- Changer le skin de chaque joueur.
