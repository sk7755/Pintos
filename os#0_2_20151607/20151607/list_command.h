#ifndef __LIST_COMMAND_H__
#define __LIST_COMMAND_H__

#include "20151607.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list_item
{
	struct list_elem elem;
	int data;
};

struct symbol;

int create_list(char list_name[]);
int l_insert(struct symbol* symbol, size_t idx, int data);
void l_push_front(struct symbol* symbol, int data);
void l_push_back(struct symbol* symbol, int data);
int l_pop_front(struct symbol* symbol);
int l_pop_back(struct symbol* symbol);
int l_front(struct symbol* symbol);
int l_back(struct symbol* symbol);
void l_size(struct symbol* symbol);
bool l_empty(struct symbol* symbol);
void l_sort(struct symbol* symbol);
void l_reverse(struct symbol* symbol);
void l_insert_ordered(struct symbol* symbol, int data);
void l_unique(struct symbol* symbol, struct symbol* duplicate);
int l_max(struct symbol* symbol);
int l_min(struct symbol* symbol);
int l_swap(struct symbol* symbol, size_t idx1, size_t idx2);
int l_remove(struct symbol* symbol, size_t idx);
int l_splice(struct symbol* dest, int before_idx, struct symbol* src, int start_idx, int end_idx);
void l_shuffle(struct symbol* symbol);
bool l_less_func(const struct list_elem *a, const struct list_elem *b, void *aux);

#endif
