#include "Header.h"	

int tree_trav_vertex(Tree* tree, int x, int y, FILE* fn, int diff) {
    int count = 1;
    Item* ip;
    if (tree == NULL)
        return 1;

    fprintf(fn, "    %s%d%s%d%s%d%s%d [pos = \"%d,%d!\"]\n", "", tree->low_limit_x, "9", tree->high_limit_x, "9", tree->low_limit_y, "9", tree->high_limit_y, x, y);

    if (tree->number > 0) {
        ip = tree->item;
        while (ip != NULL) {
            fprintf(fn, "    %d%s%d [pos = \"%d,%d!\"]\n", ip->key_x, "9", ip->key_y, x, y - count);
            count++;
            ip = ip->next;
        }
    }
    if (tree->number == 0 && tree->sub[0] != NULL && tree->sub[1] != NULL && tree->sub[2] != NULL && tree->sub[3] != NULL) {
        if (diff > 2) {
            tree_trav_vertex(tree->sub[0], x - 10, y - 5, fn, diff - 2);
            tree_trav_vertex(tree->sub[1], x - 5, y - 5, fn, diff - 2);
            tree_trav_vertex(tree->sub[2], x + 5, y - 5, fn, diff - 2);
            tree_trav_vertex(tree->sub[3], x + 10, y - 5, fn, diff - 2);
        }
        else
        {
            tree_trav_vertex(tree->sub[0], x - 10, y - 5, fn, diff);
            tree_trav_vertex(tree->sub[1], x - 5, y - 5, fn, diff);
            tree_trav_vertex(tree->sub[2], x + 5, y - 5, fn, diff);
            tree_trav_vertex(tree->sub[3], x + 10, y - 5, fn, diff);
        }
    }
}

int tree_trav_edge(Tree* tree, FILE* fn) {
    Item* ip;
    if (tree == NULL)
        return 1;
    if (tree->number > 0) {
        ip = tree->item;
        fprintf(fn, "    %s%d%s%d%s%d%s%d -> %d%s%d\n", "", tree->low_limit_x, "9", tree->high_limit_x, "9", tree->low_limit_y, "9", tree->high_limit_y, ip->key_x, "9", ip->key_y);
        while (ip != NULL) {
            if (ip->next != NULL)
                fprintf(fn, "    %d%s%d -> %d%s%d\n", ip->key_x, "9", ip->key_y, ip->next->key_x, "9", ip->next->key_y);
            ip = ip->next;
        }
    }
    if (tree->number == 0 && tree->sub[0] != NULL && tree->sub[1] != NULL && tree->sub[2] != NULL && tree->sub[3] != NULL) {
        for (int p = 0; p < 4; p++) {
            fprintf(fn, "    %s%d%s%d%s%d%s%d -> %s%d%s%d%s%d%s%d\n", "", tree->low_limit_x, "9", tree->high_limit_x, "9", tree->low_limit_y, "9", tree->high_limit_y,
                "", tree->sub[p]->low_limit_x, "9", tree->sub[p]->high_limit_x, "9", tree->sub[p]->low_limit_y, "9", tree->sub[p]->high_limit_y);
            tree_trav_edge(tree->sub[p], fn);
        }
    }
}

int tree_trav_points(Tree* tree, FILE* fn) {
    Item* ip;
    if (tree == NULL)
        return 1;
    if (tree->number > 0) {
        ip = tree->item;
        while (ip != NULL) {
            fprintf(fn, "    %d%s%d [pos = \"%d,%d!\"]\n", ip->key_x, "9", ip->key_y, ip->key_x, ip->key_y);
            ip = ip->next;
        }
    }
    if (tree->number == 0 && tree->sub[0] != NULL && tree->sub[1] != NULL && tree->sub[2] != NULL && tree->sub[3] != NULL) {
        for (int p = 0; p < 4; p++)
            tree_trav_points(tree->sub[p], fn);
    }
}

int VisualizeTree(Tree* tree) {
    if (tree->number == 0 && tree->sub[0] == NULL && tree->sub[1] == NULL && tree->sub[2] == NULL && tree->sub[3] == NULL) {
        printf("%s", "Tree is empty");
        return -1;
    }
    FILE* fn = NULL;
    if ((fn = fopen("tree.dot", "wb")) == NULL)
        return -1;
    fprintf(fn, "digraph tree {\n");//???
    fprintf(fn, "    node [fontname=\"Arial\"];\n");
    tree_trav_vertex(tree, 500, 500, fn, 10);
    tree_trav_edge(tree, fn);
    fprintf(fn, "}\n");
    fclose(fn);
    system("dot -Kfdp -n -Tpng -o tree.png tree.dot");
    return 1;
}

int VisualizePoints(Tree* tree) {
    if (tree->number == 0 && tree->sub[0] == NULL && tree->sub[1] == NULL && tree->sub[2] == NULL && tree->sub[3] == NULL) {
        printf("%s", "Tree is empty");
        return -1;
    }
    FILE* fn = NULL;
    if ((fn = fopen("tree.dot", "wb")) == NULL)
        return -1;
    fprintf(fn, "digraph tree {\n");//???
    fprintf(fn, "    node [fontname=\"Arial\"];\n");
    tree_trav_points(tree, fn);
    fprintf(fn, "}\n");
    fclose(fn);
    system("dot -Kfdp -n -Tpng -o tree.png tree.dot");
    return 1;
}