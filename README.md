# Labyrinth
A randomly generated labyrinth in C language


# How to Compile and Run
To compile, run the Makefile then run the programm with ./labyrinthe

However, you'll need the MLV library to compile it yourself. It's pretty old but easily downloadable on debian/ubuntu.
http://www-igm.univ-mlv.fr/~boussica/mlv/index.html


# Various Options
You can run the programm with a few options that you can combine
(e.g. ./labyrinthe --acces --taille=10x15 --victor)

+ --mode=texte  to display the labyrinth in the terminal
+ --taille=NxM  to adjust the size of the labyrinth with N and M integers
+ --graine=N    to choose the seed for srand 
+ --attente=N   to choose an interval of time (in ms) between the disappearance of each wall (--attente=0 shows the final state of the labyrinth)
+ --unique      the labyrinth have an only way to resolv it
+ --acces       to have a labyrinth where you can have access to each "tile"
+ --victor      to show the path to "clear" the maze
