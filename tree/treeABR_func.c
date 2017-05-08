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
				printf("ROTAZIONE DELL'ALBERO\n\n");
				treeABR_func_rotate(&albero);  //aggiorno il riferimento alla nuova radice dell'albero ruotato
				break;
            case 7:
				printf("BILANCIAMENTO DELL'ALBERO\n\n");
				treeABR_func_balance(&albero);
				break;
		}
        if(choiceMenu != 8)
		    io_pressKey();
	}while(choiceMenu != 8);
}

//Interfaccia utente
int treeABR_func_menu(TREE albero)	{
	int choiceMenu;
	printf("\t\t\tAlbero - MENU PRINCIPALE\n");
	printf("1. Genera Albero\n");
	printf("2. Inserisci nuovo elemento nell'Albero\n");
    if(*albero)    {   //se l'Albero esiste, mostro gli altri elementi del menu
        printf("3. Stampa Albero\n");
        printf("4. Cancella elemento nell'Albero\n");
        printf("5. Cancella completamente l'Albero\n");
        printf("6. Ruota sottoalbero nell'Albero\n");
        printf("7. Bilancia l'Albero");
    }
    printf("\n");
    printf("8. Torna al Menu Introduttivo\n");
    printf("\n\n");
	do {
		printf("SCELTA: ");
		if(((choiceMenu = io_getInteger()) < 1 || choiceMenu > 8) || (!*albero && (choiceMenu > 2 && choiceMenu < 8))) //nel caso l'utente inserisca una scelta del menu non presente
			printf("ATTENZIONE: Valore non valido\n\n");
	}while((choiceMenu < 1 || choiceMenu > 8) || (!*albero && (choiceMenu > 2 && choiceMenu < 8)));
    io_clearScreen();   //pulizia dello schermo del terminale
	return choiceMenu;
}


//Calcolo altezza media di sequenza di Alberi
void treeABR_func_average()  {
	int n_trees, n_nodes_A = 0, n_nodes_B = 0, choiceMode;
    do  {
        printf("Quanti alberi vuoi generare?: ");
        if((n_trees = io_getInteger()) < 1)
            printf("ATTENZIONE: Valore non valido\n\n");
    }while(n_trees < 1);
    printf("\n");
    do  {
        printf("Numero fisso o numero variabile di nodi fra gli alberi?\n\t1. Fisso\t2. Variabile: ");
        if((choiceMode = io_getInteger()) < 1 || choiceMode > 2)
            printf("ATTENZIONE: Valore non valido\n\n");
    }while(choiceMode < 1 || choiceMode > 2);
    printf("\n");
    if(choiceMode == 1) {
        do  {
            printf("Quanti nodi vuoi inserire negli alberi?: ");
            if((n_nodes_A = io_getInteger()) < 1)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(n_nodes_A < 1);
    } else if(choiceMode == 2)  {
        do  {
            printf("Quale numero MINIMO di nodi vuoi inserire negli alberi?: ");
            if((n_nodes_A = io_getInteger()) < 1)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(n_nodes_A < 1);
        printf("\n");
        do  {
            printf("Quale numero MASSIMO di nodi vuoi inserire negli alberi?: ");
            if((n_nodes_B = io_getInteger()) < n_nodes_A)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(n_nodes_B < n_nodes_A);
    }
    treeABR_average(n_trees, n_nodes_A, n_nodes_B);
}

//Calcolo altezza media di sequenza di Alberi
void treeABR_func_merge()  {
	TREEel albero1 = NULL;
    TREEel albero2 = NULL;
    int idx;
    for(idx=0;idx<random_num(10, 30);idx++) //si inseriscono un numero di nodi casuale compreso tra 10 e 30 in albero1
        treeABR_insertKey_v2(&albero1, random_num(1, MAX_tree));	//inserisce un numero casuale compreso fra 1 e MAX_tree

    for(idx=0;idx<random_num(10, 30);idx++) //si inseriscono un numero di nodi casuale compreso tra 10 e 30 in albero2
        treeABR_insertKey_v2(&albero2, random_num(1, MAX_tree));	//inserisce un numero casuale compreso fra 1 e MAX_tree

    printf("\tALBERO albero1\n");
    treeABR_func_print(&albero1); //stampa dell'albero albero1
    printf("\n\n");
    printf("\tALBERO albero2\n");
    treeABR_func_print(&albero2); //e albero2
    printf("\n\n");

    printf("Alberi pronti per il Merge\n");
    io_pressKey();  //premo invio per incominciare il Merge

    treeABR_merge(&albero1, &albero2);

    printf("\tALBERO albero1 unito\n");
    treeABR_func_print(&albero1); //stampa dell'albero albero1 unito
}


//Rotazione dell'albero con restituzione del riferimento alla nuova radice
void treeABR_func_rotate(TREE albero)  {
    int choice;
    int n_rot;
    treeABR_func_print(albero); //stampa dell'albero
    printf("\tRadice: %d\n\n", (*albero)->elem);
    printf("In quale direzione vuoi ruotare l'albero?\n\t1. Sinistra\t2. Destra\n\n");
    do  {
        printf("SCELTA: ");
        if((choice = io_getInteger()) < 1 || choice > 2)
            printf("ATTENZIONE: Valore non valido\n\n");
    }while(choice < 1 || choice > 2);

    if((choice == 1 && !((*albero)->dx)) || (choice == 2 && !((*albero)->sx))) {
        printf("ATTENZIONE: non è possibile effettuare la rotazione a ");
        if(choice == 1)
            printf("Sinistra\n\n");
        else if(choice == 2)
            printf("Destra\n\n");
    } else {
        do  {
            printf("Quante rotazioni a ");
            if(choice == 1)
                printf("Sinistra ");
            else if(choice == 2)
                printf("Destra ");
            printf("vuoi effettuare?: ");
            if((n_rot = io_getInteger()) < 1)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(n_rot < 1);
        int idx_rot;
        for(idx_rot=0;idx_rot<n_rot;idx_rot++)  {
            if(choice == 1 && (*albero)->dx) 
                treeABR_rotate_SX(albero);
            else if(choice == 2 && (*albero)->sx)  
                treeABR_rotate_DX(albero);
            else    {
                printf("ATTENZIONE: Limite albero raggiunto\n\n");
                break;
            }
            printf("\tNuova Radice: %d\n\n", (*albero)->elem);
        }
    }
}

//Bilanciamento dell'Albero
void treeABR_func_balance(TREE albero)  {


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
        treeABR_insertKey_v2(albero, random_num(1, MAX_tree));	//inserisce un numero casuale compreso fra 1 e MAX_tree
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

    treeABR_insertKey_v2(albero, val);
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