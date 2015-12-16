# ASSM-NeuralNetwork

Ce projet utilise un réseau de neurones pour, à partir de deux sons, en synthétiser un troisième.

Le programme prend en entrée un échantillon de son et un son à traiter. La sortie réseau de neurones pilote des générateurs de sons qui ont tous des fréquences et des formes d'ondes différentes.
Lors de l'initialisation l'échantillon sonore permet de calibrer le réseau de neurones et celui-ci est ainsi entrainé à reproduire le son passé en entrée.

Ensuite en appliquant le deuxième son à notre réseau, un nouveau son va être synthétisé et enregistré dans un nouveau fichier.


## Compilation
La compilation s'effectue avec cmake, il est recommandé de compiler en release avec cmake -DCMAKE_BUILD_TYPE=Release ...

Des binaires pour linux et windows sont pré-compilés.


## Utilisation
usage : ./NeuralNetwork sample_sound.wav sound_to_process.wav [output_sound.wav]

Les configurations du réseau et de l'algorithme génétique peuvent être faites dans le fichier src/stdafx.h

Le dossier data contient des échantillons de sons. Des exemples de sons synthétisés sont disponibles dans le dossier results. 


## Implémentation
L'apprentissage du réseau est réalisé à l'aide d'un algorithme génétique. Au départ les neurones ont des coefficients aléatoires. A chaque génération les meilleurs réseaux sont sélectionnés et un croisement génétique est effectué. L'évaluation d'un réseau consiste à comparer la FFT de la sortie des générateurs et la FFT du signal d'entrée.


##Crédits
- Maupeu Xavier
- Cabon Yohann

Lecture/écriture fichiers wav : WavUtil(https://github.com/jp-myk/WAVUtil)

Calcul des FFTs : Kiss FFT (http://sourceforge.net/projects/kissfft/)

