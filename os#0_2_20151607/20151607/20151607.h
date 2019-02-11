#ifndef __20151607_H__
#define __20151607_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "list_command.h"
#include "hash_table_command.h"
#include "bitmap_command.h"

#define DEBUG_MODE 0
#define CMD_BUF_SIZE 1000

enum data_type{D_LIST,D_HASH_TABLE,D_BITMAP};

struct symbol
{
	struct hash_elem elem;
	char* name;
	void* data;
	enum data_type d_type;
};

//execute command
int execute_command(char arg[]);
int execute_list(struct symbol* s, char command[], char arg[]);
int execute_hashtable(struct symbol *s, char command[], char arg[]);
int execute_bitmap(struct symbol* s, char command[], char arg[]);
void execute_quit();

//delete data and dumpdata
void delete_data_struct(struct symbol* symbol);
void dumpdata(struct symbol* symbol);

//parsing and data transform
int str_to_int(char* str);
char* read_command(char** parse);

//symbol table
struct hash* symbol_table;
unsigned symbol_hash_func(const struct hash_elem *e, void *aux);
bool symbol_hash_less(const struct hash_elem *a, const struct hash_elem *b, void *aux);
struct symbol* find_symbol(char name[]);
void symbol_destructor(struct hash_elem *e, void *aux);

#endif
