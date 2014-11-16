#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "labyrinthe.h"

//Affichage du menu principal
void main_menu(){
	printf("\n\nEntrez le numero de menu : \n");
	printf("1-Afficher un labyrinthe fixe\n");
	printf("2-Afficher un labyrinthe à partir d'un fichier '.txt'\n");
	printf("3-Afficher un labyrinthe aleatoire\n");
	printf("4-Quitter le programme\n\n");
}

//Affichage du sous-menu
void sub_menu(struct Labyrinthe lab){
	if (is_solved(lab)){
		printf("\n\nQue voulez-vous faire avec votre labyrinthe? (Entrer le numero de menu) : \n");
		printf("0-Reafficher le labyrinthe sans solutions\n");
		printf("1-Afficher tous les chemins possibles\n");
		printf("2-Afficher l'un des chemins le plus court\n");
	} else {
		printf("\nIl n'y a pas de chemins possible pour ce labyrinthe\n");
	}
	printf("3-Retour au menu principal\n");
	printf("4-Quitter le programme\n");
}


int main(void){
	int i = 0, j = 0;
	int choix;
	struct Labyrinthe lab = {NULL,0,0};
//	do{
		main_menu();
//		scanf("%d",&choix);
		switch(3) {
			case 1 :
					//Création du labyrinthe fixe, puis affichage
					lab = createFixedLab(lab, LAB_L_FIX, LAB_C_FIX, 0, 0, 3, 3);
					afficherLab(lab, 0);
					
					researchPath(lab);
				do{
					sub_menu(lab);
					scanf("%d", &choix);
					if (choix == 0 || choix == 1 || choix == 2){
						afficherLab(lab,choix);
					} else if (choix == 3){
						break;
					} else if (choix == 4){
						exit(0);
					} else {
						printf("\nNumero incorrect ! \n\n");
					}
				} while (1);
				break;
			case 2 : 
				//char * nomfichier;
			/*	printf("Entrez le chemin absolue de votre fichier à charger : \n");
				scanf("%s", &nomfichier);*/
				lab = createLabFromFile(lab/*, nomfichier*/);
				afficherLab(lab,0);
				researchPath(lab);
				printf("\n\n\n");
				do{
					sub_menu(lab);
					scanf("%d", &choix);
					if (choix == 0 || choix == 1 || choix == 2){
						afficherLab(lab, choix);
					} else if (choix == 3){
						break;
					} else if (choix == 4){
						exit(0);
					} else {
						printf("\nNumero incorrect ! \n\n");
					}
				} while (1);
//				afficherPath(lab);
//				afficherLab(lab);
				break;
			case 3 :
				choix = 0;
				while(!(choix==3)){
					printf("Nombre de ligne ? \n");
					scanf("%d", &lab.l);
					printf("Nombre de colonne ? \n");
					scanf("%d", &lab.c);
					lab = createRandomLab(lab);
					afficherLab(lab,0);
					
					researchPath(lab);
					printf("\n\n\n\n\n");
					do{
						sub_menu(lab);
						scanf("%d", &choix);
						if (choix == 0 || choix == 1 || choix == 2){
							afficherLab(lab, choix);
						} else if (choix == 3){
							break;
						} else if (choix == 4){
							exit(0);
						} else {
							printf("\nNumero incorrect ! \n\n");
						}
					} while (1);
				}
				break;
			case 4 : 
				exit(0);
				break;
			default :
				printf("Le numero du menu est incorrect !\n");
				break;
		}
//	}while(1);

}