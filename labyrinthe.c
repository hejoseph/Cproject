#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"


unsigned short** initTab2DFixed(){
	int i = 0, j = 0;
	unsigned short tab2Dfixe[LAB_C_FIX][LAB_L_FIX] = { { 11, 12, 11, 12 }, { 9, 6, 9, 6 }, { 3, 10, 0, 14 }, { 11, 10, 2, 14 } };
	unsigned short **pLAB;

	pLAB = malloc(LAB_L_FIX*sizeof(unsigned short));
	if (pLAB == NULL)
	{
		fprintf(stderr, "Allocation impossible \n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i<sizeof(pLAB); i++){
		*(pLAB + i) = malloc(LAB_C_FIX*sizeof(unsigned short));
		if (*(pLAB + i) == NULL)
		{
			fprintf(stderr, "Allocation impossible \n");
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i<sizeof(pLAB); i++){
		for (j = 0; j < sizeof(*(pLAB + i)); j++){
			pLAB[i][j] = tab2Dfixe[i][j];
		}
	}

	return pLAB;
}


struct Labyrinthe createFixedLab(struct Labyrinthe lab, int line, int column){
	lab.l = line;
	lab.c = column;
	lab.tab2D = initTab2DFixed();
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

/*
void afficherLab(struct Labyrinthe lab){
	if (sizeof(lab.tab2D)>1&&sizeof(*lab.tab2D)>1){
		int i = 0, j = 0;
		int t = 0, f = 0;
		char mur = 'h';
		unsigned short ** tab2D = lab.tab2D;
		do{
			printf("\n");
			if (i < sizeof(tab2D)){
				mur = 'h';
			}
			t = 0;
			j = 0;
			while (t == 0){
				if (mur == 'h'){
					if (tab2D[i][j] >> 3 & 1){
						affMurH();	
						
					}
					j++;
					if (j == sizeof(*tab2D)){
						mur = 'g';
						j = 0;
						printf("\n");
					}
				}
				else if (mur == 'g'){
					if (tab2D[i][j] & 1){
						affMurG();
						
					}
					if (j == sizeof(*tab2D)-1){
						affMurD();
						t = 1;
						if (i == sizeof(tab2D)-1){
							mur = 'b';
						
						}
					}
					j++;
					
				}
				else {
					affMurB();
					if ((i == sizeof(tab2D)) && (j == sizeof(*tab2D) - 1)){
						f = 1;
						t = 1;
					}
					j++;
				}
				
				
			}
			i++;
		} while (f==0);
		
	}
}
*/


void afficherLab(struct Labyrinthe lab){
	int i=0, j=0;
	if (sizeof(lab.tab2D)>1&&sizeof(*lab.tab2D)>1){
		for(i=0;i<sizeof(lab.tab2D);i++){
			for(j=0;j<sizeof(*lab.tab2D);j++){
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
			for(j=0;j<sizeof(*lab.tab2D);j++){
				if(lab.tab2D[i][j]&1){
					affMurG();
					printf("   ");
				} else {
					printf(" ");
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