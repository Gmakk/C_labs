#include "Header.h"
#include "File.h"

int main() {
	Table table;
	Read(&table);
	int rc;
	const char* msgs[] = { "0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(Table*) = { NULL, D_Add, D_Find, D_Delete, D_Show };
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&table))
			break;

	printf("That's all.\n");
	Write(&table);
	delTable(&table);
	return 0;
}