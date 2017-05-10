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
	TREE *albero1_arr = treeABR_merge_toArray(albero1);
	treeABR_merge_visit(albero1_arr, albero2, 0);
}

//Creazione array di appoggio ordinato con riferimenti ai nodi
TREE *treeABR_merge_toArray(TREE albero)	{
	TREE *albero_arr = (TREE *)calloc(treeABR_inOrder(albero, 0, 0), sizeof(TREE)); //allocazione array di puntatori ai nodi con conteggio (senza stampa, terzo parametro '0')
	treeABR_merge_toArray_print(albero_arr, treeABR_merge_toArray_create(albero_arr, albero, 0));	//riempimento e stampa dell'array
	return albero_arr;
}

//Assegnazione ricorsiva inOrder nell'array dei puntatori ai nodi, con restituzione del numero di nodi
int treeABR_merge_toArray_create(TREE *albero_arr, TREE albero, int idx)	{
	if(*albero)	{
		idx = treeABR_merge_toArray_create(albero_arr, &(*albero)->sx, idx);
		albero_arr[idx] = albero;	//inserisco il riferimento al nodo attuale in posizione idx
		return treeABR_merge_toArray_create(albero_arr, &(*albero)->dx, idx+1);
	}
	return idx;
}

void treeABR_merge_toArray_print(TREE *albero_arr, int n_elem)	{
	int idx;
	printf("\tARRAY T1\n");
	for(idx=0;idx<n_elem;idx++)
		printf("[%d] %d\n", idx, (*albero_arr[idx])->elem);
}

//Visita in T2 per il merge in T1 tramite array, senza nuova allocazione, con inserimento fra intervalli di valori
int treeABR_merge_visit(TREE *albero1_arr, TREE albero2, int idx)	{
	if(*albero2)	{
		int del = 0;
		printf("DEBUG: visita a sinistra\n\n");
		idx = treeABR_merge_visit(albero1_arr, &(*albero2)->sx, idx);	//scorro T2 a sinistra aspettandomi l'indice 'idx' aggiornato
		
		printf("DEBUG: Elemento attuale: %d\n", (*albero2)->elem);
		//N.B.:solo durante la visita viene aggiornato e ritornato ai R.A. precedenti l'indice di visita 'idx' in T1
		//'idx' è l'indice del valore minimo dell'intervallo
		//'idx+1' è l'indice del valore massimo dell'intervallo
		printf("DEBUG VISITA: intervallo attuale [%d]-[%d] = %d - %d\n", idx, idx+1, (*albero1_arr[idx])->elem, (*albero1_arr[idx+1])->elem);
		while(albero1_arr[idx+1] && (*albero1_arr[idx+1])->elem < (*albero2)->elem)	{	//se il valore in visita in T2 è più grande del margine superiore dell'attuale intervallo nell'array
			idx++;	//passo al valore successivo nell'array di T1 fin quando qui dentro non trovo un valore più grande di T2 (ricavando un nuovo intervallo di valori)
			printf("DEBUG i: %d\n", idx);
		}
		printf("DEBUG: indici nuovi[%d]-[%d] = ", idx, idx+1);
		printf("%d - %d\n\n", (*albero1_arr[idx])->elem, (*albero1_arr[idx+1])->elem);
		
		if(!(*albero1_arr[idx+1]))
			printf("\tDEBUG: raggiunto indice massimo\n\n");

		printf("DEBUG: salvataggio sottoalbero destro\n");
		TREEel albero2_destra = (*albero2)->dx; //mi salvo temporaneamente il nodo per accedere al sottoalbero destro per continuare la visita in T2
		printf("\tDEBUG: SALVATO\n");
		if(!albero2_destra)
			printf("DEBUG: Prima ELEMENTO A DESTRA NON PRESENTE\n");
		(*albero2)->sx = NULL;	//tolgo i vecchi riferimenti ai figli in T2 ai fini dell'inserimento in T1
		(*albero2)->dx = NULL;
		if(!albero2_destra)
			printf("DEBUG: Dopo ELEMENTO A DESTRA NON PRESENTE\n");
		printf("DEBUG: riferimenti annullati\n");
		printf("DEBUG: prepare to merge %d in %d-%d\n", (*albero2)->elem, (*albero1_arr[idx])->elem, (*albero1_arr[idx+1])->elem);
		if((*albero2)->elem < (*albero1_arr[idx])->elem)	{	//questa condizione, se verificata, può avvenire solo all'inizio della visita in T2,
			printf("DEBUG: valore più piccolo dell'intervallo\n");
			(*albero1_arr[idx])->sx = *albero2;				//quando e se ci sono valori di T2 più piccoli del valore minimo di T1
		}else if((*albero1_arr[idx])->elem < (*albero2)->elem && (*albero2)->elem < (*albero1_arr[idx+1])->elem)	{ //se il valore è compreso nell'intervallo
			printf("DEBUG: valore compreso nell'intervallo\n");
			if(!(*albero1_arr[idx])->dx)	{	//se la foglia del minimo dell'intervallo non ha un sottoalbero destro
				printf("\tDEBUG: salvato al margine minimo a destra\n");
				(*albero1_arr[idx])->dx = *albero2;	//inserisco il valore come foglia destra del minimo
			} else if(!(*albero1_arr[idx+1])->sx)	{//se la foglia del massimo dell'intervallo non ha un sottoalbero sinistro
				printf("\tDEBUG: salvato al margine massimo a sinistra\n");				
				(*albero1_arr[idx+1])->sx = *albero2;	//inserisco il valore come foglia sinistra del massimo
			} else	{
				printf("\tDEBUG: ERRORE inserimento foglia\n");
				if(albero1_arr[idx])
					printf("\t\tsu margine minore: %d", (*albero1_arr[idx])->dx->elem);
				if(albero1_arr[idx+1])
					printf("\t\tsu margine superiore: %d", (*albero1_arr[idx+1])->sx->elem);
			}
		} else if((*albero1_arr[idx+1])->elem < (*albero2)->elem)	{ 	//questa condizione, se verificata, può avvenire solo verso la fine della visita in T2,
			printf("DEBUG: valore più grande dell'intervallo\n");		
			(*albero1_arr[idx])->sx = *albero2;						//quando e se ci sono valori di T2 più grandi del valore massimo di T1
		}else if((*albero1_arr[idx])->elem == (*albero2)->elem || (*albero1_arr[idx+1])->elem == (*albero2)->elem)	{
			printf("DEBUG: DUPLICATO\n");
			del = 1;
		}

		if(!del)	//se il nuovo nodo non è un duplicato in T1
			albero1_arr[idx] = albero2;	//aggiorno i riferimenti al valore del margine minimo per stabilire il nuovo intervallo con l'elemento appena inserito
		printf("DEBUG: visita a destra\n\n");
		idx = treeABR_merge_visit(albero1_arr, &albero2_destra, idx);	//scorro inOrder l'albero T2 con l'indice del margine minimo aggiornato
		printf("DEBUG: fine visita %d\n\n", (*albero2)->elem);
		

		if(del)	{//se il nodo è un duplicato
			free(*albero2); 	//lo dealloco
			printf("DEBUG: deallocato duplicato\n");			
		}//treeABR_merge_insertKey(albero1, *albero2);	//inserisce il nodo partendo dalla radice di albero1
	}
	return idx;
}
	
/*	
void treeABR_merge_insertKey(TREE albero1, TREEel node2)	{
	if(*albero1)	{		//se la "scatola" ha qualcosa dentro
		if(node2->elem < (*albero1)->elem)	//confronto il valore 'node2' con quello presente al suo interno
			treeABR_merge_insertKey(&(*albero1)->sx, node2);	//se 'node2' è più piccolo, scendo a sinistra
		else if(node2->elem > (*albero1)->elem)
			treeABR_merge_insertKey(&(*albero1)->dx, node2);	//altrimenti, a destra
		else		//se sono uguali
			free(node2);
	} else		//se non c'è niente dentro la "scatola"
		*albero1 = node2;
}
*/

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
void treeABR_postOrder_h(TREE albero)	{
	if(*albero)	{
		treeABR_postOrder_h(&(*albero)->sx);
		treeABR_postOrder_h(&(*albero)->dx);
		(*albero)->h = treeABR_h_max(albero) + 1;
	}
}

int treeABR_h_max(TREE albero)	{
	if(((*albero)->sx && !(*albero)->dx) || (((*albero)->sx && (*albero)->dx) && ((*albero)->sx->h > (*albero)->dx->h)))
		return (*albero)->sx->h;
	else if((!(*albero)->sx && (*albero)->dx) || (((*albero)->sx && (*albero)->dx) && ((*albero)->sx->h <= (*albero)->dx->h)))
		return (*albero)->dx->h;
	else
		return -1;
}