#include <stdio.h>
#include <time.h>

#include "tree/treeABR_func.h"

int main()  {
	int choiceMenu;

    srand(time(NULL));		//funzione per la generazione casuale di valori
	
	do	{
		io_clearScreen();
		printf("\t\tProgetto 2 - Gruppo 32 - MENU INTRODUTTIVO\n");

		printf("1. Calcolo altezza media degli alberi\n");
		printf("2. Merge di due alberi\n");
		printf("3. Gestione singolo albero (Esercizio Rotazione e Bilanciamento)\n");
		printf("4. Esci\n");
		printf("\n\n");
		do {
			printf("SCELTA: ");
			if((choiceMenu = io_getInteger()) < 1 || choiceMenu > 4) //nel caso l'utente inserisca una scelta del menu non presente
				printf("ATTENZIONE: Valore non valido\n\n");
		}while(choiceMenu < 1 || choiceMenu > 4);
		io_clearScreen();
		switch(choiceMenu)	{
			case 1:
				printf("CALCOLO ALTEZZA MEDIA ALBERI\n\n");
                treeABR_func_average();
				break;
			case 2:
				printf("MERGE 2 ALBERI\n\n");
				treeABR_func_merge();
				break;
			case 3:
				treeABR_func_main();
				break;
			case 4:
				printf("\n");
				printf("SESSIONE TERMINATA\n\n");
		}
		if(choiceMenu != 3)	//non premo invio quando torno al menu introduttivo dopo aver lavorato su treeABR_func_main
			io_pressKey();
	}while(choiceMenu != 4);

	io_clearScreen();
	return 1;
}
