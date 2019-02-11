#ifndef __HASH_TABLE_COMMAND_H__
#define __HASH_TABLE_COMMAND_H__

#include "20151607.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hash_item
{
	struct hash_elem elem;
	int data;
};

struct symbol;

//hash table command
int create_hashtable(char hash_table_name[]);
int h_insert(struct symbol* symbol, int data);
int h_replace(struct symbol* symbol, int data);
int h_find(struct symbol* symbol, int data);
int h_delete(struct symbol* symbol, int data);
void h_clear(struct symbol* symbol);
void h_size(struct symbol* symbol);
void h_empty(struct symbol* symbol);
void h_apply(struct symbol* symbol, char func[]);

//action, hash and compare function
void h_square(struct hash_elem *e, void *aux);
void h_triple(struct hash_elem *e, void *aux);
void h_destructor(struct hash_elem *e, void *aux);
unsigned h_hash_func(const struct hash_elem *e, void *aux);
bool h_less_func(const struct hash_elem *e, const struct hash_elem *b, void *aux);

#endif
