#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "Header_LIST.h"

#ifdef VECTOR

void queue_new(queue* pointer) {
    pointer->top = 0;
    for (int i = 0; i < pointer->allocated; ++i) {
        pointer->vector[i].id = -1;
        pointer->vector[i].tc = -1;
        pointer->vector[i].te = -1;
    }
}

void queue_push(queue* pointer, int id, int tc, int te) {
    /*int count = 0;
    while (pointer->vector[count].id != -1 && count < pointer->allocated-1)
        count++;
    if (pointer->vector[count].id == -1) {
        pointer->vector[pointer->top].id = id;
        pointer->vector[pointer->top].tc = tc;
        pointer->vector[pointer->top].te = te;
        pointer->top++;
    }*/
    if (pointer->allocated > pointer->top) {
        pointer->vector[pointer->top].id = id;
        pointer->vector[pointer->top].tc = tc;
        pointer->vector[pointer->top].te = te;
        pointer->top++;
    }
    else {
        printf("%s", "Queue is full!");
    }
}

process* queue_pop(queue* pointer) {
    process* ret = (process*)calloc(1, sizeof(struct process));
    if (pointer->top != 0) {
        ret->id = pointer->vector[0].id;
        ret->tc = pointer->vector[0].tc;
        ret->te = pointer->vector[0].te;
        pointer->vector[0].id = -1;
        pointer->vector[0].tc = -1;
        pointer->vector[0].te = -1;
        for (int i = 0; i < pointer->allocated-1; i++) {
            pointer->vector[i].id = pointer->vector[i + 1].id;
            pointer->vector[i].tc = pointer->vector[i + 1].tc;
            pointer->vector[i].te = pointer->vector[i + 1].te;
        }
        pointer->vector[pointer->allocated - 1].id = -1;
        pointer->vector[pointer->allocated - 1].tc = -1;
        pointer->vector[pointer->allocated - 1].te = -1;
        pointer->top -= 1;
        return ret;
    }
    else
    {
        printf("%s", "\nThe queue is empty!\n");
    }
}


void round_robin(queue* pointer, queue* pointer_buf, int time_quantum, int** table) {
    queue_init(pointer,3);
    queue_new(pointer);
    int count = 0, count_time = time_quantum;
    queue pointer_buf_search;
    queue_init(&pointer_buf_search, 20);
    queue_new(&pointer_buf_search);
    process* buffer = queue_pop(pointer_buf);//первый pop, push
    queue_push(pointer, buffer->id, buffer->tc, buffer->te);
    free(buffer);
    while (pointer->top != 0 || pointer_buf->top != 0) {
        while (pointer->vector[0].te > 0 && count_time > 0) {
            pointer->vector[0].te--;
            count_time--;
            table[pointer->vector[0].id - 1][count] = 1;
            if (pointer_buf->top != 0 && pointer->top!=pointer->allocated) {
                int count_search = 0, count_empty = pointer->allocated - pointer->top;
                process* buffer_search = NULL;
                while (pointer_buf->top != 0 && count_empty > 0) {
                    buffer_search = queue_pop(pointer_buf);
                    if (buffer_search->tc <= count && pointer->top != pointer->allocated) {
                        queue_push(pointer, buffer_search->id, buffer_search->tc, buffer_search->te);
                        free(buffer_search);
                        count_empty--;
                    }
                    else {
                        queue_push(&pointer_buf_search, buffer_search->id, buffer_search->tc, buffer_search->te);
                        free(buffer_search);
                        count_search++;
                    }
                }
                for (int i = 0; i < count_search; i++) {
                    buffer_search = queue_pop(&pointer_buf_search);
                    queue_push(pointer_buf, buffer_search->id, buffer_search->tc, buffer_search->te);
                    free(buffer_search);
                }
            }
            count++;
        }
        count_time = time_quantum;
        if (pointer->top == 0 && pointer_buf != 0) {
            buffer = queue_pop(pointer_buf);
            queue_push(pointer, buffer->id, buffer->tc, buffer->te);
            free(buffer);
        }
        if (pointer->vector->te == 0)
            free(queue_pop(pointer));
        else {
                buffer = queue_pop(pointer);
                queue_push(pointer, buffer->id, buffer->tc, buffer->te);
                free(buffer);
        }
    }
    queue_free(pointer);
    queue_free(pointer_buf);
}

void queue_free(queue* pointer) {
    free(pointer->vector);
}

void queue_init(queue* pointer,int n) {
        pointer->vector = (process*)calloc(n,sizeof(process));
    pointer->allocated = n;
}


#endif