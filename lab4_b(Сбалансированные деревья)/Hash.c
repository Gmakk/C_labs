#include "Header.h"

int hash1(char* c)
{
	int i = 0;
	for (int j = 0; j < strlen(c); ++j)
		i += c[j];
	return (i % Limit);
}

int hash2(int* i)
{
	*i += (Limit / 2) + 1;
}

ADD_table(Table* ptab)