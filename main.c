#include <stdio.h>
#include <time.h>

#include "tree/treeABR_func.h"

int main()  {
    srand(time(NULL));		//funzione per la generazione casuale di valori
	io_clearScreen();
	printf("\t\t\tLibreria Gruppo 32 - MENU PRINCIPALE\n");

	treeABR_func_main();

	io_clearScreen();
	return 1;
}
