#include "Header.h"

int ADD(List* all, List* list, int x, int y, char* name) {
	List* lp;
	if (all->sub == NULL) {//вершин нет
		all->sub = (Graph*)calloc(1, sizeof(Graph));
		all->sub->list = list;
		all->sub->x = x;
		all->sub->y = y;
		all->sub->name = name;
		all->next = NULL;
	}
	else {
		lp = all;
		while (lp->next != NULL)
			lp = lp->next;
		lp->next = (List*)calloc(1, sizeof(List));
		lp->next->sub = (Graph*)calloc(1, sizeof(Graph));
		lp->next->sub->list = list;
		lp->next->sub->x = x;
		lp->next->sub->y = y;
		lp->next->sub->name = name;
		lp->next->next == NULL;
	}
	return 1;
}

int ADD_edge(Graph* sub, Graph* sub2, int weight) {
	List* lp, * list;
	//создание указателя на элемент
	lp = (List*)calloc(1, sizeof(List));;
	lp->sub = sub2;
	lp->weight = weight;
	lp->next = NULL;
	//ребер еще не было
	if (sub->list == NULL)
		sub->list = lp;
	//обавление в конец списка
	else {
		list = sub->list;
		while (list->next != NULL)
			list = list->next;
		list->next = lp;
	}
}

int check_edge(List* all, Graph* sub, Graph* sub2) {
	List* list;
	if (all->next == NULL) {
		return -1;
	}
	if (all->sub == NULL) {
		return -1;
	}
	list = sub->list;
	while (list != NULL) {
		if (list->sub == sub2) {
			return -1;
		}
		list = list->next;
	}
	return 1;
}

Graph* find_with_this_name(List* all, char* name) {
	List* lp = all;
	if (all->sub != NULL) {
		while (lp != NULL) {
			if (strcmp(lp->sub->name, name) == 0)
				return lp->sub;
			lp = lp->next;
		}
	}
	return NULL;
}

int free_list(List* all) {
	List* lp, * parent;
	if (all != NULL) {
		lp = all;
		if (lp->next == NULL) {
			free(lp);
			return 1;
		}
		else {
			parent = lp;
			lp = lp->next;
			while (lp != NULL) {
				free(parent);
				parent = lp;
				lp = lp->next;
			}
			free(parent);
		}
	}
	return 1;
}

int delete_from_list(Graph* sub, List* target) {
	List* all = sub->list;
	List* lp, * parent;
	if (all->sub == NULL)
		return -1;
	lp = all;
	if (lp->next == NULL) {
		if (target == all) {
			free(all);
			sub->list = NULL;
			return 2;
		}
		else
			return -1;
	}
	parent = all;
	lp = all->next;
	//первый элемент
	if (target == parent) {
		parent->sub = lp->sub;
		parent->next = lp->next;
		parent->weight = lp->weight;
		free(lp);
		lp = NULL;
		return 1;
	}
	while (lp->next != NULL && lp != target) {
		parent = lp;
		lp = lp->next;
	}
	//последний элмент
	if (lp->next == NULL && target == lp) {
		parent->next = NULL;
		free(lp);
		lp = NULL;
		return 1;
	}
	//элемент из середины
	if (target == lp) {
		parent->next = lp->next;
		free(lp);
		lp = NULL;
		return 1;
	}
	return -1;
}

int delete_mentions(List* all, Graph* gp) {
	List* lp = all, * check, * buf;
	while (lp != NULL) {
		if (lp->sub->list != NULL) {
			check = lp->sub->list;
			while (check != NULL) {
				if (check->sub == gp) {
					//buf = check->next;
					if (delete_from_list(lp->sub, check) == 2)
						lp->sub->list = NULL;
					break;
					//check = buf;
				}
				else
					check = check->next;
			}
		}
		lp = lp->next;
	}
	return 1;
}

int delete_element(List* all, char* name) {
	List* lp, * parent;
	if (all->sub == NULL)
		return -1;
	lp = all;
	if (lp->next == NULL) {
		if (strcmp(name, lp->sub->name) == 0) {
			free(lp->sub->name);
			free_list(lp->sub->list);
			free(lp->sub);
			all->sub = NULL;
			all->next = NULL;
			return 1;
		}
		else
			return -1;
	}
	parent = all;
	lp = all->next;
	//первый элемент
	if (strcmp(name, parent->sub->name) == 0) {
		free(all->sub->name);
		free_list(all->sub->list);
		free(all->sub);
		all->next = lp->next;
		all->sub = lp->sub;
		free(lp);
		return 1;
	}
	while (lp->next != NULL && strcmp(name, lp->sub->name) != 0) {
		parent = lp;
		lp = lp->next;
	}
	//последний элмент
	if (lp->next == NULL && strcmp(name, lp->sub->name) == 0) {
		parent->next == NULL;
		free(lp->sub->name);
		free_list(lp->sub->list);
		free(lp->sub);
		free(lp);
		return 1;
	}
	//элемент из середины
	if (strcmp(name, lp->sub->name) == 0) {
		parent->next = lp->next;
		free(lp->sub->name);
		free_list(lp->sub->list);
		free(lp->sub);
		free(lp);
		return 1;
	}
	return -1;
}

int print_graph(Graph* buf) {
	List* lp;
	printf("%s", "x       y       name\n");
	printf("%d%s%d%s%s%c", buf->x, "	", buf->y, "	", buf->name, '\n');
	if (buf->list != NULL) {
		printf("%s", "Related vertexes with weidth:\n");
		lp = buf->list;
		while (lp->next != NULL) {
			printf("%s%s%d%c", lp->sub->name, " ; ", lp->weight, '\n');
			lp = lp->next;
		}
		printf("%s%s%d%c", lp->sub->name, " ; ", lp->weight, '\n');
	}
}

int count_List(List* all) {
	List* lp;
	int count = 0;
	lp = all;
	while (lp != NULL) {
		count++;
		lp = lp->next;
	}
	return count;
}

int count_number(List* all, Graph* sub) {
	int count = 0;
	List* lp = all;
	while (lp != NULL && lp->sub != sub){
		count++;
		lp = lp->next;
	}
	return count;
}

int entry_count(Graph* sub) {
	return sub->sum;
}

int outputs_count(Graph* sub) {
	int count = 0;
	List* lp;
	if (sub->list == NULL)
		return 0;
	lp = sub->list;
	while (lp!=NULL){
		count++;
		lp = lp->next;
	}
	return count;
}

int source_check(List* all, Graph* sub) {
	int outputs, entry;
	outputs = outputs_count(sub);
	entry = entry_count(sub);
	if (outputs == 0 && entry > 0)//сток
		return 1;
	if (outputs > 0 && entry == 0)//исток
		return -1;
	return 0;
}

int set_sum(List* all) {
	int count = 0;
	List* lp = all, * lp2;
	while (lp != NULL) {
		lp->sub->sum = 0;
		lp = lp->next;
	}
	lp = all;
	while (lp != NULL) {
		if (lp->sub->list != NULL && lp->sub->visited == 0) {
			lp2 = lp->sub->list;
			while (lp2 != NULL) {
				lp2->sub->sum++;
				lp2 = lp2->next;
			}
		}
		lp = lp->next;
	}
	return count;
}