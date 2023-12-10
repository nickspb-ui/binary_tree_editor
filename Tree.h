#pragma once

#include <iostream>
#include <vector>
#include <windows.h>


typedef struct Tree {
	int key;
	int N; // number of subtrees
	Tree* left;
	Tree* right;
};


void print_tree(Tree*, int*, int);
void add(Tree**, int);
bool del(Tree*, int, Tree*);
