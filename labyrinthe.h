#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#define LAB_C_FIX 4 /* nombre fixe de colonne pour le labyrinthe fixe*/

#define LAB_L_FIX 4 /* nombre fixe de ligne pour le labyrinthe fixe */

/*Définition du labyrinthe*/
struct Labyrinthe{
	unsigned short** tab2D;
	int l; /*nb ligne*/
	int c;	/*nb colonne*/
	int xentrer;
	int yentrer;
	int xsortie;
	int ysortie;
	int xsearcher;
	int ysearcher;
};



void afficherLab(struct Labyrinthe lab, int menu);



struct Labyrinthe createFixedLab(struct Labyrinthe lab, int line, int column, int xe,int ye,int xs,int ys);

struct Labyrinthe createRandomLab(struct Labyrinthe lab);

struct Labyrinthe createLabFromFile(struct Labyrinthe lab, char * nomfichier);

void researchPath(struct Labyrinthe lab);

int is_solved(struct Labyrinthe lab);

unsigned short ** tabAlloc(unsigned short ** pTab, int l, int c);

void display_multiple_paths(struct Labyrinthe lab);

void display_shortest_path(struct Labyrinthe lab);

void display_one_path(struct Labyrinthe lab);

void free_memory(struct Labyrinthe* lab);

#endif
