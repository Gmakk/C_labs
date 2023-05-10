#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include "Header.h"	

int getInt(int* a) {
	int n = 0;
	while (n == 0) {
		n = scanf_s("%d", a);
		if (n < 0)
			return n;
		if (n == 0) {
			scanf_s("%*c", NULL);
			printf("%s", "Enter correct number\n");
		}
	}
	return n;
}

int getUnsigned(unsigned int* a) {
	int n = 0;
	while (n == 0) {
		n = scanf_s("%u", a);
		if (n < 0)
			return n;
		if (n == 0) {
			scanf_s("%*c", NULL);
			printf("%s", "Enter correct number\n");
		}
	}
	return n;
}

int getNumber(int* a) {           //ввод числа
	int n = getUnsigned(a);
	while (*a < 0) {
		printf("%s", "Enter correct number\n");
		n = getUnsigned(a);
	}
	return n;
}

char* get_str() {
	char buf[81] = { 0 };
	char* res = NULL;
	int len = 0;
	int n = 0;
	do {
		n = scanf("%80[^\n]", buf, 80);
		if (n < 0) {
			if (!res) {
				return NULL;
			}
		}
		else if (n > 0) {
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		}
		else {
			scanf("%*c");
		}
	} while (n > 0);

	if (len > 0) {
		res[len] = '\0';
	}
	else {
		res = calloc(1, sizeof(char));
	}

	return res;
}

int length(char* a)
{
	int i = 0;
	for (; a[i] != '\0'; ++i) {
	}
	return i;
}

int number_digits(unsigned int n) {
	int count = 0;
	while (n) {
		n /= 10;
		count++;
	}
	return count;
}

/*char* get_str_file(FILE* fp) {
	char buf[81] = { 0 };
	char* res = NULL;
	int len = 0;
	int n = 0;
	do {
		n = fscanf(fp,"%80[^\n]", buf, 80);
		if (n < 0) {
			if (!res) {
				return NULL;
			}
		}
		else if (n > 0) {
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		}
		else {
			fscanf(fp,"%*c");
		}
	} while (n > 0);

	if (len > 0) {
		res[len] = '\0';
	}
	else {
		res = calloc(1, sizeof(char));
	}

	return res;
}*/