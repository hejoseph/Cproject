#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"

//Initialisation d'un tableau 2 dimension à valeur fixe
unsigned short** initTab2DFixed(){
	int i = 0, j = 0;
	//Valeur fixé
	unsigned short tab2Dfixe[LAB_C_FIX][LAB_L_FIX] = { { 11, 12, 11, 12 }, { 9, 6, 9, 6 }, { 3, 10, 0, 14 }, { 11, 10, 2, 14 } };
	int 
	unsigned short **pLAB;

	//Tableau alloué pour la "premire dimension" qui correspond à la ligne. Ex : première case du tableau correspond première ligne du labyrinthe
	pLAB = malloc(LAB_L_FIX*sizeof(unsigned short));
	if (pLAB == NULL)
	{
		fprintf(stderr, "Allocation impossible \n");
		exit(EXIT_FAILURE);
	}

	//Un tableau est alloué pour chaque ligne, ce qui forme le tableau bidimensionnel
	for (i = 0; i<sizeof(pLAB); i++){
		*(pLAB + i) = malloc(LAB_C_FIX*sizeof(unsigned short));
		if (*(pLAB + i) == NULL)
		{
			fprintf(stderr, "Allocation impossible \n");
			exit(EXIT_FAILURE);
		}
	}

	//Remplissage du tableau bidimensionnel avec les valeurs fixées au départ.
	for (i = 0; i<sizeof(pLAB); i++){
		for (j = 0; j < sizeof(*(pLAB + i)); j++){
			pLAB[i][j] = tab2Dfixe[i][j];
		}
	}

	return pLAB;
}


struct Labyrinthe createFixedLab(struct Labyrinthe lab, int i, int column,int xe,int ye, int xs,int ys){
	lab.l = i;
	lab.c = column;
	lab.tab2D = initTab2DFixed();
	lab.xentrer = xe;
	lab.yentrer = ye;
	lab.xsortie = xs;
	lab.ysortie = ys;
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


//Affichage du Labyrinthe
void afficherLab(struct Labyrinthe lab){
	int i=0, j=0;
	//test
	for(i=0;i<sizeof(lab.tab2D);i++){
		for(j=0;j<sizeof(*lab.tab2D);j++){
			printf("%d\t",lab.tab2D[i][j]);
			if(j==sizeof(*lab.tab2D)-1){
				printf("\n");
			}
		}
	}
	
	if (sizeof(lab.tab2D)>1&&sizeof(lab.tab2D[0])>1){
		for(i=0;i<sizeof(lab.tab2D);i++){
			for(j=0;j<sizeof(lab.tab2D[i]);j++){
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
			for(j=0;j<sizeof(lab.tab2D[i]);j++){
				if(lab.tab2D[i][j]&1){
					affMurG();
				} else {
					printf(" ");
				}
				if (i == lab.xentrer && j == lab.yentrer){
					printf(" E ");
				} else if (i == lab.xsortie && j == lab.ysortie){
					printf(" S ");
				}else {
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
	unsigned short **tab; // pointeur
	int l; // nombre de ligne de la matrice
	int i=0;
	int c; // nombre de colonne de la matrice
	int j=0; 
	int xentrer, yentrer, xsortie, ysortie;
	
	FILE *fichier;

	// ouverture du ficher texte
	fichier = fopen("matrice.txt", "r");
	if(fichier == NULL)	//test d'ouverture du fichier
		printf("erreur de fichier\n");

	// recuperation taille et position entrer & sortie
	fscanf(fichier, "%d %d %d %d %d %d", &c, &l, &xentrer, &yentrer, &xsortie, &ysortie);

	lab.xentrer = xentrer;
	lab.yentrer = yentrer;
	lab.xsortie = xsortie;
	lab.ysortie = ysortie;
	lab.l = l;
	lab.c = c;

	// declaration du tableau 2D
	
	tab = (unsigned short**)malloc(l*sizeof(unsigned short*));
	if (tab == NULL)
		printf("erreur de tableau1\n");
	for(i=0;i<lab.l;i++) {
		tab[i] = (unsigned short *)malloc(lab.c*sizeof(unsigned short));
		if (tab[i] == NULL)
			printf("erreur de tableau2\n");
		}

	// Remplissage du tableau bidimensionnel à partir du fichier (lecture)
	for(i=0; i < lab.l; i++) {
		for(j=0; j < lab.c; j++) {
			fscanf(fichier, "%d", &tab[i][j]);
		}
	}

	lab.tab2D = tab;
	return lab;
}