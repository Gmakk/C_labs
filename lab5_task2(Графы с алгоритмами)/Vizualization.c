#include "Header.h"

int viz_vertex(List* all,FILE* fn) {
    List* lp = all;
    while (lp!=NULL){
        fprintf(fn, "    %s [pos = \"%d,%d!\"]\n", lp->sub->name, rand() % 10, rand() % 10);
        lp = lp->next;
    }
    return 1;
}

int viz_edge(List* all, FILE* fn) {
    List* lp = all, * lp2;
    while (lp!=NULL){
        if (lp->sub->list != NULL) {
            lp2 = lp->sub->list;
            while (lp2!=NULL){
                fprintf(fn, "    %s -> %s [label = %d]\n", lp->sub->name, lp2->sub->name, lp2->weight);
                lp2 = lp2->next;
            }
        }
        lp = lp->next;
    }
    return 1;
}

int VisualizeGraph(List* all) {
    if (all->sub == NULL) {
        printf("%s", "Graph is empty\n");
        return 1;
    }
    FILE* fn = NULL;
    if ((fn = fopen("graph.dot", "wb")) == NULL)
        return -1;
    fprintf(fn, "digraph graph1 {\n");
    fprintf(fn, "    node [fontname=\"Arial\"];\n");
    viz_vertex(all, fn);
    viz_edge(all, fn);
    fprintf(fn, "}\n");
    fclose(fn);
    system("dot -Kfdp -n -Tpng -o graph.png graph.dot");
    return 1;
}