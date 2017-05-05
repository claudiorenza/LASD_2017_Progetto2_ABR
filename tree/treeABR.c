#include "treeABR.h"

//Inserimento del nodo nell'albero, in maniera efficiente
void treeABR_insertKey_ver2(TREE T, int key)	{
	if(*T)	{		//se la "scatola" ha qualcosa dentro
		if(key < (*T)->elem)	//confronto il valore 'key' con quello presente al suo interno
			treeABR_insertKey_ver2(&(*T)->sx, key);	//se 'key' è più piccolo, scendo a sinistra
		else if(key > (*T)->elem)
			treeABR_insertKey_ver2(&(*T)->dx, key);	//altrimenti, a destra
		else	{	//se sono uguali
			printf("DEBUG: valori uguali\n");
			if(!((*T)->sx))	//se trovo un sottoalbero vuoto a sinistra, inserisco lì il valore duplicato
				(*T)->sx = treeABR_createNode(key);
			else if(!((*T)->dx))	//altrimenti a destra
				(*T)->dx = treeABR_createNode(key);
			else	//continuo la visita all'interno del sottoalbero sinistro
				treeABR_insertKey_ver2(&(*T)->sx, key);
		}
	} else	//se non c'è niente dentro la "scatola"
		*T = treeABR_createNode(key);
}

TREEel treeABR_createNode(int key)	{
	TREEel T_new = NULL;
	if((T_new = (struct Albero *)malloc(sizeof(struct Albero))))	{	//alloco (con controllo) il contenuto da inserire nella "scatola"
		T_new->elem = key;
		T_new->sx = NULL;	//che sono vuote
		T_new->dx = NULL;
	} else	{
		printf("[MEM] ATTENZIONE: Problema di allocazione TREEel - treeABR_creaNodo\n");
		exit(1);
	}
	return T_new;
}

//Eliminazione ricorsiva dei nodi in postOrder
void treeABR_delete(TREE T)	{
	if(*T)	{
		treeABR_delete(&(*T)->sx);
		treeABR_delete(&(*T)->dx);
		treeABR_nodeFree(*T);
		*T = NULL;
	}
}

//Eliminazione del nodo
void treeABR_deleteKey(TREE T, int key)	{
	if(*T)	{
		if(key < (*T)->elem)	//confronto dei valori con il tipo di dato dell'albero
			treeABR_deleteKey(&(*T)->sx, key);
		else if (key > (*T)->elem)
			treeABR_deleteKey(&(*T)->dx, key);
		else	{	//key == (*T)->elem
			TREEel tmp = *T;
			if((*T)->sx == NULL)	//Caso I e II: zero o un figlio
				*T = (*T)->dx; //aggancio al figlio destro (che può essere anche NULL)
			else if((*T)->dx == NULL)
				*T = (*T)->sx; //aggancio al figlio sinistro
			else	{				//Caso III: due figli
				tmp = treeABR_staccaMin(&(*T)->dx, T);		//ricerca del valore minimo
                int elem_canc = (*T)->elem;  //key temporaneo per la sostituzione col nodo da cancellare
                (*T)->elem = tmp->elem;	//swap col valore minimo, per la corretta deallocazione dell'key e del nodo
                tmp->elem = elem_canc;
			}
			treeABR_nodeFree(tmp); //funzione di deallocazione completa del nodo isolato (key interno e nodo in sè)
		}
	} else {
		printf("Il valore inserito non è presente nell'albero\n\n");
	}
}

//Ricerca del valore più piccolo nei sottoalberi sinistri
TREEel treeABR_staccaMin(TREE T, TREE P)	{
	TREEel min = NULL;
	if(*T)	{
		if((*T)->sx)
			return treeABR_staccaMin(&(*T)->sx, T);	//ricerca ricorsiva del valore minimo
		else	{				//arrivato al nodo minimo
			min = *T;
			if(T == &(*P)->sx)		//aggancio il padre al figlio del nodo da sostituire per la successiva eliminazione
				(*P)->sx = (*T)->dx;
			else
				(*P)->dx = (*T)->dx;
		}
	}
	return min;
}


//Liberazione della memoria allocata dinamicamente del nodo
void treeABR_nodeFree(TREEel T_curr)	{
	T_curr->sx = NULL;
	T_curr->dx = NULL;
	free(T_curr);	//libero la "scatola"
}

//Visita in ordine di un albero con contatore del numero dei nodi
int treeABR_inOrder(TREE T, int i)	{
	if(*T)	{
		i = treeABR_inOrder(&(*T)->sx, i);
		printf("%d\n", (*T)->elem);
		i++;
		return treeABR_inOrder(&(*T)->dx, i);
	}
	return i;
}

int treeABR_postOrder_h(TREE T, int h_local)	{
	if(*T)	{
		int h_sx = treeABR_postOrder_h(&(*T)->sx, h_local+1);
		int h_dx = treeABR_postOrder_h(&(*T)->dx, h_local+1);
		if(h_sx > h_dx)
			return h_sx;
		else
			return h_dx;
	}
	return h_local-1;
}