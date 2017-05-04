#ifndef TREEABR_H_INCLUDED
#define TREEABR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct Albero   {
    int elem;
    struct Albero *sx;
    struct Albero *dx;
};

typedef struct Albero ** TREE;
typedef struct Albero * TREEel;

void treeABR_insertKey(TREE T, int key);
TREEel treeABR_createNode(int key);

void treeABR_delete(TREE T);

void treeABR_deleteKey(TREE T, int key);

TREEel treeABR_staccaMin(TREE T, TREE P);

void treeABR_nodeFree(TREEel T_curr);

int treeABR_inOrder(TREE T, int i);

#endif