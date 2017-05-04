#include "treeABR.h"

//Inserimento del nodo nell'albero
TREE treeABR_init()	{
	TREE T = NULL;
	if(T = (struct Albero **)malloc(sizeof(struct Albero *)))	//creo la "scatola" alla radice
			*T = NULL;	//che è vuota
	else	{
		printf("[MEM] ATTENZIONE: Problema di allocazione TREE - treeABR_init\n");
		exit(1);
	}
	return T;
}

//Inserimento del nodo nell'albero
void treeABR_insertKey(TREE T, int key)	{
	if(*T)	{		//se la "scatola"" ha qualcosa al suo interno
		if(key <= (*T)->elem)	//confronto il valore 'key' con quello presente al suo interno
			treeABR_insertKey((*T)->sx, key);	//se 'key' è più piccolo, scendo a sinistra
		else if(key > (*T)->elem);
			treeABR_insertKey((*T)->dx, key);	//altrimenti, a destra
	} else		//se non c'è niente dentro la "scatola"
		*T = treeABR_creaNodo(key);	//inserisco nella "scatola" il nuovo elemento
}

//Riempimento del nodo con la stringa
TREEel treeABR_creaNodo(int key)	{
	TREEel T_new = NULL;
	if(T_new = (struct Albero *)malloc(sizeof(struct Albero)))	{	//alloco (con controllo) il contenuto da inserire nella "scatola"
		T_new->elem = key;
		if((T_new->sx = (struct Albero **)malloc(sizeof(struct Albero *))) && (T_new->dx = (struct Albero **)malloc(sizeof(struct Albero *))))	{	//creo le "scatole" per i figli sinistro e destro
			*(T_new->sx) = NULL;	//che sono vuote
			*(T_new->dx) = NULL;
		} else	{
			printf("[MEM] ATTENZIONE: Problema di allocazione TREE - treeABR_creaNodo\n");
			exit(1);
		}
	} else	{
		printf("[MEM] ATTENZIONE: Problema di allocazione TREEel - treeABR_creaNodo\n");
		exit(1);
	}
	return T_new;
}

//Eliminazione ricorsiva dei nodi in postOrder
void treeABR_delete(TREE T)	{
	if(*T)	{
		treeABR_delete((*T)->sx);
		treeABR_delete((*T)->dx);
		*T = treeABR_nodeFree(*T);
	}
}

//Eliminazione del nodo
void treeABR_deleteKey(TREE T, int key)	{
	if(*T)	{
		if(key < (*T)->elem)	//confronto dei valori con il tipo di dato dell'albero
			treeABR_deleteKey((*T)->sx, key);
		else if (key > (*T)->elem)
			treeABR_deleteKey((*T)->dx, key);
		else	{	//key == T->elem
			TREE tmp = T;
			if(tmp->sx == NULL)	//Caso I e II: zero o un figlio
				T = tmp->dx; //aggancio al figlio destro (che può essere anche NULL)
			else if(tmp->dx == NULL)
				T = tmp->sx; //aggancio al figlio sinistro
			else	{				//Caso III: due figli
				tmp = treeABR_staccaMin(T->dx, T);		//ricerca del valore minimo
                int elem_canc = T->elem;  //key temporaneo per la sostituzione col nodo da cancellare
                T->elem = tmp->elem;	//swap col valore minimo, per la corretta deallocazione dell'key e del nodo
                tmp->elem = elem_canc;
			}
			treeABR_nodeFree(tmp); //funzione di deallocazione completa del nodo isolato (key interno e nodo in sè)
		}
	} else {
		printf("Il valore inserito non è presente nell'albero\n\n");
	}
	return T;
}

//Ricerca del valore più piccolo nei sottoalberi sinistri
TREE treeABR_staccaMin(TREE T, TREE P)	{
	if(T)	{
		if(T->sx)
			return treeABR_staccaMin(T->sx, T);	//ricerca ricorsiva del valore minimo
		else	{				//arrivato al nodo minimo
			if(T == P->sx)		//aggancio il padre al figlio del nodo da sostituire per la successiva eliminazione
				P->sx = T->dx;
			else
				P->dx = T->dx;
		}
	}
	return T;
}


//Liberazione della memoria allocata dinamicamente del nodo
TREEel tree_nodeFree(TREEel T_curr)	{
	free(T_curr->sx);	//dealloco le "scatole" figlie (già vuote)
	free(T_curr->dx);
	free(T_curr);	//libero la "scatola"
	return NULL;
}

//Visita in ordine di un albero con contatore del numero dei nodi
int treeABR_inOrder(TREE T, int i)	{
	if(*T)	{
		i = treeABR_inOrder((*T)->sx, i);
		printf("%d\n", (*T)->elem);
		i++;
		i = treeABR_inOrder((*T)->dx, i);
	}
	return i;
}
