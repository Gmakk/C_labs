#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

char* get_str() {
    char buf[81] = { 0 };
    char* res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf_s("%80[^\n]", buf, 80);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else {
            scanf_s("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

int number_check(char* symbol) {
    int ret = 0;
    if (symbol != NULL) {
        if (*symbol < 48 || *symbol>57)
            ret = -1;
        if ((int)(*symbol) < 0)
            ret = -1;
    }
    return ret;
}

void table_fill(int** table, int height, int width) {   //заполнение таблицы 0
    for (int g = 0; g < height; ++g) {
        for (int i = 0; i < width; ++i) {
            table[g][i] = 0;
        }
    }
}

int getInt(int* a) {
    int n = 0;
    while (n == 0) {
        n = scanf_s("%d", a);
        if (n < 0)
            return n;
        if (n == 0) {
            scanf_s("%*c", NULL);
            printf("%s", "Enter correct number\n");
        }
    }
    return n;
}

int getNumber(int* a) {           //ввод числа
    int n = getInt(a);
    while (*a < 0) {
        printf("%s", "Enter correct number\n");
        n = getInt(a);
    }
    return n;
}

result* input(queue* queue) {
    queue_init(queue,20);
    queue_new(queue);
    result* ret = (result*)malloc(sizeof(result));
    char* str = get_str();
    str = get_str();
    char sep[2] = " /";
    char* istr = NULL;
    char** next_token;
    int count = 0, width = 0, id = 0, tc = 0, te = 0, check = 0;
    if (strlen(str) >= 5)
    {
        //id
        istr = strtok_s(str, sep, &next_token);
        if (number_check(istr) == -1)
            check = -1;
        id += (int)(*istr) - 48;
        if (strlen(istr) > 1) {
            id *= 10;
            id += (int)(*(istr + 1)) - 48;
        }
        //tc
        istr = strtok_s(NULL, sep, &next_token);
        if (number_check(istr) == -1)
            check = -1;
        tc += (int)(*istr) - 48;
        if (strlen(istr) > 1) {
            tc *= 10;
            te += (int)(*(istr + 1)) - 48;
        }
        if (tc != 0)
            check = -1;
        //te
        istr = strtok_s(NULL, sep, &next_token);
        if (number_check(istr) == -1)
            check = -1;
        te += (int)(*istr) - 48;
        if (strlen(istr) > 1) {
            te *= 10;
            te += (int)(*(istr + 1)) - 48;
        }
        //push;
        if (check == 0) {
            queue_push(queue, id, tc, te);
            width += te;
            count++;
        }
        else
            printf("%s", "Incorrect input\n");
        istr = strtok_s(NULL, sep, &next_token);
        if (number_check(istr) == -1)
            check = -1;
        if (check == -1)
            printf("%s", "Incorrect input\n");
        id = 0;
        tc = 0;
        te = 0;
    }
    if (strlen(str) - 5 >= 5 && check == 0) {
        while (istr != NULL && check == 0)
        {
            //id
            id += (int)(*istr) - 48;
            if (strlen(istr) > 1) {
                id *= 10;
                id += (int)(*(istr + 1)) - 48;
            }
            //tc
            istr = strtok_s(NULL, sep, &next_token);
            if (number_check(istr) == -1)
                check = -1;
            tc += (int)(*istr) - 48;
            if (strlen(istr) > 1) {
                tc *= 10;
                te += (int)(*(istr + 1)) - 48;
            }
            //te
            istr = strtok_s(NULL, sep, &next_token);
            if (number_check(istr) == -1)
                check = -1;
            te += (int)(*istr) - 48;
            if (strlen(istr) > 1) {
                te *= 10;
                te += (int)(*(istr + 1)) - 48;
            }
            //push;
            if (check == 0) {
                queue_push(queue, id, tc, te);
                width += te;
                count++;
            }
            else {
                printf("%s", "Incorrect input\n");
                break;
            }
            istr = strtok_s(NULL, sep, &next_token);
            if (number_check(istr) == -1) {
                check = -1;
                printf("%s", "Incorrect input\n");
                break;
            }
            id = 0;
            tc = 0;
            te = 0;
        }
    }
    ret->height = count;
    ret->width = width;
    free(str);
    if (check != 0) {
        ret->height = -1;
        ret->width = -1;
    }
    return ret;
}

void table_print(int** table, int height, int width) {   //итоговый вывод
    for (int g = 0; g < height; ++g) {
        printf("%d", g + 1);
        if ((g + 1) <= 9)
            printf("%s", " ");
        for (int i = 0; i < width; ++i) {
            if (table[g][i] == 1)
                printf("%c %s", '*', " ");
            else
                printf("%s", "   ");
            if (i > 9)
                printf("%s", " ");
        }
        printf("%s", "\n");
    }
}