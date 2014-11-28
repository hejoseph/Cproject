#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "labyrinthe.h"
ss
//Affichage du menu principal
void main_menu(){
	printf("\n\nEntrez le numero de menu : \n");
	printf("1-Afficher un labyrinthe fixe\n");
	printf("2-Afficher un labyrinthe à partir d'un fichier '.txt'\n");
	printf("3-Afficher un labyrinthe aleatoire\n");
	printf("4-Quitter le programme\n\n");
}

void initLab(struct Labyrinthe* lab, int ligne, int colonne, int xentrer, int yentrer, int xsortie, int ysortie){
	lab->tab2D = tabAlloc(lab->tab2D, ligne, colonne);
	lab->l = ligne;
	lab->c = colonne ;
	lab->xentrer = xentrer ;
	lab->yentrer = yentrer ;
	lab->xsortie = xsortie;
	lab->ysortie = ysortie;

}

//Affichage du sous-menu
void sub_menu(struct Labyrinthe lab, int choix){
	if (is_solved(lab)){
		printf("\n\nQue voulez-vous faire avec votre labyrinthe? (Entrer le numero de menu) : \n");
		if (choix!=0){
			printf("0-Reafficher le labyrinthe sans solutions\n");
		}
		if (choix != 1){
			printf("1-Afficher plusieurs chemins possibles\n");
		}
		if (choix != 2){
			printf("2-Afficher l'un des chemins le plus court\n");
		}
	} else {
		printf("\nIl n'y a pas de chemins possible pour ce labyrinthe\n");
	}
	printf("3-Retour au menu principal\n");
	printf("4-Quitter le programme\n");
}

void duplicate_struct(struct Labyrinthe source, struct Labyrinthe* dest){
	int i, j = 0;
	for (i = 0; i < source.l; i ++){
		for (j = 0; j < source.c; j++){
			dest->tab2D[i][j] = source.tab2D[i][j];
		}
	}
}


int main(void){
	int i = 0, j = 0;
	int choix;
	char newLab=' ';
	struct Labyrinthe lab = {NULL,0,0};
	struct Labyrinthe lab_copy = { NULL, 0, 0 };
	do{
		main_menu();
		scanf("%d",&choix);
		switch(choix) {
			case 1 :
					//Création initiale du labyrinthe fixe, puis affichage
					lab = createFixedLab(lab, LAB_L_FIX, LAB_C_FIX, 0, 0, 3, 3);
					//allocation d'un autre tableau
					lab_copy.tab2D = tabAlloc(lab_copy.tab2D, LAB_L_FIX, LAB_C_FIX);
					afficherLab(lab, 0);
					researchPath(lab);
					choix = ' ';
				do{
					duplicate_struct(lab, &lab_copy);
					sub_menu(lab, choix);
					scanf("%d", &choix);
					switch (choix) {
					case 0:
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
				} while (1);
				break;
			case 2 : 
				//char * nomfichier;
			/*	printf("Entrez le chemin absolue de votre fichier à charger : \n");
				scanf("%s", &nomfichier);*/
				lab = createLabFromFile(lab/*, nomfichier*/);
				lab_copy = createLabFromFile(lab);
				afficherLab(lab,0);
				researchPath(lab);
				choix = ' ';
				printf("\n\n\n");
				do{
					duplicate_struct(lab,&lab_copy);
					sub_menu(lab, choix);
					scanf("%d", &choix);
					/*if (choix == 0 || choix == 1 || choix == 2){
						afficherLab(lab, choix);
					} else if (choix == 3){
						break;
					} else if (choix == 4){
						exit(0);
					} else {
						printf("\nNumero incorrect ! \n\n");
					}*/
					switch (choix) {
					case 0 : 
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
					default :
						printf("\nVous n'avez pas entrer la bonne valeur ! \n");
						break;
					}
				} while (choix!=3);
//				afficherPath(lab);
//				afficherLab(lab);
				break;
			case 3 :
				choix = 0;
				while(!(choix==3)){
					printf("Quel est le nombre de ligne et de colonne? \n(exemple: taper '3 2' pour ligne = 3, colonne = 2)\n");
					scanf("%d %d", &lab.l, &lab.c);
					printf("\nPosition Entrer du labyrinthe ? \n");
					scanf("%d %d", &lab.xentrer, &lab.yentrer);
					printf("\nPosition Sortie du labyrinthe ? \n");
					scanf("%d %d", &lab.xsortie, &lab.ysortie);
					do{
						lab = createRandomLab(lab);
						initLab(&lab_copy, lab.l, lab.c, lab.xentrer, lab.yentrer, lab.xsortie, lab.ysortie);

						afficherLab(lab,0);
					
						researchPath(lab);
					
						if(!(is_solved(lab))){
							newLab = ' ';
							printf("\nAucun chemin, voulez-vous regenerer un autre labyrinthe?(O/N)\n");
							scanf("%c",&newLab);
exit(1);
							/*if(newLab == 'o' || newLab == 'O'){
								free(lab.tab2D);
							}*/
						}
					} while (newLab == 'o' || newLab == 'O');
					printf("\n\n\n\n\n");
					choix = ' ';
					do{
						duplicate_struct(lab,&lab_copy);
						sub_menu(lab, choix);
						scanf("%d", &choix);
						switch (choix) {
						case 0:
							afficherLab(lab, choix);
							break;
						case 1:
							display_multiple_paths(lab);
							break;
						case 2:
							display_shortest_path(lab);
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
				}
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
