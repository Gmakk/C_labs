#include "Header.h"

int main() {
	Tree tree;
	tree.info = NULL;
	Read(&tree);
	int rc;
	const char* msgs[] = { "0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Timing", "6. Visualization","7. Counting"};
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(Tree*) = { NULL, D_Add, D_Find, D_Delete, D_Show, D_Timing, VisualizeTree, Counting};
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&tree))
			break;

	printf("That's all.\n");
	Write(&tree);
	delTree(&tree);
	return 0;
}