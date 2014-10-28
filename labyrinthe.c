#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"


unsigned short** initTab2DFixed(){
	int i = 0, j = 0;
	unsigned short tab2Dfixe[LAB_C_FIX][LAB_L_FIX] = { { 11, 12, 11, 12 }, { 9, 6, 9, 6 }, { 3, 10, 0, 14 }, { 11, 10, 2, 14 } };
	unsigned short **pLAB;

	pLAB = malloc(LAB_L_FIX*sizeof(unsigned short));
	if (pLAB == NULL)
	{
		fprintf(stderr, "Allocation impossible \n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i<sizeof(pLAB); i++){
		*(pLAB + i) = malloc(LAB_C_FIX*sizeof(unsigned short));
		if (*(pLAB + i) == NULL)
		{
			fprintf(stderr, "Allocation impossible \n");
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i<sizeof(pLAB); i++){
		for (j = 0; j < sizeof(*(pLAB + i)); j++){
			pLAB[i][j] = tab2Dfixe[i][j];
		}
	}

	return pLAB;
}


struct Labyrinthe createFixedLab(struct Labyrinthe lab, int i, int column){
	lab.l = i;
	lab.c = column;
	lab.tab2D = initTab2DFixed();
	return lab;
}

void affMurH(){
	
	printf("---");

}

void affMurB(){
	printf("---");
}

void affMurG(){
	printf("|");
}

void affMurD(){
	printf("|");
}



void afficherLab(struct Labyrinthe lab){
	int i=0, j=0;
	for(i=0;i<sizeof(lab.tab2D);i++){
		for(j=0;j<sizeof(*lab.tab2D);j++){
			printf("%d\t",lab.tab2D[i][j]);
			if(j==sizeof(*lab.tab2D)-1){
				printf("\n");
			}
		}
	}
	if (sizeof(lab.tab2D)>1&&sizeof(*lab.tab2D)>1){
		for(i=0;i<sizeof(lab.tab2D);i++){
			for(j=0;j<sizeof(*lab.tab2D);j++){
				printf("+");
				if(lab.tab2D[i][j]>>3&1){
					affMurH();
					if(j==sizeof(*lab.tab2D)-1){
						printf("+");
					}
				}else {
					printf("   ");
					if(j==sizeof(*lab.tab2D)-1){
						printf("+");
					}
				}
				if(j==sizeof(*lab.tab2D)-1){
					printf("\n");

				}
			}
			for(j=0;j<sizeof(*lab.tab2D);j++){
				if(lab.tab2D[i][j]&1){
					affMurG();
					printf("   ");
				} else {
					printf(" ");
					printf("   ");
				}
				if(j==sizeof(*lab.tab2D)-1){
					affMurD();
					printf("\n");
				}
			}
			if(i==sizeof(lab.tab2D)-1){
				for(j=0;j<sizeof(*lab.tab2D);j++){
					printf("+");
					affMurB();
					if(j==sizeof(*lab.tab2D)-1){
						printf("+");
					}
				}
			}
		}
	}
}

unsigned short ** initTab2DRandom(int l, int c){
	int i =0,j = 0;
	unsigned short ** pTab2D;
	pTab2D = malloc(l*sizeof(unsigned short));
	if (pTab2D == NULL)
	{
		fprintf(stderr, "Allocation impossible \n");
		exit(EXIT_FAILURE);
	}
	pTab2D = malloc(c*sizeof(unsigned short));
	if (pTab2D == NULL)
	{
		fprintf(stderr, "Allocation impossible \n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<sizeof(pTab2D);i++){

	}
}

struct Labyrinthe createRandomLab(struct Labyrinthe lab){
	lab.c=4;
	lab.l=4;
	if(lab.c>1&&lab.l>1){
		lab.tab2D = initTab2DRandom(lab.l,lab.c);
	}
}

struct Labyrinthe createLabFromFile(struct Labyrinthe lab/*, char * nomfichier*/){
	int **tab; // pointeur
	int hauteur; // hauteur de la matrice
	int i=0;
	int largeur; // largeur de la matrice
	int j=0; 
	int xentrer, yentrer, xsortie, ysortie;
	int c;
	FILE *fichier;

	// ouverture du ficher texte
	fichier = fopen("U:\\GitProjectC\\matrice.txt", "r");
	if(fichier == NULL)	//test d'ouverture du fichier
		printf("erreur de fichier\n");

	// recuperation taille et position entrer & sortie
	fscanf(fichier, "%d %d %d %d %d %d", &largeur, &hauteur, &xentrer, &yentrer, &xsortie, &ysortie);

	lab.xentrer = xentrer;
	lab.yentrer = yentrer;
	lab.xsortie = xsortie;
	lab.ysortie = ysortie;
	lab.l = hauteur;
	lab.c = largeur;

	// declaration du tableau 2D
	
	tab = malloc(hauteur*sizeof(int*));
	if (tab == NULL)
		printf("erreur de tableau1\n");
	for(i=0;i<lab.l;i++) {
		tab[i] = malloc(lab.c*sizeof(int));
		if (tab[i] == NULL)
			printf("erreur de tableau2\n");
		}

	// lecture
	for(i=0; i < lab.l; i++) {
		for(j=0; j < lab.c; j++) {
			fscanf(fichier, "%d", &tab[i][j]);
		}
	}

	lab.tab2D = tab;

	//affichage
/*	printf("labyrinthe de dimension %d X %d\n", largeur, hauteur);
	printf("donnees dans le fichier .txt :\n");
	for (i = 0; i<hauteur; i++) {
		for (j = 0; j < largeur; j++) {
		printf("%d ", tab[i][j]);
		}
	printf("\n");
	}
	printf("position entrer (%d;%d)\n", xentrer, yentrer);
	printf("position sortie (%d;%d)\n", xsortie, ysortie);*/

	// fermeture
	/*fclose(fichier);
	for(i=0;i<hauteur;i++) {
		free(tab[i]);
		}
	free(tab);*/

	return lab;
}