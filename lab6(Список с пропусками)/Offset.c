#include "Header.h"

int ADD_words(int number) {
	int size;
	char* word, buf;
	FILE* fp;
	fp = fopen("Words.txt", "a");
	for (int i = 0; i < number; i++) {
		size = rand() % 6 + 2;
		word =(char*)calloc(size, sizeof(char));
		for (int j = 0; j < size - 1; j++) {
			buf = 65 + rand() % 26;
			word[j] = buf;
		}
		word[size - 1] = '\0';
		fprintf(fp,"%s%c", word,' ');
		if (i % 5 == 0 && i!=0)
			fprintf(fp, "%c", '\n');
		free(word);
	}
	fclose(fp);
	return 1;
}

int first_occ(char* name) {
	//читаем посимвольно
	int number1, offset = 0, string_count = 1, size = 0;
	char* new,buf,*buf2;//buf2
	FILE* fp;
	Item* ip;
	fp = fopen("Words.txt", "r");
	if (!fp) {
		return -2;
	}
	List* list = new_list();
	buf2 = (char*)calloc(1, sizeof(char));
	new = (char*)calloc(1, sizeof(char));
	while (!feof(fp)) {
		new = (char*)realloc(new, size + 1);
		buf = fgetc(fp);
		offset++;
		if (buf == ' '|| buf == '\n' || feof(fp)) {
			new[size] = '\0';
			size = 0;
			if (find_with_this_key(list, new) == NULL )
				ADD(list, new, string_count, offset - length(new) - 1, buf2, 0);
			new = (char*)malloc(1, sizeof(char));
		}
		else {
			new[size] = buf;
			size++;
		}
		if (buf == '\n') {
			string_count++;
			offset = 0;
		}	
	}
	ip = find_with_this_key(list, name);
	if (ip == NULL)
		return -1;
	else {
		printf("%s%d\n%s%d\n", "String:", ip->num1, "Offset:", ip->num2);
	}
	fclose(fp);
	return 1;
}

int offset() {
	int choice, number, result;
	char* name;
	printf("%s", "Add items(1) or find offset(2):");
	getInt(&choice);
	switch (choice) {
	case 1:
		printf("%s", "How many items to add:");
		getInt(&number);
		ADD_words(number);
		break;
	case 2:
		printf("%s", "Enter string:");
		scanf_s("%*c");
		name = get_str();
		result = first_occ(name);
		switch (result)
		{
		case -2:
			printf("%s", "File is empty\n");
			break;
		case -1:
			printf("%s", "There is no such element\n");
			break;
		default:
			break;
		}
		break;
	default:
		printf("%s", "There is no such option\n");
		break;
	}
}