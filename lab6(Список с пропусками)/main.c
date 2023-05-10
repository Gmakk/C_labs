#include "Header.h"

int main() {
	srand(time(NULL));
	List* list = new_list();
	Read(list);
	int rc;
	const char* msgs[] = { "0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Timing","6. Vizualization","7.Offset"};
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(List*) = { NULL, D_Add, D_Find, D_Delete, D_Show, D_Timing, VisualizeList, offset};
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](list))
			break;

	printf("That's all.\n");
	Write(list);
	delTree(list);
	return 0;
}