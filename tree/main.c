#include <stdio.h>
#include <time.h>

#include "treeABR_func.h"

int main()  {
    srand(time(NULL));		//funzione per la generazione casuale di valori
	
	treeABR_func_main();
	io_clearScreen();

	return 1;
}
