#ifndef TREEABR_H_INCLUDED
#define TREEABR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../io/io.h"
#include "../io/random.h"

#define MAX_tree 256

struct Albero   {
    int elem;
    int h;
    struct Albero *sx;
    struct Albero *dx;
};

typedef struct Albero ** TREE;
typedef struct Albero * TREEel;


int treeABR_insertKey(TREE albero, int key);
void treeABR_insertKey_dup(TREE albero, int key);
TREEel treeABR_createNode(int key);

void treeABR_delete(TREE albero);

void treeABR_deleteKey(TREE albero, int key);

TREEel treeABR_staccaMin(TREE albero, TREE P);

void treeABR_nodeFree(TREEel albero_curr);

void treeABR_average(int n_trees, int n_nodes_A, int n_nodes_B);

void treeABR_merge(TREE albero1, TREE albero2);
TREE *treeABR_merge_toArray(TREE albero);
int treeABR_merge_toArray_create(TREE *albero_arr, TREE albero, int idx);
void treeABR_merge_toArray_print(TREE *albero_arr, int n_elem);
int treeABR_merge_visit(TREE *albero1_arr, TREE albero2, int idx);

void treeABR_rotate_SX(TREE albero);
void treeABR_rotate_DX(TREE albero);

int treeABR_inOrder(TREE albero, int i, int print);

void treeABR_postOrder_h(TREE albero);
int treeABR_h_max(TREE albero);

#endif