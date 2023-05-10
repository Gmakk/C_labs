#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct List
{
	struct List* next;
	struct Graph* sub;
	int weight;
}List;

typedef struct Graph
{
	int x, y, visited, sum;
	char* name;
	struct List* list;//список смежных графов
}Graph;

int D_Add(List* all);

int D_Find(List* all);

int D_Delete(List* all);

int D_Show(List* all);

int D_Timing();

int delTree(List* all);

int getInt(int* a);

int getUnsigned(unsigned int* a);

char* get_str();

int length(char* a);

int getNumber(int* a);

int ADD(List* all, List* sub, int x, int y, char* name);

int ADD_edge(Graph* sub, Graph* sub2, int weight);

int check_edge(List* all, Graph* sub, Graph* sub2);

Graph* find_with_this_name(List* all, char* name);

int delete_from_list(Graph* sub, List* target);

int delete_element(List* all, char* name);

int free_list(List* all);

int delete_mentions(List* all, Graph* gp);

int print_graph(Graph* buf);

int Write(List* all);

int Read(List* all);

int count_List(List* all);

int count_number(List* all,Graph* sub);

int source_check(List* all, Graph* sub);

int entry_count(Graph* sub);

int outputs_count(Graph* sub);

int set_sum(List* all);

int VisualizeGraph(List* all);

int viz_vertex(List* all, FILE* fn);

int viz_edge(List* all, FILE* fn);