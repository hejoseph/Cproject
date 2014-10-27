#include <stdio.h>
#include <stdlib.h>
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
		//scanf("%d",&choix);
		switch(1) {
			case 1 :
				lab = createFixedLab(lab,LAB_L_FIX, LAB_C_FIX);
				afficherLab(lab);
				break;
			case 2 : 
				break;
			case 3 :
				lab = createRandomLab(lab);
				//afficherLab(lab);
				break;
			case 4 : 
				exit(0);
				break;
			default :
				printf("Le numero du menu est incorrect !\n");
		}
//	}while(choix<1 || choix>4);

}