#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "Header_LIST.h"


#ifdef LIST

void queue_new(queue* pointer) {
    pointer->pointer = NULL;
}

void queue_push(queue* pointer, int id, int tc, int te) {     //���������� ��������
    process* new = (process*)malloc(sizeof(process));
    new->te = te;
    new->tc = tc;
    new->id = id;
    if (pointer->pointer == NULL) {//������ �������
        pointer->pointer = new;
        new->next = new;
    }
    else {   //�� ������ �������
        process* ptr = pointer->pointer;
        while (ptr->next != pointer->pointer) {
            ptr = ptr->next;
        }
        ptr->next = new;
        new->next = pointer->pointer;
    }
}

process* queue_pop(queue* que) {
    process* ptr = que->pointer;
    process* ret = (process*)calloc(1, sizeof(struct process));
    if (que->pointer == NULL) {//������ �������
        printf("%s", "Queue is empty!\n");
    }
    if (ptr == ptr->next) {//1 ������� � �������
        ret->te = ptr->te;
        ret->id = ptr->id;
        ret->tc = ptr->tc;
        free(que->pointer);
        que->pointer = NULL;
    }
    else { //>1 �������� � �������
        while (ptr->next != que->pointer) {
            ptr = ptr->next;
        }
        ret->te = ptr->next->te;
        ret->id = ptr->next->id;
        ret->tc = ptr->next->tc;
        ptr->next = que->pointer->next;
        free(que->pointer);
        que->pointer = ptr->next;
    }
    return ret;
}

void queue_init(queue* pointer,int n) {
}

void round_robin(queue* pointer, queue* pointer_buf, int time_quantum, int** table) {             //�������������
    queue_new(pointer);
    int count = 0, count_time = time_quantum;
    process* buffer = queue_pop(pointer_buf);
    queue_push(pointer, buffer->id, buffer->tc, buffer->te);//���� ������� ��������
    free(buffer);
    while (pointer->pointer != NULL) {
        while (pointer->pointer->te > 0 && count_time > 0) {            //������ ��������
            pointer->pointer->te -= 1;       //��������� ���������
            count_time -= 1;
            table[pointer->pointer->id - 1][count] = 1;     //���������� �������
            if (pointer_buf->pointer != NULL) {
                int amount = 0;
                if (pointer_buf->pointer != NULL) {
                    queue buffer;
                    queue_new(&buffer);
                    while (pointer_buf->pointer != NULL) { //��������� ����� ���������
                        process* process_buf = queue_pop(pointer_buf);
                        if (process_buf->tc == count) {
                            queue_push(pointer, process_buf->id, process_buf->tc, process_buf->te);
                            free(process_buf);
                        }
                        else {
                            queue_push(&buffer, process_buf->id, process_buf->tc, process_buf->te);
                            amount++;
                            free(process_buf);
                        }
                    }for (int i = 0; i < amount; i++) {
                        process* process_buf = queue_pop(&buffer);
                        queue_push(pointer_buf, process_buf->id, process_buf->tc, process_buf->te);
                        free(process_buf);
                    }
                    queue_free(&buffer);
                }
            }
            count++;
        }
        if (pointer->pointer->te == 0) {//������������ ������������� ��������
            free(queue_pop(pointer));
        }
        else {
            process* process_buf = queue_pop(pointer);
            queue_push(pointer, process_buf->id, process_buf->tc, process_buf->te);//��������� � ����� �������
            free(process_buf);
        }

        //pointer->pointer = pointer->pointer->next;
        count_time = time_quantum;
    }
    queue_free(pointer);
    queue_free(pointer_buf);
}

void queue_free(queue* pointer) {         //������� ������
    if (pointer->pointer == NULL)
        free(pointer->pointer);
    else {
        if (pointer->pointer != NULL) {
            while (pointer->pointer != NULL) {
                process* process_buf = queue_pop(pointer);
                free(process_buf);
            }
            free(pointer->pointer);
        }
    }
}


#endif