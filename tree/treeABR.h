#ifndef TREEABR_H_INCLUDED
#define TREEABR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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


void treeABR_insertKey_v1(TREE albero, int key);
void treeABR_insertKey_v2(TREE albero, int key);
TREEel treeABR_createNode(int key);

void treeABR_delete(TREE albero);

void treeABR_deleteKey(TREE albero, int key);

TREEel treeABR_staccaMin(TREE albero, TREE P);

void treeABR_nodeFree(TREEel albero_curr);

void treeABR_average(int n_trees, int n_nodes_A, int n_nodes_B);

void treeABR_merge(TREE albero1, TREE albero2);
void treeABR_insertKey_merge(TREE albero, TREEel node);

void treeABR_rotate_SX(TREE albero);
void treeABR_rotate_DX(TREE albero);

int treeABR_inOrder(TREE albero, int i);

void treeABR_postOrder_h(TREE albero);
int treeABR_h_max(TREE albero);

#endif