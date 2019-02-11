#ifndef __BITMAP_COMMAND_H__
#define __BITMAP_COMMAND_H__

#include "20151607.h"
#include "bitmap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct symbol;

int create_bitmap(char bitmap_name[], size_t bit_cnt);
void b_size(struct symbol* symbol);
int b_set(struct symbol* symbol, size_t idx, bool value);
int b_mark(struct symbol* symbol, size_t idx);
int b_reset(struct symbol* symbol, size_t idx);
int b_flip(struct symbol* symbol, size_t idx);
int b_test(struct symbol* symbol, size_t idx);
void b_set_all(struct symbol* symbol, bool value);
int b_set_multiple(struct symbol* symbol, size_t start, size_t cnt, bool value);
int b_count(struct symbol* symbol, size_t start, size_t cnt, bool value);
int b_contains(struct symbol* symbol, size_t start, size_t cnt, bool value);
int b_any(struct symbol* symbol, size_t start, size_t cnt);
int b_none(struct symbol* symbol, size_t start, size_t cnt);
int b_all(struct symbol* symbol, size_t start, size_t cnt);
int b_scan(struct symbol* symbol, size_t start, size_t cnt, bool value);
int b_scan_and_flip(struct symbol* symbol, size_t start, size_t cnt, bool value);
void b_dump(struct symbol* symbol);
int b_expand(struct symbol* symbol, int size);

#endif
