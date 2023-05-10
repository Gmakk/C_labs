#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Length_1 5
#define Length_2 5

typedef struct FilePlace {//информация
    int length, offset;
}FilePlace;

typedef struct InfoType {//информация
    int num1, num2;
    char* str;
    int lenght;
}InfoType;

typedef struct Item {
    //InfoType* info;// указатель на информацию
    int release;// версия элемента
    struct Item* next;// указатель на следующий элемент с данным составным ключем
    FilePlace place;
    int key1;	// ключ элемента из 1-го пространства ключей;
    char* key2;	// ключ элемента из 2-го пространства ключей;
}Item;

typedef struct KeySpace1 {
    int key;			    // ключ элемента, не может быть 0
    int par;			// ключ родительского элемента
    Item* item;			// указатель на информацию
}KeySpace1;

typedef struct KeySpace2 {
    int busy;		// признак занятости элемента
    char* key;		// ключ элемента     //a string with variable length (null-terminated)
    int release;	// номер версии элемента
    Item* item;	// указатель на информацию
}KeySpace2;

typedef struct Table {
    KeySpace1* ks1;		// указатель на первое пространство ключей
    KeySpace2* ks2;		// указатель на второе пространство ключей

    int msize1;     // размер области 1-го пространства ключей
    int msize2;     // размер области 2-го пространства ключей

    int number;
}Table;

int getInt(int* a);

char* get_str();

int dialog(const char* msgs[], int N);

int find1(Table* ptab, int key);

int find2(Table* ptab, char* key);

int hash1(char* c);

int hash2(int* i);

void sort_ks1(Table* ptab);

int D_Add(Table* ptab);

int D_Find(Table* ptab);

int D_Delete(Table* ptab);

int D_Show(Table* ptab);

void delTable(Table* ptab);

void list_print(Item* ptr, int par);

void add_first(Table* ptab, int key1, char* key2, int num1, int num2, char* str);

void add_following(Table* ptab, int key1, char* key2, int par, int num1, int num2, char* str);

void correct_par_key(Table* ptab, int key1);

void free_list(Item* ptr);

void delete_from_key_spc(Table* ptab, int par, int result1, int result2);

void delete_certain(Table* ptab, int result1, int result2, int rel);

void delete_Item(Item* ptr);

void binary_search(Table* ptab, int par);