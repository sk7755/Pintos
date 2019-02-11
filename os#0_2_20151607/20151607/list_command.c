#include "list_command.h"

/* Create symbol whose name is list_name in symbol table
	parameter : list name
	return true if no error, otherwise false
*/
int create_list(char list_name[])
{
	if (DEBUG_MODE)
		printf("---func :create_list	para :%s\n", list_name);

	if (find_symbol(list_name) != NULL)
		return 0;

	struct symbol *pnew = malloc(sizeof(struct symbol));
	pnew->name = malloc(strlen(list_name) + 1);
	pnew->d_type = D_LIST;
	strcpy(pnew->name, list_name);

	struct list* pdata = malloc(sizeof(struct list));
	list_init(pdata);

	pnew->data = pdata;
	hash_insert(symbol_table, &(pnew->elem));

	return 1;
}

/* Insert integer in list according to index parameter
	parameter : symbol of list, index, int data
	return true if no error, otherwise false
*/
int l_insert(struct symbol* symbol, size_t idx, int data)
{
	if (DEBUG_MODE)
		printf("--func:l_insert	para:%s %d\n", symbol->name, data);
	struct list_item* pnew = malloc(sizeof(struct list_item));
	pnew->data = data;

	if (idx > list_size(symbol->data))
		return 0;
	struct list_elem *e = list_begin(symbol->data);
	while (idx--)
		e = list_next(e);

	list_insert(e, &(pnew->elem));
	return 1;
}

/* Insert integer in front of list
	parameter : symbol of list, int data
*/
void l_push_front(struct symbol* symbol, int data)
{
	if (DEBUG_MODE)
		printf("--func:l_push_front	para:%s %d\n", symbol->name, data);
	struct list_item* pnew = malloc(sizeof(struct list_item));
	pnew->data = data;
	list_push_front(symbol->data, &(pnew->elem));
}

/* Insert integer in rear of list
	parameter : symbol of list, int data
*/
void l_push_back(struct symbol* symbol, int data)
{
	if (DEBUG_MODE)
		printf("--func:l_push_back	para:%s %d\n", symbol->name, data);
	struct list_item* pnew = malloc(sizeof(struct list_item));
	pnew->data = data;
	list_push_back(symbol->data, &(pnew->elem));
}

/* Delete integer in front of list and deallocate
	parameter : symbol of list, int data
	return true if non empty, otherwise false
*/
int l_pop_front(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_pop_front	para:%s\n", symbol->name);
	if (list_empty(symbol->data))
		return 0;
	free(list_entry(list_pop_front(symbol->data), struct list_item, elem));
	return 1;
}

/* Delete integer in rear of list and deallocate
	parameter : symbol of list, int data
	return true if non empty, otherwise false
*/
int l_pop_back(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_pop_back	para:%s\n", symbol->name);
	if (list_empty(symbol->data))
		return 0;
	free(list_entry(list_pop_back(symbol->data), struct list_item, elem));
	return 1;
}

/* Print integer in front of list
	parameter : symbol of list, int data
	return true if non empty, otherwise false
*/
int l_front(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_front	para:%s\n", symbol->name);
	if (list_empty(symbol->data))
		return 0;
	struct list_elem* e = list_front(symbol->data);
	printf("%d\n", list_entry(e, struct list_item, elem)->data);
	return 1;
}

/* Print integer in rear of list
	parameter : symbol of list, int data
	return true if non empty, otherwise false
*/
int l_back(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_back	para:%s\n", symbol->name);
	if (list_empty(symbol->data))
		return 0;
	struct list_elem* e = list_back(symbol->data);
	printf("%d\n", list_entry(e, struct list_item, elem)->data);
	return 1;
}

/* Print size of list
	parameter : symbol of list
*/
void l_size(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_size  para:%s\n", symbol->name);
	printf("%lu\n", list_size(symbol->data));
}

/* Print truth value about EMPTY
	parameter : symbol of list
	return true if list is empty, otherwise false
*/
bool l_empty(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_empty	para:%s\n", symbol->name);
	int ret = list_empty(symbol->data);

	if (ret)
		printf("true\n");
	else
		printf("false\n");

	return ret;
}

/* Sort the list to accending order
	parameter : symbol of list
*/
void l_sort(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_sort	para:%s\n", symbol->name);
	list_sort(symbol->data, l_less_func, NULL);
}

/* Make the list reverse order
	parameter : symbol of list
*/
void l_reverse(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_reverse	para:%s\n", symbol->name);
	list_reverse(symbol->data);
}

/* Insert integer in list keeping accending order
	parameter : symbol of list, int data
*/
void l_insert_ordered(struct symbol* symbol, int data)
{
	if (DEBUG_MODE)
		printf("--func:l_insert_orderd	para:%s %d\n", symbol->name, data);
	struct list_item *pnew = malloc(sizeof(struct list_item));
	pnew->data = data;
	list_insert_ordered(symbol->data, &(pnew->elem), l_less_func, NULL);

}

/* duplicate list1 to list2 such that there no exist element which apear more than once
	if list2 is NULL, list1 duplicate to itself and list1 will be deleted 
	parameter : symbol of list1, symbol of list2
*/
void l_unique(struct symbol* symbol, struct symbol* duplicate)
{
	if (DEBUG_MODE)
	{
		printf("--func:l_unique	para:%s ", symbol->name);
		if (duplicate == NULL)
			printf("NULL\n");
		else
			printf("%s\n", duplicate->name);
	}
	if (duplicate == NULL)
		list_unique(symbol->data, NULL, l_less_func, NULL);
	else
		list_unique(symbol->data, duplicate->data, l_less_func, NULL);
}

/*	Print max element in list
	parameter : symbol of list
	return : true if no error, otherwise false
*/
int l_max(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_max	para:%s\n", symbol->name);
	if (list_empty(symbol->data))
		return 0;
	struct list_elem *max = list_max(symbol->data, l_less_func, NULL);

	printf("%d\n", list_entry(max, struct list_item, elem)->data);

	return 1;
}

/*	Print min element in list
parameter : symbol of list
return : true if no error, otherwise false
*/
int l_min(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_min	para:%s\n", symbol->name);
	if (list_empty(symbol->data))
		return 0;

	struct list_elem *min = list_min(symbol->data, l_less_func, NULL);

	printf("%d\n", list_entry(min, struct list_item, elem)->data);

	return 1;
}

/*	Swap element1 indexed idx1 and element2 indexed idx2
	parameter : symbol of list, index1 ,index2
	return : true if no error, otherwise false
*/
int l_swap(struct symbol* symbol, size_t idx1, size_t idx2)
{
	if (DEBUG_MODE)
		printf("--func:l_swap		para:%s %d %d\n", symbol->name, idx1, idx2);

	if (idx1 >= list_size(symbol->data) || idx2 >= list_size(symbol->data))
		return 0;

	struct list_elem* e = list_begin(symbol->data);

	if (idx1 > idx2)
	{
		int tmp = idx1;
		idx1 = idx2;
		idx2 = tmp;
	}
	idx2 -= idx1;

	while (idx1--)
		e = list_next(e);
	struct list_elem *a = e;
	while (idx2--)
		e = list_next(e);
	struct list_elem *b = e;

	list_swap(a, b);

	return 1;
}

/*	Shuffle the list in some method
	parameter : symbol of list
*/
void l_shuffle(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:l_shuffle	para:%s\n", symbol->name);
	list_shuffle(symbol->data);
}

/*	Remove element indexed idx in list
	parameter : symbol of list, index
	return : true if no error, otherwise false
*/
int l_remove(struct symbol* symbol, size_t idx)
{
	if (DEBUG_MODE)
		printf("--func:l_remove	para:%s %d\n", symbol->name, idx);
	if (idx >= list_size(symbol->data))
		return 0;

	struct list_elem* e = list_begin(symbol->data);
	while (idx--)
		e = list_next(e);

	list_remove(e);
	free(list_entry(e, struct list_item, elem));

	return 1;
}

/*	Paste (start_idx ~ end_idx -1) of src list to before_idx of dest list
	and remove this part in src list
	parameter : dest list, before index, src list, start index, end index
	return : true if no error, otherwise false
*/
int l_splice(struct symbol* dest, int before_idx, struct symbol* src, int start_idx, int end_idx)
{
	if (DEBUG_MODE)
		printf("--func:l_splice	para:%s %d %s %d %d\n", dest->name, before_idx, src->name, start_idx, end_idx);
	int src_size = list_size(src->data);
	int dest_size = list_size(dest->data);
	if (start_idx > end_idx || src_size < end_idx || dest_size < before_idx)	//index error
		return 0;

	struct list_elem* start = list_begin(src->data);
	end_idx -= start_idx;
	while (start_idx--)
		start = list_next(start);

	struct list_elem* end = start;
	while (end_idx--)
		end = list_next(end);

	struct list_elem* before = list_begin(dest->data);

	while (before_idx--)
		before = list_next(before);

	list_splice(before, start, end);

	return 1;
}

/*	Integer compare(less) function of list
	parameter : list element a, list element b
	return true if data of a is less than data of b, otherwise false
*/
bool l_less_func(const struct list_elem *a, const struct list_elem *b, void *aux)
{
	struct list_item* item_a = list_entry(a, struct list_item, elem);
	struct list_item* item_b = list_entry(b, struct list_item, elem);

	return item_a->data < item_b->data;
}
