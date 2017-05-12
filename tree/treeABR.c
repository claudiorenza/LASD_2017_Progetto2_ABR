#include "treeABR.h"

//Inserimento del nodo nell'albero, con controllo di eventuali duplicati
int treeABR_insertKey(TREE albero, int key)	{
	if(*albero)	{		//se la "scatola" ha qualcosa dentro
		if(key < (*albero)->elem)	//confronto il valore 'key' con quello presente al suo interno
			return treeABR_insertKey(&(*albero)->sx, key);	//se 'key' è più piccolo, scendo a sinistra
		else if(key > (*albero)->elem)
			return treeABR_insertKey(&(*albero)->dx, key);	//altrimenti, a destra
		else	
			return 1;	//confermo alla funzione ricorsiva che c'è un duplicato
	} else	//se non c'è niente dentro la "scatola"
		*albero = treeABR_createNode(key);
	return 0;	//niente da segnalare
}

//Inserimento del nodo nell'albero con nodi uguali, con inserimento di elementi duplicati
void treeABR_insertKey_dup(TREE albero, int key)	{
	if(*albero)	{		//se la "scatola" ha qualcosa dentro
		if(key < (*albero)->elem)	//confronto il valore 'key' con quello presente al suo interno
			treeABR_insertKey_dup(&(*albero)->sx, key);	//se 'key' è più piccolo, scendo a sinistra
		else if(key > (*albero)->elem)
			treeABR_insertKey_dup(&(*albero)->dx, key);	//altrimenti, a destra
		else	{	//se sono uguali
			if(!((*albero)->sx))	//se trovo un sottoalbero vuoto a sinistra, inserisco lì il valore duplicato
				(*albero)->sx = treeABR_createNode(key);
			else if(!((*albero)->dx))	//altrimenti a destra
				(*albero)->dx = treeABR_createNode(key);
			else	//continuo la visita all'interno del sottoalbero sinistro
				treeABR_insertKey_dup(&(*albero)->sx, key);
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
				*albero = (*albero)->dx; //metti nello "scatolo" il figlio destro (che può essere anche NULL)
			else if((*albero)->dx == NULL)
				*albero = (*albero)->sx; //metti nello "scatolo" il figlio sinistro
			else	{				//Caso III: due figli
				tmp = treeABR_staccaMin(&(*albero)->dx, albero);		//ricerca del valore minimo
                int elem_canc = (*albero)->elem;  //key temporaneo per la sostituzione col nodo da cancellare
                (*albero)->elem = tmp->elem;	//swap col valore minimo, per la corretta deallocazione dell'key e del nodo
                tmp->elem = elem_canc;
			}
			treeABR_nodeFree(tmp); //funzione di deallocazione completa del nodo isolato (key interno e nodo in sè)
		}
	} else 
		printf("Il valore inserito non è presente nell'albero\n\n");
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
		if(n_nodes_B)		//se ho stabilito un margine minimo e massimo del numero di nodi
			n_nodes_sum = n_nodes_sum + (n_nodes = random_num(n_nodes_A, n_nodes_B));	//genero un valore casuale di nodi compreso tra A e B
		else
			n_nodes = n_nodes_A;
		for(idx_nodes=0;idx_nodes<n_nodes;idx_nodes++)	//inserisco n_nodes_A nodi
			while(treeABR_insertKey(&albero, random_num(1, INT_MAX)));	//inserisce un valore casuale compreso fra 1 e INT_MAX, senza duplicati
		treeABR_postOrder_h(&albero);	//inserisco le altezze nell'albero
		h_sum = h_sum + albero->h;	//somma delle altezze degli alberi
		treeABR_delete(&albero);	//cancello l'albero per crearne uno nuovo
	}
	printf("\n\n");
	if(n_nodes_B)
		printf("Numero medio di nodi negli alberi: %.3f\n", (float)n_nodes_sum / (float)n_trees);
	printf("Altezza media degli alberi: %.3f\n\n", (float)h_sum / (float)n_trees);
}

//Unione di due alberi in maniera efficiente
void treeABR_merge(TREE albero1, TREE albero2)	{
	TREEel *albero1_arr = treeABR_merge_toArray(albero1);
	treeABR_merge_visit(albero1_arr, albero2, 0, treeABR_inOrder(albero1, 0, 0));
}

//Creazione array di appoggio ordinato con riferimenti ai nodi
TREEel *treeABR_merge_toArray(TREE albero)	{
	TREEel *albero_arr = (TREEel *)calloc(treeABR_inOrder(albero, 0, 0), sizeof(TREEel)); //allocazione array di puntatori ai nodi con conteggio (senza stampa, terzo parametro '0')
	treeABR_merge_toArray_create(albero_arr, albero, 0);	//riempimento e stampa dell'array
	return albero_arr;
}

//Assegnazione ricorsiva inOrder nell'array dei puntatori ai nodi, con restituzione del numero di nodi
int treeABR_merge_toArray_create(TREEel *albero_arr, TREE albero, int idx)	{
	if(*albero)	{
		idx = treeABR_merge_toArray_create(albero_arr, &(*albero)->sx, idx);
		albero_arr[idx] = *albero;	//inserisco il riferimento al nodo attuale in posizione idx
		return treeABR_merge_toArray_create(albero_arr, &(*albero)->dx, idx+1);
	}
	return idx;
}

/* Mettiamo a disposizione l'algoritmo per la stampa dell'array
void treeABR_merge_toArray_print(TREEel *albero_arr, int n_elem)	{
	int idx;
	printf("\tARRAY T1\n");
	for(idx=0;idx<n_elem;idx++)
		printf("[%d] %d\n", idx, albero_arr[idx]->elem);
}
*/

//Visita in T2 per il merge in T1 tramite array, senza nuova allocazione, con inserimento fra intervalli di valori
int treeABR_merge_visit(TREEel *albero1_arr, TREE albero2, int idx, int idx_limit)	{
	if(*albero2)	{
		int del = 0;
		idx = treeABR_merge_visit(albero1_arr, &(*albero2)->sx, idx, idx_limit);	//scorro T2 a sinistra aspettandomi l'indice 'idx' aggiornato
		
		//N.B.:solo durante la visita viene aggiornato e ritornato ai R.A. precedenti l'indice di visita 'idx' in T1
		//'idx' è l'indice del valore minimo dell'intervallo
		//'idx+1' è l'indice del valore massimo dell'intervallo
		while(idx+1 < idx_limit-1 && albero1_arr[idx+1]->elem < (*albero2)->elem)		//se il valore in visita in T2 è più grande del margine superiore dell'attuale intervallo nell'array
			idx++;	//passo al valore successivo nell'array di T1 fin quando qui dentro non trovo un valore più grande di T2 (ricavando un nuovo intervallo di valori)
		if((*albero2)->elem < albero1_arr[idx]->elem)	{	//questa condizione, se verificata, può avvenire solo all'inizio della visita in T2,
			albero1_arr[idx]->sx = *albero2;				//quando e se ci sono valori di T2 più piccoli del valore minimo di T1
		}else if(albero1_arr[idx]->elem < (*albero2)->elem && (*albero2)->elem < albero1_arr[idx+1]->elem)	{ //se il valore è compreso nell'intervallo
			if(!albero1_arr[idx]->dx)		//se la foglia del minimo dell'intervallo non ha un sottoalbero destro
				albero1_arr[idx]->dx = *albero2;	//inserisco il valore come foglia destra del minimo
			else if(!albero1_arr[idx+1]->sx)	//se la foglia del massimo dell'intervallo non ha un sottoalbero sinistro
				albero1_arr[idx+1]->sx = *albero2;	//inserisco il valore come foglia sinistra del massimo
			else	{
				printf("\tDEBUG: ERRORE inserimento foglia\n");
				if(albero1_arr[idx])
					printf("\t\tsu margine minore: %d", albero1_arr[idx]->dx->elem);
				if(albero1_arr[idx+1])
					printf("\t\tsu margine superiore: %d", albero1_arr[idx+1]->sx->elem);
			}
		} else if(albero1_arr[idx+1]->elem < (*albero2)->elem)	 	//questa condizione, se verificata, può avvenire solo verso la fine della visita in T2,
			albero1_arr[idx]->sx = *albero2;						//quando e se ci sono valori di T2 più grandi del valore massimo di T1
		else if(albero1_arr[idx]->elem == (*albero2)->elem || albero1_arr[idx+1]->elem == (*albero2)->elem)	{
			printf("TROVATO DUPLICATO: %d\n\n", albero1_arr[idx]->elem);
			del = 1;
		}
		TREEel albero2_destra = (*albero2)->dx; //mi salvo temporaneamente il nodo per accedere al sottoalbero destro per continuare la visita in T2
		(*albero2)->sx = NULL;	//tolgo i vecchi riferimenti ai figli in T2 ai fini dell'inserimento in T1
		(*albero2)->dx = NULL;
		
		if(!del)	//se il nuovo nodo non è un duplicato in T1
			albero1_arr[idx] = *albero2;	//aggiorno i riferimenti al valore del margine minimo per stabilire il nuovo intervallo con l'elemento appena inserito
		else		//se il nodo è un duplicato
			free(*albero2); 	//lo dealloco

		idx = treeABR_merge_visit(albero1_arr, &albero2_destra, idx, idx_limit);	//scorro inOrder l'albero T2 con l'indice del margine minimo aggiornato
	}
	return idx;
}

//Rotazione singola a sinistra
void treeABR_rotate_single_SX(TREE albero)	{
	TREEel new_root = (*albero)->dx;
	(*albero)->dx = new_root->sx;
	new_root->sx = *albero;
	(*albero)->h = treeABR_h_max(albero) + 1;
	printf("\tDEBUG ROTAZIONE SX: aggiornamento altezza root->dx %d [h: %d]\n", (*albero)->elem, (*albero)->h);												
	new_root->h = treeABR_h_max(&new_root) + 1;
	printf("\tDEBUG ROTAZIONE SX: aggiornamento altezza root %d [h: %d]\n", new_root->elem, new_root->h);													
	*albero = new_root;
}

//Rotazione singola a destra
void treeABR_rotate_single_DX(TREE albero)	{
	TREEel new_root = (*albero)->sx;
	(*albero)->sx = new_root->dx;
	new_root->dx = *albero;
	new_root->h = treeABR_h_max(&new_root) + 1;
	printf("\tDEBUG ROTAZIONE DX: aggiornamento altezza root %d [h: %d]\n", new_root->elem, new_root->h);														
	(*albero)->h = treeABR_h_max(albero) + 1;
	printf("\tDEBUG ROTAZIONE DX: aggiornamento altezza root->sx %d [h: %d]\n", (*albero)->elem, (*albero)->h);													
	*albero = new_root;
}

//Rotazione doppia a sinistra
void treeABR_rotate_double_SX(TREE albero)	{
	treeABR_rotate_single_DX(&(*albero)->sx);
	treeABR_rotate_single_SX(albero);
}

//Rotazione doppia a destra
void treeABR_rotate_double_DX(TREE albero)	{
	treeABR_rotate_single_SX(&(*albero)->dx);
	treeABR_rotate_single_DX(albero);
}


void treeABR_balance(TREE albero)	{
	if(*albero)	{
		printf("DEBUG: %d [%d]\n", (*albero)->elem, (*albero)->h);				
		printf("DEBUG: entro a sinistra\n");		
		treeABR_balance(&(*albero)->sx);
		printf("DEBUG: entro a destra\n");		
		treeABR_balance(&(*albero)->dx);
		printf("DEBUG: visita %d [%d]\n", (*albero)->elem, (*albero)->h);				
		treeABR_balance_visit(albero);
		printf("DEBUG: risalgo\n");
	}

}

void treeABR_balance_visit(TREE albero)	{
	if(treeABR_h((*albero)->sx) - treeABR_h((*albero)->dx) == 2)	{
		printf("\tDEBUG ROTAZIONE DX: APPLICABILE sx: %d - dx: %d\n", treeABR_h((*albero)->sx), treeABR_h((*albero)->dx));				
		if(treeABR_h((*albero)->sx) > treeABR_h((*albero)->dx))	{
			printf("\tDEBUG ROTAZIONE DX: singola rotazione\n");											
			treeABR_rotate_single_DX(albero);
		} else	{
			printf("\tDEBUG ROTAZIONE DX: doppia rotazione\n");								
			treeABR_rotate_double_DX(albero);
		}
	} else if(treeABR_h((*albero)->dx) - treeABR_h((*albero)->sx) == 2)	{
		printf("\tDEBUG ROTAZIONE SX: APPLICABILE sx: %d - dx: %d\n", treeABR_h((*albero)->sx), treeABR_h((*albero)->dx));		
		if(treeABR_h((*albero)->dx) > treeABR_h((*albero)->sx))	{
			printf("\tDEBUG ROTAZIONE SX: singola rotazione\n");					
			treeABR_rotate_single_SX(albero);
		} else	{
			printf("\tDEBUG ROTAZIONE SX: doppia rotazione\n");								
			treeABR_rotate_double_SX(albero);
		}
	} else	{
		(*albero)->h = treeABR_h_max(albero) + 1;	
		printf("\tDEBUG ROTAZIONE: aggiornamento altezza %d [h: %d]\n", (*albero)->elem, (*albero)->h);															
	}									
}


//Visita in ordine di un albero con restituzione del numero dei nodi, con possibile di stampa
int treeABR_inOrder(TREE albero, int idx, int print)	{
	if(*albero)	{
		idx = treeABR_inOrder(&(*albero)->sx, idx, print);
		if(print)
			printf("%d [h: %d]\n", (*albero)->elem, (*albero)->h);
		return treeABR_inOrder(&(*albero)->dx, idx+1, print);
	}
	return idx;
}

//Assegnamento delle altezze in postOrder
void treeABR_preOrder(TREE albero)	{
	if(*albero)	{
		printf("%d [h: %d]\n", (*albero)->elem, (*albero)->h);
		treeABR_preOrder(&(*albero)->sx);
		treeABR_preOrder(&(*albero)->dx);
	}
}

//Assegnamento delle altezze in postOrder
void treeABR_postOrder_h(TREE albero)	{
	if(*albero)	{
		treeABR_postOrder_h(&(*albero)->sx);
		treeABR_postOrder_h(&(*albero)->dx);
		(*albero)->h = treeABR_h_max(albero) + 1;
	}
}

//Ritorno dell'altezza del nodo
int treeABR_h(TREEel albero)	{
	if(albero)
		return albero->h;
	return -1;
}

//Ritorno del sottoalbero più alto
int treeABR_h_max(TREE albero)	{
	if(treeABR_h((*albero)->sx) > treeABR_h((*albero)->dx))	
		return treeABR_h((*albero)->sx);
	return treeABR_h((*albero)->dx); /*else if(treeABR_h((*albero)->sx) <= treeABR_h((*albero)->dx))*/
}