#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#define LAB_C_FIX 4 /* nombre fixe de colonne pour le labyrinthe fixe*/

#define LAB_L_FIX 4 /* nombre fixe de ligne pour le labyrinthe fixe */
/*const int LAB_C_FIX = 4;
const int LAB_L_FIX = 4;*/


/*Définition du labyrinthe*/
struct Labyrinthe{
	unsigned short** tab2D;
	int l; /*nb ligne*/
	int c;	/*nb colonne*/
	int xentrer;
	int yentrer;
	int xsortie;
	int ysortie;
};



void afficherLab(struct Labyrinthe lab);



struct Labyrinthe createFixedLab(struct Labyrinthe lab, int line, int column);

struct Labyrinthe createRandomLab(struct Labyrinthe lab);

struct Labyrinthe createLabFromFile(struct Labyrinthe lab/*, char * nomfichier*/);

#endif