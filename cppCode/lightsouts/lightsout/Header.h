 #pragma once
//Types utilisés
typedef int** matrice;
typedef int* vecteur;

//Bibliothèques utilisées
#include"math.h"
#include "time.h"


//===================
//FONCTIONS UTILISEES
//===================


//Interface d'aide
int noobHelper() {
	printf("\nLights Out commands :\n");
	printf("\nEach parameter is seperated by a blank.\n");
	printf("\n'-d' 'l' 'c' to define your matrix size. 'l' and 'c' are followed to define the number of lines and the number of columns (integers). \n");
	printf("\n'-b' 's' to set your matrix' content. 's' is the matrix' plain content, line by line (integer), in binary. You must have defined your matrix' size in the other command's parameters. \n");
	printf("\n'-x' 's' to set your matrix' content. 's' is the matrix' hexa code, line by line (hexa-integer). You must have defined your matrix' size in the other command's parameters.\n");
	printf("\n'-v' is used to solve your matrix using Gauss-Jordan elimination. You must have defined your matrix and its size in the other command's parameters.");
	return 1;
}

//Erreurs
int setError(int code) {
	switch (code) {
	case STRINGERROR:
		printf("Wrong or missing string after command (-d / -b ). Please check again.\n");
		break;
	case INTERROR:
		printf("Wrong or missing integers\n");
		break;
	case GAUSSERROR:
		printf("The matrix is either unsolvable or the solver couldn't proceed to its solving.\n");
		break;
	case MATRIXERROR:
		printf("The matrix has not been saved and couldn't been solved.");
		break;

	case STRINGHEXAERROR:
		printf("Wrong or missing string after command (-x). Please check again.\n");
		break;
	}
	return 0;
}

//Avertissements
void setWarning(int code) {
	switch (code) {
	case SIZEWARNING:
		printf("\nWarning : Your matrix is defined as a vector. (No size declared before with -d)\n");
	}
}

//Main screen
int welcome() {
	printf("\n _      _____ _____ _    _ _______ _____    ____  _    _ _______ \n");
	printf("| |    |_   _/ ____| |  | |__   __/ ____|  / __ \\| |  | |__   __|\n");
	printf("| |      | || |  __| |__| |  | | | (___   | |  | | |  | |  | |   \n");
	printf("| |      | || | |_ |  __  |  | |  \\___ \\  | |  | | |  | |  | |   \n");
	printf("| |____ _| || |__| | |  | |  | |  ____) | | |__| | |__| |  | |   \n");
	printf("|______|_____\\_____|_|  |_|  |_| |_____/   \\____/ \\____/   |_|   \n");
	printf("    ____    ___     _       __      __  ______   _____ \n");
	printf("  / ____|  / __ \\  | |      \\ \\    / / |  ____| |  __ \ \n");
	printf(" | (___   | |  | | | |       \\ \\  / /  | |__    | |__) |\n");
	printf("  \\___ \\  | |  | | | |        \\ \\/ /   |  __|   |  _  / \n");
	printf("  ____) | | |__| | | |____     \\  /    | |____  | | \\ \\ \n");
	printf(" |_____/   \\____/  |______|     \\/     |______| |_|  \\_\\ \n");
	printf("\nWelcome to LIGHTS OUT SOLVER \nby Louis Krempp, Geoffroy Latour, and Baptiste Millot. \nPress -h for help.\n\n\n");
	return 1;
}

//Vérifie les matrice entrée (binaires)
int plainStringErrorChecker(char* s) {
	for (int i = 0; i < strlen(s); i++) {
		if ((s[i] != '0') && (s[i] != '1')) return 1;
	}
	return 0;
}

//Vérifie la matrice entrée (hexa)           A FAIRE
int hexaStringErrorChecker(char* s) {
	for (int i = 0; i < strlen(s); i++) {
		if ((s[i] < '0') || ((s[i] > '9') && (s[i] < 'A')) || ((s[i] > 'F') && (s[i] < 'a')) || (s[i] > 'f')) return 1;
	}
	return 0;
}

int pivot(matrice m, vecteur p, int taille) {
	int swapp = 0;
	int pivotValide = -1;
	for (int i = 0; i < taille; i++) { // x et y coordonné du pivot
		if (m[i][i] == 0) {
			swapp = chercherswapp(m, p, i, taille);
			if (swapp == -1) {
				continue;
			}
			else {
				echanger(m, p, swapp, i, taille);
			}
		}
		for (int j = i; j < taille; j++) {  //on suprimer les "1" parasites sur la colonne en dessous de i

			if (m[j][i] == 1) {
				xor (m, p, j, i, taille);

			}
		}
	}
	for (int i = taille - 1; i >= 0; i--) { // x et y coordonné du pivot

		if (m[i][i] == 1) {
			if (pivotValide == -1) {
				pivotValide = i;
			}
			for (int j = i; j >= 0; j--) {  //on suprimer les "1" parasites sur la colonne en dessous de i
				if (m[j][i] == 1) {
					xor (m, p, j, i, taille);
				}
			}
		}
	}
	return solution(m, p, taille, pivotValide); //on retourne la fonction solution}
}


int chercherswapp(matrice m, vecteur p, int pivotY, int taille) {
	int pivotX = pivotY;
	while (m[pivotY][pivotX] != 1 && pivotY < taille) {
		pivotY++;
		if (pivotY == taille) {
			return -1;
		}
	}
	return pivotY;
}

int choisirPivot(matrice m, int taille, int pivotX, int pivotY) {

	while (m[pivotY][pivotX] != 1 && pivotY < taille) {  //on choisi le pivot selon la formule
		pivotY++;
		if (pivotY == taille) {
			return -1;
		}
	}
	return pivotY;
}

int xor(matrice m, vecteur p, int ligneY, int lignePivot, int taille) {


	if (ligneY == lignePivot)return;
	p[ligneY] = p[ligneY] ^ p[lignePivot];
	for (int i = 0; i < taille; i++) {
		m[ligneY][i] = m[lignePivot][i] ^ m[ligneY][i];
	}
}

int echanger(matrice m, vecteur p, int Y1, int Y2, int taille) {

	if (Y1 == Y2) {
		return;
	}
	vecteur tempoM = malloc(taille * sizeof(int));
	int tempoP;

	tempoP = p[Y1];
	p[Y1] = p[Y2];
	p[Y2] = tempoP;

	for (int i = 0; i < taille; i++) {
		tempoM[i] = m[Y1][i];
		m[Y1][i] = m[Y2][i];
		m[Y2][i] = tempoM[i];
	}

}

int solution(matrice m, vecteur p, int taille, int posPivot) {

	int compteur1 = 0;
	int compteur2 = 0;
	for (int i = 0; i <taille; i++) {  //on compte le nombre de "1" 
		for (int j = 0; j < taille; j++) {
			if (m[i][j] == 1 && i <= posPivot)compteur1++;  //compteur 1 est le nombre de "1" au dessous du pivot
			if (m[i][j] == 1 && posPivot<i)compteur2++;  //compteur 2 est le nombre de "1" au dessus du pivot
		}
		if (compteur1 == 0 && compteur2 == 0 && p[i] == 1) {
			sol(0); //pas solution
			return;
		}
		if (compteur2 > 0) {
			sol(2); // infinité
			return;
		}
		compteur1 = 0;
		compteur2 = 0;
	}
	sol(1);  //solution
	return;
}

int sol(int a)
{
	switch (a)
	{
	case 1:
		printf_s("\nthere is only one solution\n");
		return 1;
		break;
	case 0:
		printf_s("\nthere is no solution ...\n");
		return -1;
		break;
	case 2:
		printf_s("\nthere is a lot of solution !  \n");
		break;
	default:
		printf_s("\nthere is a problem please, try again \n");
		break;
	}
}

matrice creationMatrice(int colonne, int ligne)
{
	int tailleVecteur = colonne*ligne;
	int** mat = malloc(tailleVecteur*sizeof(int*));   // creation de la matrice et mise a 0 de toutes les cases.
	for (int i = 0; i < tailleVecteur; i++) {
		mat[i] = malloc(tailleVecteur*sizeof(int));
		for (int j = 0; j < tailleVecteur; j++) {
			mat[i][j] = 0;
		}
	}


	for (int i = 0; i < tailleVecteur; i++) {

		if (i - colonne >= 0) {  //pour savoir si on peut mettre un "1" au dessus de la case coché
			mat[i - colonne][i] = 1;
		}
		if (i%colonne != 0)	mat[i - 1][i] = 1; //procedure pour les "1" de droite de millieu et de droite
		mat[i][i] = 1;
		if (i%colonne != colonne - 1)	mat[i + 1][i] = 1;

		if (i + colonne < tailleVecteur) { //pour savoir si on peut mettre un "1" au dessous de la case coché
			mat[i + colonne][i] = 1;
		}



	}
	return mat;
}

vecteur creationvecteurAlea(int colonne, int ligne)
{
	srand(time(NULL));
	int tailleVecteur = colonne*ligne;
	int *vec = malloc(tailleVecteur * sizeof(int*));
	for (int i = 0; i < tailleVecteur; i++) {
		vec[i] = rand() % 2;
	}



	return vec;
}

void chartoint(char* str)  // fonction de goeffroy
{

	int tmp = atoi(str);
	int * tmps = malloc(strlen(str)*sizeof(char));

	printf_s("%d\n", tmp);

}

int affichageOnlyVec(vecteur v, int nbcolonne, int nbligne)
{
	for (int i = 0; i < nbligne*nbcolonne; i++) {

		printf_s("|");
		printf_s("%d", v[i]);
		printf_s("|");
		if (((i + 1) % nbcolonne) == 0)printf("\n");

	}

}

int affichageTout(matrice tab, vecteur v, int nbligne, int nbcol)
{
	int taille = nbligne*nbcol;
	for (int i = 0; i < taille; i++) {
		for (int j = 0; j < taille; j++) {
			printf_s("|");
			printf_s("%d", tab[i][j]);
			printf_s("|");
		}
		printf_s("=|");
		printf_s("%d", v[i]);
		printf_s("|");
		printf_s("\n");
	}

}

void afflightout()
{
	printf_s("=============== \n");
	printf_s(" LIGHT OUT SOLVER  \n");
	printf_s("=============== \n");
}

int procedureClassique(matrice m, vecteur p, int colonne, int ligne) {
	//colonne, ligne
	afflightout();
	printf("\Your %d x %d gameboard :\n", colonne, ligne);
	affichageOnlyVec(p, colonne, ligne); //affiche la grille
	if (pivot(m, p, colonne*ligne) != -1) { //trouve les solutions...
		printf("\nA possible solution:\n");
		affichageOnlyVec(p, colonne, ligne); //on affich les solutions..
	}

}

int procedureSpecial(matrice m, vecteur p, int colonne, int ligne) {
	//colonne, ligne
	afflightout();
	printf("\Your %d x %d gameboard :\n", colonne, ligne);
	affichageOnlyVec(p, colonne, ligne); //affiche la grille
	printf("\n=== ANALYSIS ===\n\nSwitch matrix (von Neumann neighborhood):  \n\n");
	affichageTout(m, p, colonne, ligne); //on affich les solutions..

	printf("\nPost elimination: \n");
	if (pivot(m, p, colonne*ligne) != -1) { //trouve les solutions...
		affichageTout(m, p, colonne, ligne); //on affich les solutions..

		printf("\n\nA possible solution:\n");
		affichageOnlyVec(p, colonne, ligne); //on affich les solutions..
	}
}

//Matrice aléatoire de l'écran de bienvenue.
int procedureAleaDemo(int col, int lin) {



	vecteur p = creationvecteurAlea(col, lin);
	// nombre de colonne/ nombres de lignes.
	matrice m = creationMatrice(col, lin);  //créé la matrice
											//la taille de cette matrice sera de 5*2 = 10.
	procedureClassique(m, p, col, lin);
}

vecteur recuperationVecteurGrilleDepart(int taille, char* s) {
	vecteur vec = malloc(sizeof(vecteur)*taille);
	int z = 0;

	for (int x = 0; x < taille; x++) {
		vec[x] = 0;
	}
	for (int x = 0; (x < taille) && (x<strlen(s)); x++) {
		vec[x] = (s[z] - '0') % 2;
		z++;
	}
	return vec;
}

//Définie la taille
int matrixSize(int Col, int Lin) {
	return Col*Lin;
}

int gaussCheck(char** argv, int argc) {
	int gauss = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0) gauss = 1;

	}
	return gauss;
}


//Cherche la taille de la matrice (-d)
int sizeCheck(char** argv, int argc) {
	int sized = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) sized = 1;

	}
	return sized;
}

//Cherche l'indice de -d
int indiceDeTaille(char** argv, int argc) {
	int indice = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) indice = i;

	}
	return indice;
}

//Vérifie que le prochain argument n'est pas une commande
int argumentCheck(char** argv, int argc, int indice) {
	int check = 0;
	for (int i = indice; i <= indice + 1; i++) {
		if ((strcmp(argv[i], "-d") == 0) || (strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "-x") == 0) || (strcmp(argv[i], "-b") == 0)) check = 1;

	}
	return check;
}

//Cherche l'indice de -b ou de -x
int definieMatrice(char** argv, int argc) {
	int defined = 0;
	for (int i = 0; i < argc; i++) {
		if ((strcmp(argv[i], "-b") == 0) || (strcmp(argv[i], "-x") == 0)) defined = 1;

	}
	return defined;
}

vecteur hexadecimalDetector(int taille, char* s) {
	vecteur vec = malloc(100* sizeof(vecteur));
	int j = 0;
	for (int i = 0; i < strlen(s); i++) { //parcours de la chaine de l'hexa
		switch (s[i]) {   //selon le caractère
		case '0':
			vec[j] = 0;
			vec[j + 1] = 0;
			vec[j + 2] = 0;
			vec[j + 3] = 0;
			break;
		case '1':
			vec[j] = 0;
			vec[j + 1] = 0;
			vec[j + 2] = 0;
			vec[j + 3] = 1;

			break;
		case '2':
			vec[j] = 0;
			vec[j + 1] = 0;
			vec[j + 2] = 1;
			vec[j + 3] = 0;

			break;
		case '3':
			vec[j] = 0;
			vec[j + 1] = 0;
			vec[j + 2] = 1;
			vec[j + 3] = 1;
			break;
		case '4':
			vec[j] = 0;
			vec[j + 1] = 1;
			vec[j + 2] = 0;
			vec[j + 3] = 0;
			break;
		case '5':
			vec[j] = 0;
			vec[j + 1] = 1;
			vec[j + 2] = 0;
			vec[j + 3] = 1;
			break;
		case '6':
			vec[j] = 0;
			vec[j + 1] = 1;
			vec[j + 2] = 1;
			vec[j + 3] = 0;
			break;
		case '7':
			vec[j] = 0;
			vec[j + 1] = 1;
			vec[j + 2] = 1;
			vec[j + 3] = 1;
			break;
		case '8':
			vec[j] = 1;
			vec[j + 1] = 0;
			vec[j + 2] = 0;
			vec[j + 3] = 0;
			break;
		case '9':
			vec[j] = 1;
			vec[j + 1] = 0;
			vec[j + 2] = 0;
			vec[j + 3] = 1;
			break;
		case 'A':
			vec[j] = 1;
			vec[j + 1] = 0;
			vec[j + 2] = 1;
			vec[j + 3] = 0;
			break;
		case 'B':
			vec[j] = 1;
			vec[j + 1] = 0;
			vec[j + 2] = 1;
			vec[j + 3] = 1;
			break;
		case 'C':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 0;
			vec[j + 3] = 0;
			break;
		case 'D':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 0;
			vec[j + 3] = 1;
			break;
		case 'E':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 1;
			vec[j + 3] = 0;
			break;
		case 'F':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 1;
			vec[j + 3] = 1;
			break;
		case 'a':
			vec[j] = 1;
			vec[j + 1] = 0;
			vec[j + 2] = 1;
			vec[j + 3] = 0;
			break;
		case 'b':
			vec[j] = 1;
			vec[j + 1] = 0;
			vec[j + 2] = 1;
			vec[j + 3] = 1;
			break;
		case 'c':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 0;
			vec[j + 3] = 0;
			break;
		case 'd':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 0;
			vec[j + 3] = 1;
			break;
		case 'e':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 1;
			vec[j + 3] = 0;
			break;
		case 'f':
			vec[j] = 1;
			vec[j + 1] = 1;
			vec[j + 2] = 1;
			vec[j + 3] = 1;
			break;
		default:  printf("\nInvalid hexadecimal digit at %dth character\n ", i); return 0;
		}
		j = j + 4;


	}
	printf("\n");
	return vec;

}