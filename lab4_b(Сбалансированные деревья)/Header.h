#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define one_square_range 2//2/3
#define x_low_limit 0
#define x_high_limit 100
//#define x_high_limit 1073676289
#define y_low_limit 0
#define y_high_limit 100
//#define y_high_limit 1073676289

#define Limit 5

typedef struct Item {//информация
	int key_x, key_y, num1, num2;
	char* str;
	struct Item* next;
}Item;

typedef struct Tree//узел дерева
{
	int low_limit_x;
	int high_limit_x;
	int low_limit_y;
	int high_limit_y;
	struct Tree* sub[4];
	struct Tree* next;
	int number;//текущее количество элементво
	struct Item* item;//NULL - элементов нет
}Tree;

typedef struct Table {//информация
	Tree* mass;
	int number; //текущее количество элементов
}Table;

int dialog(const char* msgs[], int N);

int D_Add(Tree* tree);

int D_Find(Tree* tree);

int D_Delete(Tree* tree);

int D_Show(Tree* tree);

int D_Timing();

int delTree(Tree* tree);

int ADD(Tree* tree, int key_x, int key_y, int num1, int num2, char* str);

int new_tree(Tree* tree, int low_x, int high_x, int low_y, int high_y, int choice);

int select_sector(Tree* tree, int key_x, int key_y);

int add_item(Tree* tree, int key_x, int key_y, int num1, int num2, char* str, int choice);

int overflow(Tree* tree, int key_x, int key_y, int num1, int num2, char* str);

Item* find_with_this_key(Tree* tree, int key_x, int key_y, int print);

int del_item(Tree* tree, int key_x, int key_y);

int print(Tree* tree, int length);

char* get_str();

int length(char* a);

int getNumber(int* a);

int getInt(int* a);

int clean(Tree* tree);

int distance(Item* ip1, Item* ip2);

int comparison(Tree* tree, Item* comp, Item** min, int lim_x, int lim_y, int** dist);

int Read(Tree* tree);

int Write(Tree* tree);

int Write_recursion(FILE* fp, Tree* tree);

int tree_trav_vertex(Tree* tree, int x, int y, FILE* fn, int diff);

int tree_trav_edge(Tree* tree, FILE* fn);

int tree_trav_points(Tree* tree, FILE* fn);

int VisualizeTree(Tree* tree);

int VisualizePoints(Tree* tree);

int offset();

int ADD_numbers(int number);

int first_occ(int number);

int recursive_count(Tree* tree, int number, FILE* fc);