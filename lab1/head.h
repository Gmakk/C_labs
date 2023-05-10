#ifndef LAB1_HEAD_H
#define LAB1_HEAD_H

typedef struct {    //строка
    int width,sum;
    float * line;
}str;

typedef struct {  //матрица
    int height;
    str * matr;
}matrix;

int getInt(int *a) {
    int n = 0;
    while (n == 0) {
        n = scanf("%d", a);
        if (n < 0)
            return n;
        if (n == 0) {
            scanf("%*c", NULL);
            printf("%s","Enter correct number\n");
        }
    }
    return 1;
}

int getFloat(float *a) {
    int n = 0;
    while (n == 0) {
        n = scanf("%f", a);
        if (n < 0)
            return n;
        if (n == 0) {
            scanf("%*c", NULL);
            printf("%s","Enter correct number\n");
        }
    }
    return 1;
}

void read(matrix matrix1){
    for(int i=0;i<matrix1.height;++i){
        printf("%s %d %s","Enter length of",i+1,"line\n");                                      //ввод и выделение памяти
        getInt(&matrix1.matr[i].width);
        matrix1.matr[i].line=calloc(matrix1.matr[i].width,sizeof(float));
        if(matrix1.matr[i].width!=0)
            printf("%s","Enter numbers\n");
        for(int g=0;g<matrix1.matr[i].width;++g) {
            getFloat(&matrix1.matr[i].line[g]);
        }
        printf("%s","\n");
    }
}

void count(matrix matrix1, int * vector){
    float * ptr1;
    float * ptr2;
    int check=0;
    for(int u=0;u<matrix1.height;++u){
        ptr1=&matrix1.matr[u].line[0];          //ставим указатель на первый элемент
        ptr2=&matrix1.matr[u].line[0];
        for(int t=0;t<matrix1.matr[u].width;t++){
            for(int r=0;r<matrix1.matr[u].width;r++){
                if(r!=t && *ptr2==*ptr1){   //подсчет различных элементов                 //  ptr1!=ptr2 &&                   matrix1.matr[u].line[t]==matrix1.matr[u].line[r]
                    check=1;
                    break;
                }
                ptr2++;
            }
            ptr2=&matrix1.matr[u].line[0];

            ptr1++;
            if(check==0)
                matrix1.matr[u].sum++;
            check=0;
        }
        vector[u]=matrix1.matr[u].sum;
    }
}
#endif
