#include "hash_table_command.h"

/* Create hash table whose name is hash_table_name
	parameter : hash table name
	return : true if no error, otherwise false
*/
int create_hashtable(char hash_table_name[])
{
	if (DEBUG_MODE)
		printf("--func:create_hash	para :%s\n", hash_table_name);

	if (find_symbol(hash_table_name) != NULL)
		return 0;

	struct symbol *pnew = malloc(sizeof(struct symbol));
	pnew->name = malloc(strlen(hash_table_name) + 1);
	pnew->d_type = D_HASH_TABLE;
	strcpy(pnew->name, hash_table_name);

	struct hash* pdata = malloc(sizeof(struct hash));
	hash_init(pdata, h_hash_func, h_less_func, 0);

	pnew->data = pdata;
	hash_insert(symbol_table, &(pnew->elem));

	return 1;
}

/* Insert integer data in hash table
	parameter : symbol of hash table, int data
	return : true if no error, otherwise false
*/
int h_insert(struct symbol* symbol, int data)
{
	if (DEBUG_MODE)
		printf("--func:h_insert		para:%s %d\n", symbol->name, data);
	struct hash_item* pnew = malloc(sizeof(struct hash_item));
	pnew->data = data;
	if (hash_insert(symbol->data, &(pnew->elem)))
		return 0;
	return 1;
}

/*	Replace old integer data with new integer data
	if there already exist same integer, delete old and insert new
	otherwise only insert new data
	parameter : symbol of hash table, int data
	return : true if no error, otherwise false
*/
int h_replace(struct symbol* symbol, int data)
{
	if (DEBUG_MODE)
		printf("--func:h_replace	para:%s %d\n", symbol->name, data);
	struct hash_item* pnew = malloc(sizeof(struct hash_item));
	pnew->data = data;

	if (hash_replace(symbol->data, &(pnew->elem)) == NULL)
		return 0;

	return 1;
}

/*	Find the integer in hash table and print that
	parameter : symbol of hash table, int data 
	return : if exist, print the integer and return 1
			if no exist, return 0
*/
int h_find(struct symbol* symbol, int data)
{
	if (DEBUG_MODE)
		printf("--func:h_find	para:%s %d\n", symbol->name, data);
	struct hash_item *pnew = malloc(sizeof(struct hash_item));
	pnew->data = data;

	int ret = 1;
	struct hash_elem *e = hash_find(symbol->data, &(pnew->elem));

	if (e == NULL)
		ret = 0;
	else
		printf("%d\n", hash_entry(e, struct hash_item, elem)->data);

	free(pnew);
	return ret;
}

/*	Delete the integer in hash table
	parameter : symbol of hash table, int data
	return : if exsit, delete in hash table ,deallocate it and return 1
			if not, return 0
*/
int h_delete(struct symbol* symbol, int data)
{
	if (DEBUG_MODE)
		printf("--func:h_delete	para:%s %d\n", symbol->name, data);
	struct hash_item *pnew = malloc(sizeof(struct hash_item));
	pnew->data = data;

	struct hash_elem *e = hash_delete(symbol->data, &(pnew->elem));
	free(pnew);

	if (e == NULL)
		return 0;

	free(hash_entry(e, struct hash_item, elem));

	return 1;
}

/*	Clear the hash table and make hash table empty
	parameter : symbol of hash table
*/
void h_clear(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:h_clear	para:%s\n", symbol->name);
	hash_clear(symbol->data, h_destructor);
}

/*	Print the size of hash table,
	that is the number of elements in hash table
	parameter : symbol of hash table
*/
void h_size(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:h_size	para:%s\n", symbol->name);
	printf("%lu\n", hash_size(symbol->data));
}

/*	Print the truth value of wheter the hash table is empty
	parameter : symbol of hash table
*/
void h_empty(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:h_empty	para:%s\n", symbol->name);

	if (hash_empty(symbol->data))
		printf("true\n");
	else
		printf("false\n");
}

/*	Apply function to all of data in hash table
	APPLY FUNC LIST : square(x -> x*x), triple(x -> x*x*x)
	parameter : symbol of hash table, apply function
*/
void h_apply(struct symbol* symbol, char func[])
{
	if (DEBUG_MODE)
		printf("--func:h_apply	para:%s %s\n", symbol->name, func);

	if (strcmp(func, "square") == 0)
		hash_apply(symbol->data, h_square);
	if (strcmp(func, "triple") == 0)
		hash_apply(symbol->data, h_triple);
}

/*	Apply function which square the data in hash element
	parameter : hash element, (aux)
*/
void h_square(struct hash_elem *e, void *aux)
{
	struct hash_item* item = hash_entry(e, struct hash_item, elem);
	item->data *= item->data;
}

/*	Apply function which triple the data in hash element
	parameter : hash element, (aux)
*/
void h_triple(struct hash_elem *e, void *aux)
{
	struct hash_item* item = hash_entry(e, struct hash_item, elem);
	item->data *= item->data * item->data;
}

/*	Destructor function which deallocate hash element
	parameter : hash element, (aux)
*/
void h_destructor(struct hash_elem *e, void *aux)
{
	free(hash_entry(e, struct hash_item, elem));
}

/*	Hash function which make hash value of integer in element
	parameter : hash element, (aux)
	return : hash value of integer
*/
unsigned h_hash_func(const struct hash_elem *e, void *aux)
{
	int i = hash_entry(e, struct hash_item, elem)->data;

	return hash_int(i);
}

/*	Integer compare(less) function of hash table
	parameter : hash element a, hash element b
	return true if data of a is less than data of b, otherwise false
*/
bool h_less_func(const struct hash_elem *a, const struct hash_elem *b, void *aux)
{
	int d_a = hash_entry(a, struct hash_item, elem)->data;
	int d_b = hash_entry(b, struct hash_item, elem)->data;

	return d_a < d_b;
}

