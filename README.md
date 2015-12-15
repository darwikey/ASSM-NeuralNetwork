# ASSM-NeuralNetwork

Ce projet utilise un reseau de neurone pour, � partir de deux sons, en synth�tiser un troisi�me.

Le programme prend en entr�e un �chantillon de son et un son � traiter. La sortie r�seau de neurone pilote des g�n�rateurs de sons qui ont tous des fr�quences et des formes d'ondes diff�rentes.
Lors de l'initialisation l'�chantillon permet de calibrer le r�seau de neurone et celui-ci est ainsi entrain� � reproduire le son pass� en entr�e.

Ensuite on applique le deuxi�me son � notre r�seau, un nouveau son va �tre synth�tis� en sortie.


## Compilation
La compilation s'effectue avec cmake, il est recommand� de compiler en release avec cmake -DCMAKE_BUILD_TYPE=Release ...
Des binaire pour linux et windows sont pr�-compil�s.


## Utilisation
usage : ./NeuralNetwork sample_sound.wav sound_to_process.wav [output_sound.wav]

Les configurations du r�seau et de l'algorithme g�n�tique peuvent �tre faites dans le fichier src/stdafx.h


## Impl�mentation
L'apprentissage du r�seau est r�alis� � l'aide d'un algorithme g�n�tique. Au d�part les connexions des neurones ont des poids al�atoires. A chaque g�n�ration les meilleurs r�seaux sont s�l�ctionn�s et un croisement g�n�tique est effectu�.


##Cr�dits
- Maupeu Xavier
- Cabon Yohann

Lecture/�criture fichiers wav : WavUtil(https://github.com/jp-myk/WAVUtil)

Calcul des FFTs : Kiss FFT (http://sourceforge.net/projects/kissfft/)

