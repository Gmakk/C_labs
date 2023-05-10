#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MaxLevel 5//100    5
#define HighStr "zzzzzzzzzzzzzzzzz"
#define LowStr "A"

typedef struct Item {
    char* key, * str;
    int level, num1, num2;
    struct Item* forvards[MaxLevel];
}Item;

typedef struct List {
    int level;
    struct Item* header;
}List;

int dialog(const char* msgs[], int N);

int D_Add(List* list);

int D_Find(List* list);

int D_Delete(List* list);

int D_Show(List* list);

int D_Timing();

int delTree(List* list);

List* new_list();

int ADD(List* list, char* key, int num1, int num2, char* str, int certain_lvl);

int DEL(List* list, char* key);

Item* find_with_this_key(List* list, char* key);

int print_Item(Item* ip);

int Write(List* list);

int Read(List* list);

Item* find_max(List* list, char* limit);

int VisualizeList(List* list);

int list_trav_vertex(List* list, FILE* fn);

int list_trav_edge(List* list, FILE* fn);

int offset();

int ADD_words(int number);

int first_occ(char* name);

char* get_str_file(FILE* fp);