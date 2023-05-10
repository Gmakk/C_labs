#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Info {//информация
	int num1, num2;
	char* str;
}Info;

typedef struct Tree
{
	unsigned int key;
	Info* info;
	struct Tree* left;
	int left_flag;//   1 - Есть дочерний элемент; 0 - нет
	struct Tree* right;
	int right_flag;//   1 - Есть дочерний элемент; 0 - нет
}Tree;

int D_Add(Tree* tree);

int D_Find(Tree* tree);

int D_Delete(Tree* tree);

int D_Show(Tree* tree);

int D_Timing(Tree* tp);

int getInt(int* a);

int getUnsigned(unsigned int* a);

char* get_str();

int length(char* a);

int getNumber(int* a);

void find(Tree* tp, unsigned int key);

Tree* get_min(Tree* tp);

void del_leaf(Tree* par, Tree* tp);

void del_1sub(Tree* par, Tree* tp);

void del_2sub(Tree* par, Tree* tp);

int print(Tree* tree, int length);

int print_list(Tree* tree, int size);

void free_element(Tree* tree);

void decimal(Tree* tree, int size);

int number_digits(unsigned int n);

int print_with_this_key(Tree* tp, unsigned int key, int check);

void ADD(Tree* tree, unsigned int key, int num1, int num2, char* str);

void set_parent(Tree* tp, Tree* parent);

int VisualizeTree(Tree* tree);

int tree_trav_vertex(Tree* tree, int x, int y, FILE* fn, int diff);

int tree_trav_edge(Tree* tree, FILE* fn);

int Counting();

int recursive_count(Tree* tree, FILE* fc);

int ADD_numbers(int number);

int count_numbers();