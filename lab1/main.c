//Из входного потока вводится непрямоугольная матрица вещественных чисел [aij], i = 1, …, m, j = 1, …, n.
// Значения m и ni заранее не известны и вводятся из входного потока.
//
//Сформировать вектор, i-ый элемент которого равен количеству разных элементов в i-ой строке матрицы.
//
//Исходную матрицу и полученный вектор вывести в выходной поток с необходимыми комментариями.
#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main() {
    matrix matrix1;
    int* vector;
    printf("Enter height\n");
    getInt(&matrix1.height);
    matrix1.matr = calloc(matrix1.height,sizeof(str));
    vector = calloc(matrix1.height,sizeof(int));

    read(matrix1);

    count(matrix1,vector);

    printf("%s","Matrix:\n");
    for(int u=0;u<matrix1.height;++u){
        for(int t=0;t<matrix1.matr[u].width;++t){
            printf("%f %s",matrix1.matr[u].line[t],"  ");           //вывод матрицы
        }
        printf("%s","\n");
    }
    printf("%s","Vector:\n");
    for(int u=0;u<matrix1.height;++u){                    //вывод вектора
        printf("%d %s",vector[u]," ");
    }

    for(int i=0;i<matrix1.height;++i){
        free(matrix1.matr[i].line);
    }                                               //очистка памяти
    free(matrix1.matr);
    free(vector);
    return 0;
}
