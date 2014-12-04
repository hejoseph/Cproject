#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "labyrinthe.h"

void clear(){
	system("clear");
}

//Affichage du menu principal
void main_menu(){
	clear();
	printf("! PROGRAMME LABYRINTHE !\n\n");
	printf("Entrez le numero de menu : \n");
	printf("1-Generation d'un labyrinthe fixe\n");
	printf("2-Generation d'un labyrinthe a partir d'un fichier '.txt'\n");
	printf("3-Generation d'un labyrinthe aleatoire\n");
	printf("4-Quitter le programme\n\n");
}

//Affichage du sous-menu
void sub_menu(struct Labyrinthe lab, int choix){
	if (is_solved(lab)){
		printf("Que voulez-vous faire avec votre labyrinthe? (Entrer le numero de menu) : \n");
		if (choix != 1){
			printf("1-Afficher plusieurs chemins possibles s'ils existent\n");
		}
		if (choix != 2){
			printf("2-Afficher l'un des chemins le plus court\n");
		}
	} else {
		printf("\nIl n'y a pas de chemins possible pour ce labyrinthe\n");
	}
	printf("3-Retour au menu principal\n");
	printf("4-Quitter le programme\n");
	printf("0-Afficher le labyrinthe sans solutions\n");
}

//copier une labyrinthe source dans une labyrinthe dest
void duplicate_struct(struct Labyrinthe source, struct Labyrinthe* dest){
	int i, j = 0;
	for (i = 0; i < source.l; i ++){
		for (j = 0; j < source.c; j++){
			dest->tab2D[i][j] = source.tab2D[i][j];
		}
	}
	dest->c = source.c;
	dest->l = source.l;
	dest->xentrer = source.xentrer;
	dest->yentrer = source.yentrer;
	dest->xsortie = source.xsortie;
	dest->ysortie = source.ysortie;
}


int main(void){
	int i = 0, j = 0;
	int choix;
	char nomfichier[]="";
	char newLab=' ';
	struct Labyrinthe lab = {NULL,0,0};
	struct Labyrinthe lab_copy = { NULL, 0, 0 };
	struct Labyrinthe lab_copy2 = { NULL, 0, 0 };
	do{
		main_menu();
		scanf("%d",&choix);
		clear();
		switch(choix) {
			case 1 :
				//Création initiale du labyrinthe fixe, puis affichage
				lab = createFixedLab(lab, LAB_L_FIX, LAB_C_FIX, 0, 0, 3, 3);

				//allocation d'un autre tableau
				lab_copy.tab2D = tabAlloc(lab_copy.tab2D, LAB_L_FIX, LAB_C_FIX);

				researchPath(lab);
				choix = ' ';
				do{
					duplicate_struct(lab, &lab_copy);
					sub_menu(lab, choix);

					scanf("%d", &choix);
					clear();
					switch (choix) {
					case 0:
						printf("Mode Sans Solutions : \n");
						afficherLab(lab_copy, choix);
						break;
					case 1:
						display_multiple_paths(lab_copy);
						break;
					case 2:
						display_shortest_path(lab_copy);
						break;
					case 3:
						break;
					case 4:
						exit(0);
					default:
						printf("\nVous n'avez pas entrer la bonne valeur ! \n");
						break;
					}
				} while (choix!=3);
				free_memory(&lab);
				free_memory(&lab_copy);
				break;
			case 2 : 
				
				printf("Entrez le nom de votre fichier a charger (matrice.txt est le fichier a tester) : \n");
				scanf("%s", nomfichier);

				//initialisation des labyrinthes 
				lab = createLabFromFile(lab, nomfichier);
				lab_copy.tab2D = tabAlloc(lab_copy.tab2D, lab.l, lab.c);
				lab_copy2.tab2D = tabAlloc(lab_copy.tab2D, lab.l, lab.c);
				duplicate_struct(lab,&lab_copy2);

				researchPath(lab);
				choix = ' ';
				printf("\n");
				do{
					duplicate_struct(lab,&lab_copy);
					sub_menu(lab, choix);
					if (is_solved(lab)){
						if (choix != 5){
							printf("5-Afficher UN seul chemin possible [quelconque]\n\n");
						}
					}
					scanf("%d", &choix);
					clear();
					switch (choix) {
					case 0 : 
						printf("Mode Sans Solutions : \n");
						afficherLab(lab_copy, choix);
						break;
					case 1 :
						display_multiple_paths(lab_copy);
						break;
					case 2:
						display_shortest_path(lab_copy);
						break;
					case 3:
						break;
					case 4:
						exit(0);
					case 5:
						if (is_solved(lab)){
							display_one_path(lab_copy2);
						}
						break;
					default :
						printf("\nVous n'avez pas entrer la bonne valeur ! \n");
						break;
					}
				} while (choix!=3);
				//free_memory(&lab);
				free_memory(&lab_copy);
				free_memory(&lab_copy2);
				break;
			case 3 :
				printf("Quel est le nombre de ligne et de colonne? \n(exemple: taper '3 2' pour ligne = 3, colonne = 2)\n");
				scanf("%d %d", &lab.l, &lab.c);
				clear();
				lab = createRandomLab(lab);
				afficherLab(lab, 0);
				printf("\nEntrer les coordonees de l'entrer du labyrinthe (exemple : '3 2' pour ligne numero 3 et colonne numero 2) : \n");
				do{
					scanf("%d %d", &lab.xentrer, &lab.yentrer);
					if(lab.xentrer > (lab.l-1) || lab.yentrer > (lab.c-1) || lab.xentrer < 0 || lab.yentrer <0){printf("Erreur de saisie, ressaisir les coordonnees de l'entrer :\n" );}
				} while((lab.xentrer > (lab.l-1) || lab.yentrer > (lab.c-1)) || (lab.xentrer < 0 || lab.yentrer <0));
				clear();
				afficherLab(lab, 0);
				printf("\nEntrer les coordonees de la sortie du labyrinthe (exemple : '3 2' pour ligne numero 3 et colonne numero 2) :\n");
				do{
					scanf("%d %d", &lab.xsortie, &lab.ysortie);
					if(lab.xsortie > (lab.l-1) || lab.ysortie > (lab.c-1) || lab.xsortie < 0 || lab.ysortie <0){printf("Erreur de saisie, ressaisir les coordonnees de la sortie :\n" );}
				} while(lab.xsortie > (lab.l-1) || lab.ysortie > (lab.c-1) || lab.xsortie < 0 || lab.ysortie <0);
				clear();
				afficherLab(lab, 0);
				lab_copy.tab2D = tabAlloc(lab_copy.tab2D, lab.l, lab.c);
				researchPath(lab);
				choix = ' ';
				printf("\n");
				do{
					duplicate_struct(lab, &lab_copy);
					sub_menu(lab, choix);
					scanf("%d", &choix);
					clear();
					switch (choix) {
					case 0:
						printf("Mode Sans Solutions : \n");
						afficherLab(lab_copy, choix);
						break;
					case 1:
						display_multiple_paths(lab_copy);
						break;
					case 2:
						display_shortest_path(lab_copy);
						break;
					case 3:
						break;
					case 4:
						exit(0);
					default:
						printf("\nVous n'avez pas entrer la bonne valeur ! \n");
						break;
					}
				} while (choix != 3);
				free_memory(&lab);
				free_memory(&lab_copy);
				break;
			case 4 : 
				exit(0);
				break;
			default :
				printf("Le numero du menu est incorrect !\n");
				break;
		}
	}while(1);

}
