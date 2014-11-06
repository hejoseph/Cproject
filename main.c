#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "labyrinthe.h"

void MenuDisplay(){
	printf("Entrez le numero de menu : \n");
	printf("1-Generer un labyrinthe fixe, puis l'afficher\n");
	printf("2-Charger votre labyrinthe a partir d'un fichier texte \n");
	printf("3-Generer un labyrinthe aleatoire, puis l'afficher\n");
	printf("4-Quitter le programme\n");
}


int main(void){
	int i = 0, j = 0;
	int choix;
	struct Labyrinthe lab = {NULL,0,0};
//	do{
		MenuDisplay();
//		scanf("%d",&choix);
		switch(3) {
			case 1 :
				//Création du labyrinthe fixe, puis affichage
				lab = createFixedLab(lab,LAB_L_FIX, LAB_C_FIX,0,0,3,3);
				afficherLab(lab);
				printf("\n\n\n");
				afficherPath(lab);
				break;
			case 2 : 
				//char * nomfichier;
			/*	printf("Entrez le chemin absolue de votre fichier à charger : \n");
				scanf("%s", &nomfichier);*/
				lab = createLabFromFile(lab/*, nomfichier*/);
				afficherLab(lab);
				break;
			case 3 :
				while (1){
					printf("Nombre de ligne ? \n");
					scanf("%d", &lab.l);
					printf("Nombre de colonne ? \n");
					scanf("%d", &lab.c);
					lab = createRandomLab(lab);
					afficherLab(lab);
					printf("\n\n\n\n\n");
					afficherPath(lab);
				}
				break;
			case 4 : 
				exit(0);
				break;
			default :
				printf("Le numero du menu est incorrect !\n");
		}
//	}while(choix<1 || choix>4);

}