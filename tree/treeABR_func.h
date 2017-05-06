#ifndef TREEABR_FUNC_H_INCLUDED
#define TREEABR_FUNC_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include "../io/io.h"
#include "../io/random.h"
#include "treeABR.h"

typedef struct Albero ** TREE;

void treeABR_func_main();

int treeABR_func_menu(TREE albero);

void treeABR_func_average();

void treeABR_func_generate(TREE albero);

void treeABR_func_insertKey(TREE albero);

void treeABR_func_deleteKey(TREE albero);

void treeABR_func_delete(TREE albero);

void treeABR_func_print(TREE albero);


#endif