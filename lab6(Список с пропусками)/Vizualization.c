#include "Header.h"

int list_trav_vertex(List* list, FILE* fn) {
	int count = 0;
	Item* ip = list->header->forvards[0];
	while (ip != NULL) {
		if (ip->key != HighStr && ip->key != LowStr) {
			for (int i = 0; i < ip->level; i++)
				fprintf(fn, "    %s%d [pos = \"%d,%d!\"]\n", ip->key ,i, count, i);
		}
		ip = ip->forvards[0];
		count+=2;
	}
    for (int i = 0; i <list->level; i++)
        fprintf(fn, "    %s%d [pos = \"%d,%d!\"]\n", "0", i, count, i);
	return 1;
}

int list_trav_edge(List* list, FILE* fn) {
    Item* ip, * parent;
    for (int i = 0; i < MaxLevel; i++) {
        ip = list->header->forvards[i];
        parent = list->header;
        while (strcmp(parent->key,HighStr)!=0){
            if (strcmp(parent->key, LowStr) != 0) {
                if(strcmp(ip->key, HighStr) != 0)
                    fprintf(fn, "    %s%d -> %s%d\n", parent->key, i, ip->key, i);
                else
                    fprintf(fn, "    %s%d -> %s%d\n", parent->key, i, "0", i);
            }
            parent = ip;
            ip = ip->forvards[i];
        }

    }
    return 1;
}

int VisualizeList(List* list) {
    if (list->level==0) {
        printf("%s", "List is empty\n");
        return 1;
    }
    FILE* fn = NULL;
    if ((fn = fopen("list.dot", "wb")) == NULL)
        return -1;
    fprintf(fn, "digraph list {\n");//???
    fprintf(fn, "    node [fontname=\"Arial\"];\n");
    list_trav_vertex(list, fn);
    list_trav_edge(list, fn);
    fprintf(fn, "}\n");
    fclose(fn);
    system("dot -Kfdp -n -Tpng -o list.png list.dot");
    return 1;
}