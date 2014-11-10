#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"


void allocationL(unsigned short ***p, int size){
	*p = malloc(size*sizeof(unsigned short));
	if (*p == NULL)
	{
		fprintf(stderr, "\n\n !!!!!!!!!  Allocation impossible !!!!!!!!!!!! \n\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void allocationC(unsigned short **p, int size){
	int i = 0;
	for (i = 0; i < size; i++){
		p[i] = malloc(size*sizeof(unsigned short));
		if (p[i] == NULL)
		{
			fprintf(stderr, "\n\n !!!!!!!!!  Allocation impossible !!!!!!!!!!!! \n\n");
			system("pause");
			exit(EXIT_FAILURE);
		}
	}
}

//Allocation du tableau 2 dimension, avec en paramètre le nombre de ligne et de colonne.
void tabAlloc(unsigned short ***p, int ligne, int colonne){
	allocationL(p, ligne);
	allocationC(*p, colonne);
}

//Initialisation d'un tableau 2 dimension à valeur fixe
unsigned short** initTab2DFixed(){
	int i = 0, j = 0;
	int l = LAB_L_FIX;
	int c = LAB_C_FIX;
	//Valeur fixé
	unsigned short tab2Dfixe[LAB_L_FIX][LAB_C_FIX] = { { 11, 12, 11, 12 }, { 9, 6, 9, 6 }, { 3, 10, 0, 14 }, { 11, 10, 2, 14 } };
	unsigned short **pTab = NULL;

	tabAlloc(&pTab, LAB_L_FIX, LAB_C_FIX);

	//Remplissage du tableau bidimensionnel avec les valeurs fixées au départ.
	for (i = 0; i<l ; i++){
		for (j = 0; j < c; j++){
			pTab[i][j] = tab2Dfixe[i][j];
		}
	}
	return pTab;
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
void affSommet(){
	printf("+");
}

//Affichage du Labyrinthe
void afficherLab(struct Labyrinthe lab, int menu){
	int i=0, j=0;
	//test
	printf("\n\n");
	for(i=0;i<lab.l;i++){
		for(j=0;j<lab.c;j++){
			printf("%d\t",lab.tab2D[i][j]);
			if(j==lab.c-1){
				printf("\n");
			}
		}
	}
	
	if (lab.l>1&&lab.c>1){
		for(i=0;i<lab.l;i++){
			for(j=0;j<lab.c;j++){
				affSommet();
				if(lab.tab2D[i][j]>>3&1){
					affMurH();
					if(j==lab.c-1){
						affSommet();
					}
				}else {
					printf("   ");
					if(j==lab.c-1){
						affSommet();
					}
				}
				if(j==lab.c-1){
					printf("\n");

				}
			}
			for(j=0;j<lab.c;j++){
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
					if (menu == 0){
						printf("   ");
					} else if (menu == 1){
						if (lab.tab2D[i][j] >> 8 & 1){
							printf(" X ");
						} else {
							printf("   ");
						}
					} else {
						if (lab.tab2D[i][j] >> 9 & 1){
							printf(" O ");
						} else {
							printf("   ");
						}
					}
					
				}
				if(j==lab.c-1){
					affMurD();
					printf("  %d",i);
					printf("\n");
				}
			}
			if(i==lab.l-1){
				for(j=0;j<lab.c;j++){
					affSommet();
					affMurB();
					if(j==lab.c-1){
						affSommet();
					}
				}
			}
		}
	}
	printf("\n");
	for (i = 0; i < lab.c; i++){
		printf("  %d ",i);
	}
	printf("\n ligne = %d\n colonne = %d\n",lab.xsearcher,lab.ysearcher);
	printf("\n\n");
	for (i = 0; i<lab.l; i++){
		for (j = 0; j<lab.c; j++){
			printf("%d\t", lab.tab2D[i][j] >> 10);
			if (j == lab.c - 1){
				printf("\n");
			}
		}
	}
}


//Génère un nombre entre a et b
unsigned short genNbBetween(int a, int b){
	int r;
	b = b + 1;
	r = (rand() % b);
	while (r<a){
		r = (rand() % b);
	}
	return r;
}

//Génère un nombre aléatoire.
unsigned short genRandNb(int i, int j, unsigned short ** pTab, int ligne, int colonne){

	int r = 0;
	if (i==0){
		if (j == 0){
			while (!(r&1 && r>>3&1)){
				r = genNbBetween(9, 13);
			}
		} else if (j == colonne - 1){
			if (pTab[i][j-1]>>2 & 1){
				r = 13;
			}
			while (!(r>>2 & 1 && r >> 3 & 1)){
				r = genNbBetween(12, 14);
				r = r & 14;
			}
		} else {
			if (pTab[i][j - 1] >> 2 & 1){
				while (!(r & 1 && r >> 3 & 1)){
					r = genNbBetween(9, 13);
				}
			}
			while (!(r >>3 & 1)){
				r = genNbBetween(8, 14);
				r = r & 14;
			}
		}
	} else if (i == ligne - 1) {
		if (j == 0){
			if (pTab[i - 1][j] >> 1 & 1){
				r = 11;
			}
			while (!(r & 1 && r >> 1 & 1)){
				r = genNbBetween(3, 7);
				r = r & 7;
			}
		} else if (j == colonne - 1){
			if (pTab[i - 1][j] >> 1 & 1 && pTab[i][j-1] >> 2 & 1){
				r = 15;
			} else if (pTab[i - 1][j] >> 1 & 1 ){
				r = 14;
			} else if (pTab[i][j - 1] >> 2 & 1){
				r = 7;
			} else {
				r = 6;
			}
		} else {
			if (pTab[i - 1][j] >> 1 & 1 && pTab[i][j - 1] >> 2 & 1){
				r = 11;
			} else if (pTab[i - 1][j] >> 1 & 1){
				while (!(r>>3 & 1 && r>>1&1)){
					r = genNbBetween(10, 14);
					r = r & 14;
				}
			} else if (pTab[i][j - 1] >> 2 & 1){
				while (!(r & 1 && r >> 1 & 1)){
					r = genNbBetween(3, 7);
					r = r & 7;
				}
			} else {
				while (!(r >> 1 & 1)){
					r = genNbBetween(2, 6);
					r = r & 6;
				}
			}
		}
	} else {
		if (j == 0){
			if (pTab[i - 1][j] >> 1 & 1){
				while (!(r & 1 && r >> 3 & 1)){
					r = genNbBetween(9, 13);
				}
			} else {
				while (!(r & 1)){
					r = genNbBetween(1, 7);
					r = r & 7;
				}
			}
			
		} else if (j == colonne - 1){
			if (pTab[i - 1][j] >> 1 & 1 && pTab[i][j - 1] >> 2 & 1){
				r = 13;
			} else if (pTab[i - 1][j] >> 1 & 1){
				while (!(r>>2 & 1 && r >> 3 & 1)){
					r = genNbBetween(12, 14);
					r = r & 14;
				}
			} else if (pTab[i][j - 1] >> 2 & 1){
				while (!(r & 1 && r >> 2 & 1)){
					r = genNbBetween(5, 7);
					r = r & 7;
				}
			} else {
				while (!( r >> 2 & 1)){
					r = genNbBetween(4, 6);
					r = r & 6;
				}
			}
		} else {
			if (pTab[i - 1][j] >> 1 & 1 && pTab[i][j - 1] >> 2 & 1){
				while (!(r >> 3 & 1 && r & 1)){
					r = genNbBetween(9, 13);
				}
			} else if (pTab[i - 1][j] >> 1 & 1){
				while (!(r >> 3 & 1 )){
					r = genNbBetween(8, 14);
					r = r & 14;
				}
			} else if (pTab[i][j - 1] >> 2 & 1){
				while (!(r & 1 )){
					r = genNbBetween(1, 7);
					r = r & 7;
				}
			} else {
			//	while (!(r & 0 && r>>3 & 0)){
					r = genNbBetween(0, 6);
					r = r & 6;
		//		}
			}
		}
	}

	return r;
}

unsigned short ** initTab2DRandom(int l, int c){
	int i =0,j = 0;
	unsigned short ** pTab2D;
	tabAlloc(&pTab2D,l,c);
	for (i = 0; i < l; i++){
		for (j = 0; j < c; j++){
			pTab2D[i][j] = genRandNb(i,j,pTab2D, l, c);
		}
	}

	return pTab2D;
}

struct Labyrinthe createRandomLab(struct Labyrinthe lab){
	lab.xentrer = 0;
	lab.yentrer = 0;
	lab.xsortie = lab.l-1;
	lab.ysortie = lab.c-1;
	if(lab.c>1&&lab.l>1){
		lab.tab2D = initTab2DRandom(lab.l,lab.c);
	}

	return lab;
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
	tabAlloc(&tab, lab.l, lab.c);
	/*tab = (unsigned short**)malloc(l*sizeof(unsigned short*));
	if (tab == NULL)
		printf("erreur de tableau1\n");
	for(i=0;i<lab.l;i++) {
		tab[i] = (unsigned short *)malloc(lab.c*sizeof(unsigned short));
		if (tab[i] == NULL)
			printf("erreur de tableau2\n");
		}*/

	// Remplissage du tableau bidimensionnel à partir du fichier texte (lecture)
	for(i=0; i < lab.l; i++) {
		for(j=0; j < lab.c; j++) {
			fscanf(fichier, "%d", &tab[i][j]);
		}
	}
	lab.tab2D = tab;
	return lab;
}

void flipBit(unsigned short * n, int range){
	unsigned short mask;
	mask = 1<<range-1;
	*n = *n^mask;
}

//9ème bit sert à indiquer que la cellule est déjà visitée
void visited(unsigned short * n){
	unsigned short mask;
	mask = 1<<9;
	*n=*n|mask;
}

void reset_virtual_wall(struct Labyrinthe * lab){
	unsigned short mask = 0, a = 0, b = 0;
	mask = ~mask;
	a = mask >> 8;
	b = mask << 4;
	mask = a & b;
	mask = ~mask;
	lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] & mask;
}

unsigned short moves(int i, struct Labyrinthe * lab){
	
	if(i==4){
		lab->xsearcher = lab->xsearcher-1;
		reset_virtual_wall(lab);
		lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] | (1 << 5);
	}
	if(i==3){
		lab->ysearcher = lab->ysearcher+1;
		reset_virtual_wall(lab);
		lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] | (1 << 4);
	}
	if(i==2){
		lab->xsearcher = lab->xsearcher+1;
		reset_virtual_wall(lab);
		lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] | (1 << 7);
	}
	if(i==1){
		lab->ysearcher = lab->ysearcher-1;
		reset_virtual_wall(lab);
		lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] | (1 << 6);
	}

	lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] | (1 << 8);
	return lab->tab2D[lab->xsearcher][lab->ysearcher];
}

void moveReverse(int i , struct Labyrinthe * lab){
	if (i == 4){
		lab->xsearcher = lab->xsearcher + 1;
	}
	if (i == 3){
		lab->ysearcher = lab->ysearcher - 1;
	}
	if (i == 2){
		lab->xsearcher = lab->xsearcher - 1;
	}
	if (i == 1){
		lab->ysearcher = lab->ysearcher +1;
	}
}

int isVisited(unsigned short a){
	return a >> 8 & 1;
}

unsigned short getVoisinVal(int i, struct Labyrinthe lab){
	if (i == 4){
		lab.xsearcher = lab.xsearcher - 1;
	}
	if (i == 3){
		lab.ysearcher = lab.ysearcher + 1;
	}
	if (i == 2){
		lab.xsearcher = lab.xsearcher + 1;
	}
	if (i == 1){
		lab.ysearcher = lab.ysearcher - 1;
	}
	return lab.tab2D[lab.xsearcher][lab.ysearcher];
}

void setDistance(struct Labyrinthe * lab, unsigned short dist){
	unsigned short mask = 0;
	mask = ~mask;
	mask = mask >> 6;
	//reset distance to 0
	lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] & mask;
	dist = dist << 10;
	lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] + dist;
}

unsigned short getDistance(unsigned short a){
	return a >> 10;
}

void researchAllPath(struct Labyrinthe lab, unsigned short sommet, unsigned short dist){
	int i = 0;
	unsigned short sommet1 = 0;
	unsigned short voisin = 0;
	unsigned short val = 0;
	int j = 4;
	//visited(&lab.tab2D[lab.xsearcher][lab.ysearcher]);
//	if (lab.xsearcher == lab.xsortie && lab.ysearcher == lab.ysortie){
		if (dist < (lab.tab2D[lab.xsearcher][lab.ysearcher] >> 10)){
			setDistance(&lab, dist);
		}
		if (lab.xsearcher != lab.xentrer || lab.ysearcher != lab.yentrer){
			if ((lab.tab2D[lab.xsearcher][lab.ysearcher] >> 10) == 0){
				setDistance(&lab, dist);
			}
		}
		
/*	} else {
		setDistance(&lab, dist);
	}*/
//	afficherLab(lab, 1);
//	afficherLab(lab,1);
	for(i=4;i>0;i--){
		if (sommet == 4577){
			sommet = 4577;
		}
	//sommet = 4577
		if(!(sommet>>i-1 & 1)){
			if (!(sommet >> i +j - 1 & 1)){
				val = getVoisinVal(i,lab);
//				if (!(isVisited(val))){
				if (getDistance(val) == 0 || dist < getDistance(val)){
					dist++;
					voisin = moves(i, &lab);
					afficherLab(lab,1);
					researchAllPath(lab, voisin, dist);
					dist--;
					moveReverse(i, &lab);
				}
			}
		}
	}
	
}



void setSearcher(struct Labyrinthe * lab, int i	){
	if (i == 4){
		lab->xsearcher = lab->xsearcher - 1;
	}
	if (i == 3){
		lab->ysearcher = lab->ysearcher + 1;
	}
	if (i == 2){
		lab->xsearcher = lab->xsearcher + 1;
	}
	if (i == 1){
		lab->ysearcher = lab->ysearcher - 1;
	}
}

void setShortPath(struct Labyrinthe * lab){
	flipBit(&lab->tab2D[lab->xsearcher][lab->ysearcher], 10);
}

void researchShortestPath(struct Labyrinthe lab){
	int i = 0;
	unsigned short dist_sommet = 0 ,dist_voisin = 0;
	unsigned short sommet = 0;
	while (!(lab.xsearcher == lab.xentrer && lab.ysearcher == lab.yentrer)){
		sommet = lab.tab2D[lab.xsearcher][lab.ysearcher];
		dist_sommet = getDistance(sommet);
		for (i = 0; i < 4; i++){
			if (!(sommet >> i & 1)){
				dist_voisin = getDistance(getVoisinVal(i+1, lab));
				if (dist_voisin == dist_sommet -1){
					setSearcher(&lab, i+1);
					setShortPath(&lab);
					break;
				}
			}
		}
	}
}

int is_solved(struct Labyrinthe lab){
	if (getDistance(lab.tab2D[lab.xsortie][lab.ysortie]) > 0){
		return 1;
	}
	return 0;
}

void researchPath(struct Labyrinthe lab){
	lab.xsearcher = lab.xentrer;
	lab.ysearcher = lab.yentrer;
	researchAllPath(lab, lab.tab2D[lab.xsearcher][lab.ysearcher], 0);

	if (is_solved(lab)){
		lab.xsearcher = lab.xsortie;
		lab.ysearcher = lab.ysortie;
		researchShortestPath(lab);
	}
	
	
}