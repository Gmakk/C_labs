//� ����������� ���������� ���� ������������� ������ ������������ ���������,
//������� ������ ������������ ������������ ����� ����� ���������� �� (������������) ��������� �Round-Robin�.
//����� ��������, ������� �������� ����� �� ����������, �������������� � ������� �������.
//������ �������, ����������� ������ � �������, �������� ����� ������ ��������� �� ��������� ����� �������,
//����� ����, ���� �� ���������� ������, ������ ���� ������� ��� �������� ���������� ���������� ������ ������� � ����� �������.
//
//�������� ���������� � �������� ������ �������, ����������� ���������, � ���������.
//������ ������, ���������� ���������� � ��������: id/tc/te, ��� id � ������������� �������� (�����),
//tc � ����� ��������� �������� (����������� �����), te � ��������� ��������� ������������ ����� (����������� �����).
#include <stdio.h>
#include <stdlib.h>
#include"Header.h"

int main() {
    int amount = 0;
    while (amount < 50) {
        int time_quantum;
        printf("%s", "Enter the value of the time quantum, for 1 process\n");
        getNumber(&time_quantum);
        queue queue1, queue_buf;
        printf("%s", "Enter id/tc/te of every process\n");
        result* res = input(&queue_buf);
        if (res->height != -1 && res->height != 0) {
            int** table = (int**)calloc(res->height, sizeof(int*));
            for (int i = 0; i < res->height; ++i)
                table[i] = (int*)calloc(res->width, sizeof(int));
            table_fill(table, res->height, res->width);
            round_robin(&queue1, &queue_buf, time_quantum, table);
            printf("%s", "\n  ");
            for (int i = 0; i < res->width; ++i)
                printf("%d %s", i, " ");
            printf("%s", "\n");
            table_print(table, res->height, res->width);
            //������� ������
            for (int i = 0; i < res->height; ++i)
                free(table[i]);
            free(table);
        }
        free(res);
    }
    return 0;
}
