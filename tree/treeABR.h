#ifndef TREEABR_H_INCLUDED
#define TREEABR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../io/io.h"
#include "../io/random.h"

#define MAX_tree 256

struct Albero   {
    int elem;
    struct Albero *sx;
    struct Albero *dx;
};

typedef struct Albero ** TREE;
typedef struct Albero * TREEel;

void treeABR_insertKey_v2(TREE T, int key);
TREEel treeABR_createNode(int key);

void treeABR_delete(TREE T);

void treeABR_deleteKey(TREE T, int key);

TREEel treeABR_staccaMin(TREE T, TREE P);

void treeABR_nodeFree(TREEel T_curr);

void treeABR_calcAverage(int n_trees, int n_nodes_A, int n_nodes_B);

int treeABR_inOrder(TREE T, int i);

int treeABR_postOrder_h(TREE T, int h_local);

#endif