#include "treeABR_func.h"

//Funzione prinicpale dell'Albero
void treeABR_func_main()  {
	TREEel albero = NULL;	//inizializzazione della struttura

	int choiceMenu;
	do	{
		io_clearScreen();
		switch(choiceMenu = treeABR_func_menu(&albero))	{	//chiamata del menu principale con scelta dell'albero con controllo di esistenza dell'Albero
			case 1:
				printf("GENERAZIONE ALBERO\n\n");
				treeABR_func_generate(&albero);
				break;
			case 2:
				printf("INSERIMENTO NUOVO ELEMENTO NELL'ALBERO\n\n");
                treeABR_func_insertKey(&albero);
				break;
			case 3:
				printf("STAMPA ALBERO\n\n");
                treeABR_func_print(&albero);
				break;
			case 4:
				printf("CANCELLAZIONE ELEMENTO NELL'ALBERO\n\n");
				treeABR_func_deleteKey(&albero);
				break;
            case 5:
				printf("CANCELLAZIONE COMPLETA DELL'ALBERO\n\n");
				treeABR_func_delete(&albero);
				break;
            case 6:
				printf("SESSIONE TERMINATA\n\n");
		}
		io_pressKey();
	}while(choiceMenu != 6);
}

//Interfaccia utente
int treeABR_func_menu(TREE albero)	{
	int choiceMenu;
	printf("\t\t\tStack - MENU PRINCIPALE\n");
	printf("1. Genera Albero\n");
	printf("2. Inserisci nuovo elemento nell'Albero\n");
    if(*albero)    {   //se l'Albero esiste, mostro gli altri elementi del menu
        printf("3. Stampa Albero\n");
        printf("4. Cancello elemento nell'Albero\n");
        printf("5. Cancella completamente l'Albero");
    }
    printf("\n");
    printf("6. Esci\n");
    printf("\n\n");
	do {
		printf("SCELTA: ");
		if(((choiceMenu = io_getInteger()) < 1 || choiceMenu > 6) || (!*albero && (choiceMenu > 2 && choiceMenu < 6))) //nel caso l'utente inserisca una scelta del menu non presente
			printf("ATTENZIONE: Valore non valido\n\n");
	}while((choiceMenu < 1 || choiceMenu > 6) || (!*albero && (choiceMenu > 2 && choiceMenu < 6)));
    io_clearScreen();   //pulizia dello schermo del terminale
	return choiceMenu;
}

//Generazione di un'Albero con valori randomici
void treeABR_func_generate(TREE albero) {
    int idx, n_elem;
    if(*albero)	{	//se è già presente, chiedo al'utente quale operazione effettuare sull'Albero
        int choice;
        printf("ATTENZIONE: Albero già presente. Cosa preferisci fare?\n\t1. Generazione nuovo Albero\t2. Inserimento nuovi elementi\n\n");
        do  {
            printf("SCELTA: ");
            if((choice = io_getInteger()) < 1 || choice > 2)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(choice < 1 || choice > 2);
        if(choice == 1) {
            treeABR_delete(albero);   //con '0' in parametro non elimino completamente l'Albero ma solo tutti i puntatori al suo interno
            printf("\n");
            if(!albero)
                printf("Albero eliminato\n\n");
        }
    }
    
    do  {
        printf("Quanti elementi vuoi inserire nell'Albero?: ");
        if((n_elem = io_getInteger()) < 1)
			printf("ATTENZIONE: Valore non valido\n\n");
	}while(n_elem < 1);

    for(idx=0;idx<n_elem;idx++)
        treeABR_insertKey_ver2(albero, random_num(1, MAX_tree));	//inserisce un numero casuale compreso fra 1 e MAX_tree
    printf("\n");
    treeABR_func_print(albero);
}

//Inserimento in input del valore nell'Albero
void treeABR_func_insertKey(TREE albero)   {
    int val;
    do  {
        printf("Quale valore vuoi inserire nell'Albero?: ");
        if((val = io_getInteger()) < 1)
            printf("ATTENZIONE: Valore non valido\n\n");
    }while(val < 1);

    treeABR_insertKey_ver2(albero, val);
    printf("\n");
    treeABR_func_print(albero);
}

//Estrazione con conferma dell'elemento dell'Albero
void treeABR_func_deleteKey(TREE albero) {
    treeABR_func_print(albero);
    int val;
    do  {
        printf("Quale valore vuoi eliminare dall'Albero?: ");
        if((val = io_getInteger()) < 1)
            printf("ATTENZIONE: Valore non valido\n\n");
    }while(val < 1);

    treeABR_deleteKey(albero, val);
    printf("\n");
    treeABR_func_print(albero);
}

//Eliminazione con conferma dell'Albero
void treeABR_func_delete(TREE albero)  {
    char choice;
    do  {
        printf("Sei sicuro di voler eliminare l'Albero? (S/N): ");
        choice = toupper(io_getChar()); //se metto un carattere minuscolo, lo rende maiuscolo
        if(choice != 'S' && choice != 'N')
            printf("ATTENZIONE: scelta non valida\n\n");
    }while(choice != 'S' && choice != 'N');

    if(choice == 'S')   {
        treeABR_delete(albero);   //con '0' in parametro non elimino completamente l'Albero ma solo tutti i puntatori al suo interno
        printf("\n");
        if(!*albero)
            printf("Albero eliminato\n\n");
    }
}

//Stampa dell'Albero
void treeABR_func_print(TREE albero)  {
    printf("\tNumero elementi: %d\n", treeABR_inOrder(albero, 0));
    printf("\tAltezza massima: %d\n", treeABR_postOrder_h(albero, 0));
}