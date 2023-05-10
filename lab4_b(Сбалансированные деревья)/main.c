#include "Header.h"

int main() {
	Tree tree;
	Table* ptab = (Table*)calloc(1, sizeof(Table));
	ptab->number = 0;
	ptab->mass = (Tree*)calloc(Limit, sizeof(Tree));
	new_tree(&tree, x_low_limit, x_high_limit, y_low_limit, y_high_limit, 4);
	Read(&tree);
	int rc;
	const char* msgs[] = { "0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Timing","6. Tree vizualization","7. Visualization of points","8.Offset" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(Tree*) = { NULL, D_Add, D_Find, D_Delete, D_Show, D_Timing, VisualizeTree, VisualizePoints, offset };
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&tree))
			break;

	printf("That's all.\n");
	Write(&tree);
	delTree(&tree);
	return 0;
}