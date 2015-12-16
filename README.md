# ASSM-NeuralNetwork

Ce projet utilise un r�seau de neurones pour, � partir de deux sons, en synth�tiser un troisi�me.

Le programme prend en entr�e un �chantillon de son et un son � traiter. La sortie r�seau de neurones pilote des g�n�rateurs de sons qui ont tous des fr�quences et des formes d'ondes diff�rentes.
Lors de l'initialisation l'�chantillon sonore permet de calibrer le r�seau de neurones et celui-ci est ainsi entrain� � reproduire le son pass� en entr�e.

Ensuite en appliquant le deuxi�me son � notre r�seau, un nouveau son va �tre synth�tis� et enregistr� dans un nouveau fichier.


## Compilation
La compilation s'effectue avec cmake, il est recommand� de compiler en release avec cmake -DCMAKE_BUILD_TYPE=Release ...

Des binaires pour linux et windows sont pr�-compil�s.


## Utilisation
usage : ./NeuralNetwork sample_sound.wav sound_to_process.wav [output_sound.wav]

Les configurations du r�seau et de l'algorithme g�n�tique peuvent �tre faites dans le fichier src/stdafx.h

Le dossier data contient des �chantillons de sons. Des exemples de sons synth�tis�s sont disponibles dans le dossier results. 


## Impl�mentation
L'apprentissage du r�seau est r�alis� � l'aide d'un algorithme g�n�tique. Au d�part les neurones ont des coefficients al�atoires. A chaque g�n�ration les meilleurs r�seaux sont s�lectionn�s et un croisement g�n�tique est effectu�. L'�valuation d'un r�seau consiste � comparer la FFT de la sortie des g�n�rateurs et la FFT du signal d'entr�e.


##Cr�dits
- Maupeu Xavier
- Cabon Yohann

Lecture/�criture fichiers wav : WavUtil(https://github.com/jp-myk/WAVUtil)

Calcul des FFTs : Kiss FFT (http://sourceforge.net/projects/kissfft/)

