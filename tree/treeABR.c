#include "treeABR.h"

//Inserimento del nodo nell'albero, in maniera efficiente
void treeABR_insertKey_v2(TREE albero, int key)	{
	if(*albero)	{		//se la "scatola" ha qualcosa dentro
		if(key < (*albero)->elem)	//confronto il valore 'key' con quello presente al suo interno
			treeABR_insertKey_v2(&(*albero)->sx, key);	//se 'key' è più piccolo, scendo a sinistra
		else if(key > (*albero)->elem)
			treeABR_insertKey_v2(&(*albero)->dx, key);	//altrimenti, a destra
		else	{	//se sono uguali
			//printf("DEBUG: valori uguali\n");
			if(!((*albero)->sx))	//se trovo un sottoalbero vuoto a sinistra, inserisco lì il valore duplicato
				(*albero)->sx = treeABR_createNode(key);
			else if(!((*albero)->dx))	//altrimenti a destra
				(*albero)->dx = treeABR_createNode(key);
			else	//continuo la visita all'interno del sottoalbero sinistro
				treeABR_insertKey_v2(&(*albero)->sx, key);
		}
	} else	//se non c'è niente dentro la "scatola"
		*albero = treeABR_createNode(key);
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
void treeABR_delete(TREE albero)	{
	if(*albero)	{
		treeABR_delete(&(*albero)->sx);
		treeABR_delete(&(*albero)->dx);
		treeABR_nodeFree(*albero);
		*albero = NULL;
	}
}

//Eliminazione del nodo
void treeABR_deleteKey(TREE albero, int key)	{
	if(*albero)	{
		if(key < (*albero)->elem)	//confronto dei valori con il tipo di dato dell'albero
			treeABR_deleteKey(&(*albero)->sx, key);
		else if (key > (*albero)->elem)
			treeABR_deleteKey(&(*albero)->dx, key);
		else	{	//key == (*albero)->elem
			TREEel tmp = *albero;
			if((*albero)->sx == NULL)	//Caso I e II: zero o un figlio
				*albero = (*albero)->dx; //aggancio al figlio destro (che può essere anche NULL)
			else if((*albero)->dx == NULL)
				*albero = (*albero)->sx; //aggancio al figlio sinistro
			else	{				//Caso III: due figli
				tmp = treeABR_staccaMin(&(*albero)->dx, albero);		//ricerca del valore minimo
                int elem_canc = (*albero)->elem;  //key temporaneo per la sostituzione col nodo da cancellare
                (*albero)->elem = tmp->elem;	//swap col valore minimo, per la corretta deallocazione dell'key e del nodo
                tmp->elem = elem_canc;
			}
			treeABR_nodeFree(tmp); //funzione di deallocazione completa del nodo isolato (key interno e nodo in sè)
		}
	} else {
		printf("Il valore inserito non è presente nell'albero\n\n");
	}
}

//Ricerca del valore più piccolo nei sottoalberi sinistri
TREEel treeABR_staccaMin(TREE albero, TREE P)	{
	TREEel min = NULL;
	if(*albero)	{
		if((*albero)->sx)
			return treeABR_staccaMin(&(*albero)->sx, albero);	//ricerca ricorsiva del valore minimo
		else	{				//arrivato al nodo minimo
			min = *albero;
			if(albero == &(*P)->sx)		//aggancio il padre al figlio del nodo da sostituire per la successiva eliminazione
				(*P)->sx = (*albero)->dx;
			else
				(*P)->dx = (*albero)->dx;
		}
	}
	return min;
}


//Liberazione della memoria allocata dinamicamente del nodo
void treeABR_nodeFree(TREEel albero_curr)	{
	albero_curr->sx = NULL;
	albero_curr->dx = NULL;
	free(albero_curr);	//libero la "scatola"
}


//Calcolo altezza media per alberi molteplici
void treeABR_average(int n_trees, int n_nodes_A, int n_nodes_B)	{
	int idx_trees, idx_nodes, h_sum = 0, n_nodes, n_nodes_sum = 0;
	TREEel albero = NULL;
	for(idx_trees=0;idx_trees<n_trees;idx_trees++)	{	//ciclo per il numero di alberi
		if(n_nodes_B)		//se ho stabilito un margine massimo del numero di nodi
			n_nodes_sum = n_nodes_sum + (n_nodes = random_num(n_nodes_A, n_nodes_B));	//genero un valore casuale di nodi compreso tra A e B
		else
			n_nodes = n_nodes_A;
		for(idx_nodes=0;idx_nodes<n_nodes;idx_nodes++)	//inserisco n_nodes_A nodi
			treeABR_insertKey_v2(&albero, random_num(1, n_nodes_A));	//inserisce un valore casuale compreso fra 1 e n_nodes_A
		//IMPORTANTE: è possibile calcolare l'altezza massima ogni volta che si inserice un nuovo nodo nell'albero,
		//risparmiando una nuova visita di tutti i nodi (O(n))
		h_sum = h_sum + treeABR_postOrder_h(&albero, 0);
		treeABR_delete(&albero);
	}
	printf("\n\n");
	if(n_nodes_B)
		printf("Numero medio di nodi negli alberi: %.3f\n", (float)n_nodes_sum / (float)n_trees);
	printf("Altezza media degli alberi: %.3f\n\n", (float)h_sum / (float)n_trees);
}

//Unione di due alberi
void treeABR_merge(TREE albero1, TREE albero2)	{
	if(*albero2)	{
		treeABR_merge(albero1, &(*albero2)->sx);
		treeABR_merge(albero1, &(*albero2)->dx);	//scorro in postOrder l'albero per visitare le foglie e mai i nodi interni per trasferire i nodi e non sottoalberi

		(*albero2)->sx = NULL;	//tolgo i vecchi riferimenti ai figli
		(*albero2)->dx = NULL;
		treeABR_insertKey_merge(albero1, *albero2);	//inserisce il nodo partendo dalla radice di albero1
	}
}


//Inserimento del nodo nell'albero per il merge, senza nuova allocazione
void treeABR_insertKey_merge(TREE albero, TREEel node)	{
	if(*albero)	{		//se la "scatola" ha qualcosa dentro
		if(node->elem < (*albero)->elem)	//confronto il valore 'node' con quello presente al suo interno
			treeABR_insertKey_merge(&(*albero)->sx, node);	//se 'node' è più piccolo, scendo a sinistra
		else if(node->elem > (*albero)->elem)
			treeABR_insertKey_merge(&(*albero)->dx, node);	//altrimenti, a destra
		else	{	//se sono uguali
			if(!((*albero)->sx))	//se trovo un sottoalbero vuoto a sinistra, inserisco lì il valore duplicato
				(*albero)->sx = node;
			else if(!((*albero)->dx))	//altrimenti a destra
				(*albero)->dx = node;
			else	//continuo la visita all'interno del sottoalbero sinistro
				treeABR_insertKey_merge(&(*albero)->sx, node);
		}
	} else		//se non c'è niente dentro la "scatola"
		*albero = node;
}


//Rotazione a sinistra
void treeABR_rotate_SX(TREE albero)	{
	TREEel new_root = (*albero)->dx;
	(*albero)->dx = new_root->sx;
	new_root->sx = *albero;
	*albero = new_root;
}

//Rotazione a destra
void treeABR_rotate_DX(TREE albero)	{
	TREEel new_root = (*albero)->sx;
	(*albero)->sx = new_root->dx;
	new_root->dx = *albero;
	*albero = new_root;
}


//Visita in ordine di un albero con contatore del numero dei nodi
int treeABR_inOrder(TREE albero, int i)	{
	if(*albero)	{
		i = treeABR_inOrder(&(*albero)->sx, i);
		printf("%d\n", (*albero)->elem);
		i++;
		return treeABR_inOrder(&(*albero)->dx, i);
	}
	return i;
}

int treeABR_postOrder_h(TREE albero, int h_local)	{
	if(*albero)	{
		int h_sx = treeABR_postOrder_h(&(*albero)->sx, h_local+1);
		int h_dx = treeABR_postOrder_h(&(*albero)->dx, h_local+1);
		if(h_sx > h_dx)
			return h_sx;
		else
			return h_dx;
	}
	return h_local-1;
}