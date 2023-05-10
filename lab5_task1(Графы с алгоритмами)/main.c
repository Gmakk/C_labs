#include "Header.h"

int main() {
	List all;
	all.next = NULL;
	all.sub = NULL;
	Read(&all);
	int rc;
	const char* msgs[] = { "0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Timing" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(List*) = { NULL, D_Add, D_Find, D_Delete, D_Show, D_Timing };
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&all))
			break;

	printf("That's all.\n");
	Write(&all);
	delTree(&all);
	return 0;
}