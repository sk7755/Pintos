#include "20151607.h"
int main()
{
	char command[CMD_BUF_SIZE];

	symbol_table = malloc(sizeof(struct hash));
	hash_init(symbol_table, symbol_hash_func, symbol_hash_less, NULL);

	while(true)
	{
		fgets(command, CMD_BUF_SIZE, stdin);
		execute_command(command);
	}

	return 0;
}

/* Execute command of user
	categorize : create , delete, quit, list, hashtable, bitmap
	parameter : argument of stdin
	return : true if no error, otherwise false
*/
int execute_command(char arg[])
{
	char *command = read_command(&arg);
	
	if (strcmp(command, "quit") == 0)
		execute_quit();

	if (strcmp(command, "create") == 0)
		return execute_create(arg);

	char *name = read_command(&arg);
	struct symbol *s = find_symbol(name);

	if(s == NULL) //There not exist object which have that name
		return 0;

	if (strcmp(command, "delete") == 0)
	{
		delete_data_struct(s);
		return 1;
	}
	if (strcmp(command, "dumpdata") == 0)
	{
		dumpdata(s);
		return 1;
	}
	if (s->d_type == D_LIST)
		return execute_list(s, command, arg);

	if (s->d_type == D_HASH_TABLE)
		return execute_hashtable(s, command, arg);

	if (s->d_type == D_BITMAP)
		return execute_bitmap(s, command, arg);

	return 0;
}

/* Execute create command of list, hashtable and bitmap
>> create list list1 : create list whose name is list1
>> create hashtable hash1 : create hashtable whose name is hash1
>> create bitmap bitmap1 bit_cnt : create bitmap whose name is bitmap1 and bit size is bit_cnt
parameter : command string except for "create"
return : false if the data name is already exist in program
else true
*/
int execute_create(char arg[])
{
	char *data_struct = read_command(&arg);
	char *name = read_command(&arg);
	if (strcmp(data_struct, "list") == 0)
		return create_list(name);

	if (strcmp(data_struct, "hashtable") == 0)
		return create_hashtable(name);

	if (strcmp(data_struct, "bitmap") == 0)
	{
		char* bit_count = read_command(&arg); //bit count
		size_t bit_cnt = str_to_int(bit_count);
		return create_bitmap(name, bit_cnt);
	}
	return 1;
}

/* Deallocate all of allocated lists, hashtables, bitmaps and symbol table
and quit the program.
>> quit
*/
void execute_quit()
{
	if (hash_size(symbol_table) > 0)
		hash_destroy(symbol_table, symbol_destructor);

	free(symbol_table);
	exit(0);
}

/* Execute list command which user inputs
>> list_command list_name parameter
COMMAND LIST : list_insert, list_splice, list_push_front, list_push_back
list_pop_front, list_pop_back, list_front, list_back, list_size
list_empty, list_sort, list_reverse, list_insert_ordered
list_unique, list_max, list_min, list_swap, list_remove, list_shuffle
parameter : symbol, command_name, arg
return : true if no error, otherwise false
*/
int execute_list(struct symbol* s, char command[], char arg[])
{
	char *parse;

	if (strcmp(command, "list_insert") == 0)
	{
		parse = read_command(&arg);
		int idx = str_to_int(parse);
		parse = read_command(&arg);
		int num = str_to_int(parse);
		l_insert(s, idx, num);
	}
	if (strcmp(command, "list_splice") == 0)
	{
		parse = read_command(&arg);
		int before_idx = str_to_int(parse);
		parse = read_command(&arg);
		struct symbol *t = find_symbol(parse);

		if (t == NULL)	//there is no symbol whose name is parse
			return 0;

		parse = read_command(&arg);
		int start_idx = str_to_int(parse);
		parse = read_command(&arg);
		int end_idx = str_to_int(parse);

		l_splice(s, before_idx, t, start_idx, end_idx);
	}
	if (strcmp(command, "list_push_front") == 0)
	{
		parse = read_command(&arg);
		int num = str_to_int(parse);
		l_push_front(s, num);
	}
	if (strcmp(command, "list_push_back") == 0)
	{
		parse = read_command(&arg);
		int num = str_to_int(parse);
		l_push_back(s, num);
	}

	if (strcmp(command, "list_remove") == 0)
	{
		parse = read_command(&arg);
		int idx = str_to_int(parse);
		l_remove(s, idx);
	}

	if (strcmp(command, "list_pop_front") == 0)
		l_pop_front(s);

	if (strcmp(command, "list_pop_back") == 0)
		l_pop_back(s);

	if (strcmp(command, "list_front") == 0)
		l_front(s);


	if (strcmp(command, "list_back") == 0)
		l_back(s);

	if (strcmp(command, "list_size") == 0)
		l_size(s);

	if (strcmp(command, "list_empty") == 0)
		l_empty(s);

	if (strcmp(command, "list_reverse") == 0)
		l_reverse(s);

	if (strcmp(command, "list_sort") == 0)
		l_sort(s);


	if (strcmp(command, "list_insert_ordered") == 0)
	{
		parse = read_command(&arg);
		int num = str_to_int(parse);
		l_insert_ordered(s, num);
	}

	if (strcmp(command, "list_unique") == 0)
	{
		parse = read_command(&arg);
		struct symbol *dup = NULL;

		if (*parse != '\0')
		{
			dup = find_symbol(parse);
			if (dup == NULL)	//there is no symbol whose name is parse
				return 0;
		}
		l_unique(s, dup);
	}

	if (strcmp(command, "list_max") == 0)
		l_max(s);

	if (strcmp(command, "list_min") == 0)
		l_min(s);

	if (strcmp(command, "list_swap") == 0)
	{
		parse = read_command(&arg);
		int idx1 = str_to_int(parse);
		parse = read_command(&arg);
		int idx2 = str_to_int(parse);

		l_swap(s, idx1, idx2);
	}
	if (strcmp(command, "list_shuffle") == 0)
		l_shuffle(s);

	return 1;
}

/* Execute hash table command which user inputs
>> hash_table_command hash_table_name parameter
COMMAND LIST : hash_insert, hash_replace, hash_find, hash_delete
			hash_clear, hash_size, hash_empty, hash_apply
parameter : symbol, command_name, arg
return : true if no error, otherwise false
*/
int execute_hashtable(struct symbol *s, char command[], char arg[])
{
	char *parse;
	if (strcmp(command, "hash_insert") == 0)
	{
		parse = read_command(&arg);
		int num = str_to_int(parse);

		h_insert(s, num);
	}

	if (strcmp(command, "hash_replace") == 0)
	{
		parse = read_command(&arg);
		int num = str_to_int(parse);

		h_replace(s, num);
	}

	if (strcmp(command, "hash_find") == 0)
	{
		parse = read_command(&arg);
		int num = str_to_int(parse);

		h_find(s, num);
	}

	if (strcmp(command, "hash_delete") == 0)
	{
		parse = read_command(&arg);
		int num = str_to_int(parse);

		h_delete(s, num);
	}

	if (strcmp(command, "hash_clear") == 0)
		h_clear(s);

	if (strcmp(command, "hash_size") == 0)
		h_size(s);

	if (strcmp(command, "hash_empty") == 0)
		h_empty(s);

	if (strcmp(command, "hash_apply") == 0)
	{
		char* action_func = read_command(&arg);
		h_apply(s, action_func);
	}

	return 1;
}

/* Execute bitmap command which user inputs
>> bitmap_command bitmap_name parameter
COMMAND LIST : bitmap_size, bitmap_set, bitmap_mark, bitmap_reset
			bitmap_flip, bitmap_test, bitmap_set_all, bitmap_set_multiple
			bitmap_count, bitmap_contains, bitmap_any, bitmap_none
			bitmap_all, bitmap_scan, bitmap_scan_and_flip, bitmap_dump
			bitmap_expand
parameter : symbol, command_name, arg
return : true if no error, otherwise false
*/
int execute_bitmap(struct symbol* s, char command[], char arg[])
{
	char *parse;

	if (strcmp(command, "bitmap_size") == 0)
		b_size(s);

	if (strcmp(command, "bitmap_set") == 0)
	{
		parse = read_command(&arg);
		size_t idx = str_to_int(parse);

		bool value = true;
		parse = read_command(&arg);
		if (strcmp(parse, "false") == 0)
			value = false;

		b_set(s, idx, value);
	}


	if (strcmp(command, "bitmap_mark") == 0)
	{
		parse = read_command(&arg);
		size_t idx = str_to_int(parse);
		b_mark(s, idx);
	}


	if (strcmp(command, "bitmap_reset") == 0)
	{
		parse = read_command(&arg);
		size_t idx = str_to_int(parse);
		b_reset(s, idx);
	}


	if (strcmp(command, "bitmap_flip") == 0)
	{
		parse = read_command(&arg);
		size_t idx = str_to_int(parse);
		b_flip(s, idx);
	}


	if (strcmp(command, "bitmap_test") == 0)
	{
		parse = read_command(&arg);
		size_t idx = str_to_int(parse);
		b_test(s, idx);
	}


	if (strcmp(command, "bitmap_set_all") == 0)
	{
		parse = read_command(&arg);
		bool value = true;
		if (strcmp(parse, "false") == 0)
			value = false;

		b_set_all(s, value);
	}


	if (strcmp(command, "bitmap_set_multiple") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		parse = read_command(&arg);
		bool value = true;

		if (strcmp(parse, "false") == 0)
			value = false;

		b_set_multiple(s, start, cnt, value);
	}


	if (strcmp(command, "bitmap_count") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		parse = read_command(&arg);
		bool value = true;

		if (strcmp(parse, "false") == 0)
			value = false;

		b_count(s, start, cnt, value);
	}


	if (strcmp(command, "bitmap_contains") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		parse = read_command(&arg);
		bool value = true;

		if (strcmp(parse, "false") == 0)
			value = false;

		b_contains(s, start, cnt, value);
	}


	if (strcmp(command, "bitmap_any") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		b_any(s, start, cnt);
	}


	if (strcmp(command, "bitmap_none") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		b_none(s, start, cnt);
	}


	if (strcmp(command, "bitmap_all") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		b_all(s, start, cnt);
	}


	if (strcmp(command, "bitmap_scan") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		parse = read_command(&arg);
		bool value = true;

		if (strcmp(parse, "false") == 0)
			value = false;

		b_scan(s, start, cnt, value);
	}


	if (strcmp(command, "bitmap_scan_and_flip") == 0)
	{
		parse = read_command(&arg);
		size_t start = str_to_int(parse);
		parse = read_command(&arg);
		size_t cnt = str_to_int(parse);
		parse = read_command(&arg);
		bool value = true;

		if (strcmp(parse, "false") == 0)
			value = false;

		b_scan_and_flip(s, start, cnt, value);
	}

	if (strcmp(command, "bitmap_dump") == 0)
		b_dump(s);


	if (strcmp(command, "bitmap_expand") == 0)
	{
		parse = read_command(&arg);
		int size = str_to_int(parse);
		b_expand(s, size);
	}

	return 1;
}

/* Transform string to integer(4byte)
	It's possible to transform signed string
	parameter : string
	return : int(string) 
*/
int str_to_int(char* str)
{
	int sign = 0;
	if(*str == '-')
	{
		str++;
		sign = 1;
	}
	int ret = 0;
	int i =0;
	while(str[i] != '\0')
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	if(sign)
		ret = -ret;
	return ret;
}

/* Read and parse the argument by blank ' '
	parameter : pointer of argument
	return : pointer of argument which point to next part(char **parse)
			pointer of argument which point to current part(char *ret)
*/
char* read_command(char** parse)
{
	char* ret = *parse;
	int i = 0;
	while((*parse)[i] != '\0' && (*parse)[i] != ' ' && (*parse)[i] != '\n')
		i++;

	if((*parse)[i] != '\0')
	{
		(*parse)[i] = '\0';
		*parse = *parse + i + 1;
	}
	return ret;
}

/* Find symbol whose name is name[] in symbol table
	parameter : name
	return : pointer of symbol if find, otherwise NULL pointer
*/
struct symbol* find_symbol(char name[])
{
	struct symbol s;
	s.name = name;

	struct hash_elem *e = hash_find(symbol_table, &(s.elem));
	if(e == NULL)
		return NULL;
	return(hash_entry(e, struct symbol, elem));
}

/* Delete data structure in symbol, remove the symbol in symboltable, and deallocate the symbol
	parameter : symbol
*/
void delete_data_struct(struct symbol* symbol)
{
	if(DEBUG_MODE)
		printf("--func:delete	para:%s\n", symbol->name);
	if(symbol->d_type == D_LIST)
	{
		int size = list_size(symbol->data);
		while(size--)
			l_pop_front(symbol);
	}
	if(symbol->d_type == D_HASH_TABLE)
		hash_destroy(symbol->data, h_destructor);

	if(symbol->d_type == D_BITMAP)
		bitmap_destroy(symbol->data);
		
	hash_delete(symbol_table, &(symbol->elem));
	free(symbol->name);
	free(symbol->data);
	free(symbol);
	
}

/* Show the content of data structure pointed by symbol
	parameter : symbol
*/
void dumpdata(struct symbol* symbol)
{
	if(DEBUG_MODE)
		printf("--func:dumpdata	para:%s\n", symbol->name);
	if(symbol->d_type == D_LIST)
	{
		if(list_size(symbol->data) > 0)
		{
			struct list_elem* e;
			for(e = list_begin(symbol->data); e != list_end(symbol->data); e= list_next(e))
			{
				printf("%d ", list_entry(e, struct list_item, elem)->data);
			}
			printf("\n");
		}
	}
	if(symbol->d_type == D_HASH_TABLE)
	{
		if(hash_size(symbol->data) > 0)
		{
			struct hash_iterator i;

			hash_first(&i, symbol->data);
			while(hash_next(&i))
			{
				printf("%d ", hash_entry(hash_cur(&i), struct hash_item, elem)->data);
			}
			printf("\n");
		}
	}
	if(symbol->d_type == D_BITMAP)
	{
		if(bitmap_size(symbol->data) > 0)
		{
			struct bitmap *b = symbol->data;
			size_t i;
			for(i = 0; i < bitmap_size(b); i++)
				printf("%d", bitmap_test(b, i));
			printf("\n");
		}
	}
}

/* Hash function of symbol table that hashes string data
	parameter : hash element, (aux)
	return : hash value
*/
unsigned symbol_hash_func(const struct hash_elem *e, void *aux)
{
	unsigned long hash = 5381;
	int c;

	char *s = hash_entry(e, struct symbol, elem)->name;
	while((c = *s++))
	{
		hash = ((hash << 5) + hash) + c;
	}

	return (unsigned)hash;
}

/*	String compare(less) function of symbol table
	parameter : hash element a, hash element b
	return true if data of a is less than data of b, otherwise false
*/
bool symbol_hash_less(const struct hash_elem *a, const struct hash_elem *b, void *aux)
{
	struct symbol *s_a = hash_entry(a, struct symbol, elem);
	struct symbol *s_b = hash_entry(b, struct symbol, elem);

	if(strcmp(s_a->name, s_b->name) < 0)
		return true;
	else
		return false;
}

/* Destructor which deallocate symbol element in symbol table
	parameter : hash element, (aux)
*/
void symbol_destructor(struct hash_elem *e, void *aux)
{
	delete_data_struct(hash_entry(e,struct symbol,elem));
}
