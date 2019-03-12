

//Bibliothèques utilisées
#include <stdio.h>
#include <stdlib.h>
#include "errors.h" //Gestion des erreurs
#include "Header.h" //Fonctions utilisées

//=================
//APPEL DU PROGRAMME
//==================
void main(int argc, char** argv) {
	
	//Variables 'globales' utilisées
	vecteur vector = 0;
	matrice matrix = 0;
	int nbLines = 0;
	int nbCol = 0;
	int size = 0;
	int tailléPlusLoin = 0;
	int alreadySized = 0;

	

	//Pas d'argument : écran d'accueil
	if (argc == 1) { 
		welcome();
		procedureAleaDemo(3,3);
	}

	//Gestion des commandes
	for (int i = 1; i < argc; i++){

		//Taille de la matrice
		if (strcmp(argv[i], "-d") == 0){ 
			if(alreadySized == 0){
				//Déclaration des variables
				nbLines = atoi(argv[i + 1]);
				nbCol = atoi(argv[i + 2]);

				//Vérifie que les variables de tailles sont existantes
				if (nbLines <= 0 || nbCol <= 0) {
					printf("Enter positive values for lines and columns\n");
					setError(INTERROR);
				}
				else {
					size = matrixSize(nbLines, nbCol);
				}

				//Pas d'autres arguments suivant (matrice non définie): on génère une matrice aléatoire qu'on résoud
				if ((argc == (i + 3)) || (argumentCheck(argv, argc, i) == 0) ||(definieMatrice(argv, argc, i) == 0) ){
					printf(" # Random matrix solver # \n");
					procedureAleaDemo(nbCol, nbLines);
				}
			}

		}

		//Entre la matrice avec un 'string'
		if (strcmp(argv[i], "-b") == 0) { 
			char vectorialString[100];
			int gauss = 0;

			int indiceTaille = 0;

			//String missing
			if (argc == (i+1)) { 
				return(setError(MATRIXERROR));
			}

			//Sinon on copie la matrice dans une variable qu'on utilisera
			strcpy(vectorialString, argv[i + 1]);
			//Cherche la présence des paramètres de taille (0 ou 1)
			tailléPlusLoin = sizeCheck(argv, argc);

			if (plainStringErrorChecker(vectorialString)) { return(setError(STRINGERROR)); } //No binary string found
			//TAILLE DE LA MATRICE
			else{ 
				//La taille n'a pas été définie: vecteur (avertissement)
				if (tailléPlusLoin == 0) { 
					nbLines = 1;
					nbCol = strlen(vectorialString);
					size = matrixSize(nbLines, nbCol);
					setWarning(SIZEWARNING);
				}
				//La taille est définie mais plus loin, fait le travail du -d
				//Le alreadySized permet de ne pas réécrire la taille afin d'éviter les erreurs
				else if(alreadySized == 0){ 
					indiceTaille = indiceDeTaille(argv, argc);
					if (indiceTaille != 0) {
						nbLines = atoi(argv[indiceTaille + 1]);
						nbCol = atoi(argv[indiceTaille + 2]);

						//Vérifie que les variables de taille sont existantes
						if (nbLines <= 0 || nbCol <= 0) {
							printf("Enter positive values for lines and columns\n");
							setError(INTERROR);
						}
						else {
							size = matrixSize(nbLines, nbCol);
						}
						alreadySized = 1;
					}
				}
				//Taille définie, on peut créer notre matrice
				if (size != 0) {
					//Création du vecteur et de la matrice
					vector = recuperationVecteurGrilleDepart(size, vectorialString);
					matrix = creationMatrice(nbCol, nbLines);
				}
				else {
					return(setError(SIZEERROR));
				}
			}

			//-V (GAUSS) OU NON
			gauss = gaussCheck(argv, argc);

			//CONCLUSION : MATRICE RESOLUE
			if ((vector != 0) || (matrix != 0)) {
				if (gauss == 1) {
					procedureSpecial(matrix, vector, nbCol, nbLines);
				}
				else {
					procedureClassique(matrix, vector, nbCol, nbLines);
				}
			}
		}

		//Entre la matrice hexa avec un 'string'
		if (strcmp(argv[i], "-x") == 0) { 
			char vectorialString[100];
			int gauss = 0;
			int indiceTaille = 0;

			//String missing
			if (argc == (i + 1)) {
				return(setError(MATRIXERROR));
			}

			//Sinon on copie la matrice dans une variable qu'on utilisera
			strcpy(vectorialString, argv[i + 1]);
			//Cherche la présence des paramètres de taille (0 ou 1)
			tailléPlusLoin = sizeCheck(argv, argc);

			if (hexaStringErrorChecker(vectorialString)) { return(setError(STRINGHEXAERROR)); } //No binary string found
		    //TAILLE DE LA MATRICE
			else {
				//La taille n'a pas été définie: vecteur (avertissement)
				if (tailléPlusLoin == 0) {
					nbLines = 1;
					nbCol = strlen(vectorialString);
					size = matrixSize(nbLines, nbCol);
					setWarning(SIZEWARNING);
				}
				//La taille est définie mais plus loin, fait le travail du -d
				//Le alreadySized permet de ne pas réécrire la taille afin d'éviter les erreurs
				else if (alreadySized == 0) {
					indiceTaille = indiceDeTaille(argv, argc);
					if (indiceTaille != 0) {
						nbLines = atoi(argv[indiceTaille + 1]);
						nbCol = atoi(argv[indiceTaille + 2]);

						//Vérifie que les variables de taille sont existantes
						if (nbLines <= 0 || nbCol <= 0) {
							printf("Enter positive values for lines and columns\n");
							setError(INTERROR);
						}
						else {
							size = matrixSize(nbLines, nbCol);
						}
						alreadySized = 1;
					}
				}
				//Taille définie, on peut créer notre matrice
				if (size != 0) {
					//Création du vecteur et de la matrice
					vector = hexadecimalDetector(size, vectorialString);
					
					matrix = creationMatrice(nbCol, nbLines);
				}
				else {
					return(setError(SIZEERROR));
				}
			}

			//-V (GAUSS) OU NON
			gauss = gaussCheck(argv, argc);

			//CONCLUSION : MATRICE RESOLUE
			if ((vector != 0) || (matrix != 0)) {
				if (gauss == 1) {
					procedureSpecial(matrix, vector, nbCol, nbLines);
				}
				else {
					procedureClassique(matrix, vector, nbCol, nbLines);
				}
			}
		}

	
		
		//Panneau d'aide
		if (strcmp(argv[i], "-h") == 0) { 
			noobHelper();
		}
	}
	
	return;
}
