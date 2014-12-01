#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"

unsigned short ** tabAlloc(unsigned short ** pTab, int l, int c){
	int i = 0;
	pTab = malloc(l*sizeof(unsigned short *));
	if (pTab == NULL)
	{
		fprintf(stderr, "Memoire insuffisante, fin du programme\n");
		exit(1);
	}
	for (i = 0; i < l; i++)
	{
		pTab[i] = malloc(c * sizeof(unsigned short));
		if (pTab[i] == NULL)
		{
			fprintf(stderr, "Memoire insuffisante, fin du programme\n");
			exit(1);
		}
	}

	return pTab;
}


//Initialisation d'un tableau 2 dimension � valeur fixe
unsigned short** initTab2DFixed(){
	int i = 0, j = 0;
	int l = LAB_L_FIX;
	int c = LAB_C_FIX;
	//Valeur fix�
	unsigned short tab2Dfixe[LAB_L_FIX][LAB_C_FIX] = { { 11, 12, 11, 12 }, { 9, 6, 9, 6 }, { 3, 10, 0, 14 }, { 11, 10, 2, 14 } };
	unsigned short **pTab = NULL;

	pTab = tabAlloc(pTab, LAB_L_FIX, LAB_C_FIX);
	
	
	//Remplissage du tableau bidimensionnel avec les valeurs fix�es au d�part.
	for (i = 0; i<l ; i++){
		for (j = 0; j < c; j++){
			pTab[i][j] = tab2Dfixe[i][j];
		}
	}
	return pTab;
}

// Cr�er un labyrinthe fixe
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
	printf("\n");
/*
	for(i=0;i<lab.l;i++){
		for(j=0;j<lab.c;j++){
			printf("%d\t",lab.tab2D[i][j]);
			if(j==lab.c-1){
				printf("\n");
			}
		}
	}
*/	
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
	printf("\n\n");

/*
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
*/
}


//G�n�re un nombre entre a et b
unsigned short genNbBetween(int a, int b){
	int r;
	b = b + 1;
	r = (rand() % b);
	while (r<a){
		r = (rand() % b);
	}
	return r;
}

//G�n�re un nombre al�atoire, qui concorde avec les murs de ses voisins.
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


// Cr��r un tableau 2D al�atoirement, en ayant une coh�rence entre les murs voisins
unsigned short ** initTab2DRandom(int l, int c){
	int i =0,j = 0;
	unsigned short ** pTab2D = NULL;
	pTab2D = tabAlloc(pTab2D,l,c);
//	tabAlloc(&pTab2D,l,c);
	for (i = 0; i < l; i++){
		for (j = 0; j < c; j++){
			pTab2D[i][j] = genRandNb(i,j,pTab2D, l, c);
		}
	}

	return pTab2D;
}

/**
*	Initialise mon labyrinthe avec des valeurs al�atoires
*/
struct Labyrinthe createRandomLab(struct Labyrinthe lab){
	if(lab.c>1&&lab.l>1){
		lab.xentrer = -1;
		lab.yentrer = -1;
		lab.xsortie = -1;
		lab.ysortie = -1;
		lab.tab2D = initTab2DRandom(lab.l,lab.c);
	}

	return lab;
}

/**
* Initialise les param�tre de mon labyrinthe � partir d'un fichier
*/
struct Labyrinthe createLabFromFile(struct Labyrinthe lab, char * nomfichier){
	unsigned short **tab = NULL; // pointeur
	int l; // nombre de ligne de la matrice
	int i=0;
	int c; // nombre de colonne de la matrice
	int j=0; 
	int xentrer, yentrer, xsortie, ysortie;
	
	FILE *fichier;

	// ouverture du ficher texte
	fichier = fopen(nomfichier, "r");
	if (fichier == NULL){	//test d'ouverture du fichier
		printf("erreur de fichier\n");
		exit(1);
	}
	// recuperation taille et position entrer & sortie

	fscanf(fichier, "%d %d %d %d %d %d", &l, &c, &xentrer, &yentrer, &xsortie, &ysortie);


	lab.xentrer = xentrer;
	lab.yentrer = yentrer;
	lab.xsortie = xsortie;
	lab.ysortie = ysortie;
	lab.l = l;
	lab.c = c;

	// declaration du tableau 2D
	tab = tabAlloc(tab, lab.l, lab.c);

	// Remplissage du tableau bidimensionnel � partir du fichier texte (lecture)
	for(i=0; i < lab.l; i++) {
		for(j=0; j < lab.c; j++) {
			fscanf(fichier, "%d", &tab[i][j]);
		}
	}
	lab.tab2D = tab;
	return lab;
}

//Modifie le bit d'une valeur, tout en sp�cifiant la rang�e du bit � modifier
void flipBit(unsigned short * n, int range){
	unsigned short mask;
	mask = 1<<range-1;
	*n = *n^mask;
}

//9�me bit sert � indiquer que la cellule est d�j� visit�e
void visited(unsigned short * n){
	unsigned short mask;
	mask = 1<<9;
	*n=*n|mask;
}

//R�nitialise les murs virtuels de la case ou est situ� le chercheur.
void reset_virtual_wall(struct Labyrinthe * lab){
	unsigned short mask = 0, a = 0, b = 0;
	mask = ~mask;
	a = mask >> 8;
	b = mask << 4;
	mask = a & b;
	mask = ~mask;
	lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] & mask;
}

/**
* Deplacement du chercheur vers une case voisine, en r�initialisant les murs virtuels, pour y rajouter un nouveau
*/
unsigned short moves(int i, struct Labyrinthe * lab, char * mode){
	
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
	if (mode =="research_all"){
		lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] | (1 << 8);
	}
	if (mode == "research_multiple"){
		lab->tab2D[lab->xsearcher][lab->ysearcher] = lab->tab2D[lab->xsearcher][lab->ysearcher] | (1 << 9);
	}
	return lab->tab2D[lab->xsearcher][lab->ysearcher];
}

/**
* 
*/
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

//Verifie si la case (valeur) a �t� visit�e ou non
int isVisited(unsigned short a){
	return a >> 8 & 1;
}

/**
* Retourne la valeur d'une case voisine
*/
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

/**
* Modifie la distance stock�e par la case(du tableau 2D) point�e par le chercheur
*/
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

/** Fonction r�cursive :
*Recherche tous les chemins d'un labyrinthe, � partir d'un sommet, 
*en affectant une distance (incr�ment�e de 1 � chaque fois) 
*� la case voisine s'il n'y a pas de mur entre le sommet et la case voisine
*/
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
					voisin = moves(i, &lab,"research_all");
					//afficherLab(lab,1);
					researchAllPath(lab, voisin, dist);
					dist--;
					moveReverse(i, &lab);
				}
			}
		}
	}
	
}


/**
* Modifie les positions x,y du chercheur
*/
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

/**
* Modifie le 10�me bit de la valeur � "1", pour indiquer que la case fait partie des plus courts chemins 
*/
void setShortPath(struct Labyrinthe * lab){
	flipBit(&lab->tab2D[lab->xsearcher][lab->ysearcher], 10);
}

/**
* Recherche du plus court chemin � partir de la sortie du labyrinthe.
*/
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

/** 
*V�rifie si le labyrinthe est solvable
*/
int is_solved(struct Labyrinthe lab){
	if (getDistance(lab.tab2D[lab.xsortie][lab.ysortie]) > 0){
		return 1;
	}
	return 0;
}

//Recherche de tous les chemins y compris le plus court s'il existe.
void researchPath(struct Labyrinthe lab){
	lab.xsearcher = lab.xentrer;
	lab.ysearcher = lab.yentrer;
	//Recherche � partir de l'entr�e du labyrinthe
	researchAllPath(lab, lab.tab2D[lab.xsearcher][lab.ysearcher], 0);
}

void researchMultiplePaths(struct Labyrinthe lab, unsigned short sommet, int tree_level){
	int i = 0;
	unsigned short val = 0;
	unsigned short voisin = 0;
	int j = 4;
//	unsigned short dist_sommet = 0, dist_voisin = 0;
	for (i = 4; i>0; i--){
		if (!(sommet >> i - 1 & 1)){
			val = getVoisinVal(i, lab);
			if (tree_level == 1){
				voisin = moves(i, &lab, "research_multiple");
				tree_level++;
				researchMultiplePaths(lab, voisin, tree_level);
				moveReverse(i, &lab);
			}
			if (getDistance(val) == getDistance(sommet)-1 ){
				voisin = moves(i, &lab, "research_multiple");
				researchMultiplePaths(lab, voisin, tree_level);
				moveReverse(i, &lab);
			}
			
		}
	}
}

//Affiche plusieurs chemins possibles.
void display_multiple_paths(struct Labyrinthe lab){

	if (is_solved(lab)){
		lab.xsearcher = lab.xsortie;
		lab.ysearcher = lab.ysortie;
		researchMultiplePaths(lab, lab.tab2D[lab.xsearcher][lab.ysearcher], 1);
	}
	afficherLab(lab, 2);
}

//Affiche le plus court chemin.
void display_shortest_path(struct Labyrinthe lab){
	if (is_solved(lab)){
	
		lab.xsearcher = lab.xsortie;
		lab.ysearcher = lab.ysortie;
		researchShortestPath(lab);
	}
	afficherLab(lab, 2);
}


void free_memory(struct Labyrinthe* lab){
	int i = 0;
	if (lab->tab2D != NULL){
		for (i = 0; i<lab->l; i++){
			free(lab->tab2D[i]);
		}
		free(lab->tab2D);
	}
}
