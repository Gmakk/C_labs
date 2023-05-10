#include "Header.h"	

int tree_trav_vertex(Tree* tree, int x, int y, FILE* fn,int diff){
    if (tree == NULL)
        return 1;
    if (tree->right_flag == 1) {
        if (diff > 4)
            tree_trav_vertex(tree->right, x + diff, y - 3, fn, diff - 4);//-3 -3
        else
            tree_trav_vertex(tree->right, x + diff, y - 3, fn, diff);
    }
    while (tree->left_flag == 1 && tree->key == tree->left->key)
        tree = tree->left;

    fprintf(fn, "    %d [pos = \"%d,%d!\"]\n", tree->key, x, y);

    if (tree->left_flag == 1) {
        if(diff>4)
            tree_trav_vertex(tree->left, x - diff, y - 3, fn, diff - 4);//-3 -3
        else
            tree_trav_vertex(tree->left, x - diff, y - 3, fn, diff);
    }
}

int tree_trav_edge(Tree* tree, FILE* fn){
    if (tree == NULL)
        return 1;
    if (tree->right_flag == 1) {
        fprintf(fn, "    %d -> %d\n", tree->key, tree->right->key);
        tree_trav_edge(tree->right, fn);
    }
    while (tree->left_flag == 1 && tree->key == tree->left->key)
        tree = tree->left;

    if (tree->left_flag == 1) {
        tree_trav_edge(tree->left, fn);
        fprintf(fn, "    %d -> %d\n", tree->key, tree->left->key);
    }
}

int VisualizeTree(Tree* tree) {
    if (tree->info == NULL) {
        printf("%s", "Tree is empty\n");
        return 1;
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