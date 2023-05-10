//#define  LIST
#define VECTOR

#ifdef LIST
typedef struct process {    //�������
    int id, tc, te;
    struct process* next;
}process;

typedef struct queue {    //�������
    process* pointer;
}queue;
#else
typedef struct process {    //�������
    int id, tc, te;
}process;

typedef struct queue {    //�������
    int top,allocated;
    process* vector;
}queue;
#endif

typedef struct result {    //������� �������
    int height, width;
}result;

char* get_str();

int getInt(int* a);

int getNumber(int* a);

void table_print(int** table, int height, int width);

void table_fill(int** table, int height, int width);

void round_robin(queue* pointer, queue* pointer_buf, int time_quantum, int** table);

int number_check(char* symbol);

result* input(queue* queue);
