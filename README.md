# ASSM-NeuralNetwork

Ce projet utilise un reseau de neurone pour à partir de deux sons, en synthétiser un troisième.

Le programme prend en entrée un échantillon de son et un son à traiter. La sortie réseau de neurone pilote des générateurs de sons qui ont tous des fréquences et des formes d'ondes différentes.
Lors de l'initialisation l'échantillon permet de calibrer le réseau de neurone et celui-ci est ainsi entrainé à reproduire le son passé en entrée.

Ensuite on applique le deuxième son à notre réseau, en sortie on va obtenir un nouveau son.

## Utilisation
usage : ./NeuralNetwork sample_sound.wav sound_to_process.wav [output_sound.wav]

Les configurations du réseau et de l'algorithme génétique peuvent être faites dans le fichier src/stdafx.h


## Implémentation
L'apprentissage du réseau est réalisé à l'aide d'un algorithme génétique.


##Credits
- Maupeu Xavier
- Cabon Yohann

lecture/écriture fichier wav : 