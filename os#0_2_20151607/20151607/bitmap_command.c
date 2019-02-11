#include "bitmap_command.h"

/*	Create bitmap whose name is bitmap_name and size is bit_cnt in symbol table
	parameter : bitmap name, bit count
	return true if no error, otherwise false
*/
int create_bitmap(char bitmap_name[], size_t bit_cnt)
{
	if (DEBUG_MODE)
		printf("--func:create_bitmap	para:%s %d\n", bitmap_name, bit_cnt);

	if (find_symbol(bitmap_name) != NULL)
		return 0;

	struct symbol *pnew = malloc(sizeof(struct symbol));
	pnew->name = malloc(strlen(bitmap_name) + 1);
	pnew->d_type = D_BITMAP;
	strcpy(pnew->name, bitmap_name);

	struct bitmap* pdata = bitmap_create(bit_cnt);

	pnew->data = pdata;
	hash_insert(symbol_table, &pnew->elem);

	return 1;
}

/*	Print bit count of bitmap
	parameter : symbol of bitmap
*/
void b_size(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:b_size		para:%s\n", symbol->name);
	printf("%d\n", bitmap_size(symbol->data));
}

/*	Set the truth value in idx position
	parameter : symbol of bitmap, index of position, truth value
	return : true if no error, otherwise false
*/
int b_set(struct symbol* symbol, size_t idx, bool value)
{
	if (DEBUG_MODE)
		printf("--func:b_set		para:%s %d %d\n", symbol->name, idx, value);

	if (idx >= bitmap_size(symbol->data))
		return 0;
	bitmap_set(symbol->data, idx, value);

	return 1;
}

/*	Set the true value in idx position
	parameter : symbol of bitmap, index of position
	return : true if no error, otherwise false
*/
int b_mark(struct symbol* symbol, size_t idx)
{
	if (DEBUG_MODE)
		printf("--func:b_mark		para:%s %d\n", symbol->name, idx);

	if (idx >= bitmap_size(symbol->data))
		return 0;
	bitmap_mark(symbol->data, idx);

	return 1;
}

/*	Set the false value in idx position
	parameter : symbol of bitmap, index of position
	return : true if no error, otherwise false
*/
int b_reset(struct symbol* symbol, size_t idx)
{
	if (DEBUG_MODE)
		printf("--func:b_reset		para:%s %d\n", symbol->name, idx);

	if (idx >= bitmap_size(symbol->data))
		return 0;
	bitmap_reset(symbol->data, idx);

	return 1;
}

/*	Flip the truth value in idx position
	true -> false, false -> true
	parameter : symbol of bitmap, index of position
	return : true if no error, otherwise false
*/
int b_flip(struct symbol* symbol, size_t idx)
{
	if (DEBUG_MODE)
		printf("--func:b_flip       para:%s %d\n", symbol->name, idx);

	if (idx >= bitmap_size(symbol->data))
		return 0;
	bitmap_flip(symbol->data, idx);

	return 1;
}

/*	Print truth value of idx position in bitmap 
	parameter : symbol of bitmap, index of position
	return : true if no error, otherwise false
*/
int b_test(struct symbol* symbol, size_t idx)
{
	if (DEBUG_MODE)
		printf("--func:b_test       para:%s %d\n", symbol->name, idx);

	if (idx >= bitmap_size(symbol->data))
		return 0;

	if (bitmap_test(symbol->data, idx))
		printf("true\n");
	else
		printf("false\n");

	return 1;
}

/*	Set all bits in bitmap to value
	parameter : symbol of bitmap, truth value
*/
void b_set_all(struct symbol* symbol, bool value)
{
	if (DEBUG_MODE)
		printf("--func:b_set_all       para:%s %d\n", symbol->name, value);

	bitmap_set_all(symbol->data, value);
}

/*	Set cnt bits starting at start position in bitmap to value
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false
*/
int b_set_multiple(struct symbol* symbol, size_t start, size_t cnt, bool value)
{
	if (DEBUG_MODE)
		printf("--func:b_set_multiple       para:%s %d %d %d\n", symbol->name, start, cnt, value);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	bitmap_set_multiple(symbol->data, start, cnt, value);

	return 1;
}

/*	Print the number of bits in bitmap between start and start + cnt - 1
	that are set to value
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false 
*/
int b_count(struct symbol* symbol, size_t start, size_t cnt, bool value)
{
	if (DEBUG_MODE)
		printf("--func:b_count       para:%s %d %d %d\n", symbol->name, start, cnt, value);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	printf("%d\n", bitmap_count(symbol->data, start, cnt, value));

	return 1;
}

/*	Print the truth value whether any bits in bitmap betwwen start and start + cnt - 1
	are set to value
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false 
*/
int b_contains(struct symbol* symbol, size_t start, size_t cnt, bool value)
{
	if (DEBUG_MODE)
		printf("--func:b_contains       para:%s %d %d %d\n", symbol->name, start, cnt, value);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	if (bitmap_contains(symbol->data, start, cnt, value))
		printf("true\n");
	else
		printf("false\n");

	return 1;
}

/*	Print the truth value whether any bits in bitmap betwwen start and start + cnt - 1
	are set to TRUE
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false
*/
int b_any(struct symbol* symbol, size_t start, size_t cnt)
{
	if (DEBUG_MODE)
		printf("--func:b_any       para:%s %d %d\n", symbol->name, start, cnt);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	if (bitmap_any(symbol->data, start, cnt))
		printf("true\n");
	else
		printf("false\n");

	return 1;
}

/*	Print the truth value whether all bits in bitmap betwwen start and start + cnt - 1
	are set to FALSE
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false
*/
int b_none(struct symbol* symbol, size_t start, size_t cnt)
{
	if (DEBUG_MODE)
		printf("--func:b_none       para:%s %d %d\n", symbol->name, start, cnt);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	if (bitmap_none(symbol->data, start, cnt))
		printf("true\n");
	else
		printf("false\n");

	return 1;
}

/*	Print the truth value whether all bits in bitmap betwwen start and start + cnt - 1
	are set to TRUE
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false
*/
int b_all(struct symbol* symbol, size_t start, size_t cnt)
{
	if (DEBUG_MODE)
		printf("--func:b_all		para:%s %d %d\n", symbol->name, start, cnt);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	if (bitmap_all(symbol->data, start, cnt))
		printf("true\n");
	else
		printf("false\n");

	return 1;
}

/*	Print the starting index of first group of cnt consecutive bits in bitmap
	at or after start that are all set to value
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false
*/
int b_scan(struct symbol* symbol, size_t start, size_t cnt, bool value)
{
	if (DEBUG_MODE)
		printf("--func:b_scan		para:%s %d %d %d\n", symbol->name, start, cnt, value);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	printf("%u\n", bitmap_scan(symbol->data, start, cnt, value));

	return 1;
}

/*	Print the starting index of first group of cnt consecutive bits in bitmap
	at or after start that are all set to value
	and flips them all to !value
	parameter : symbol of bitmap, start index, count, truth value
	return : true if no error, otherwise false
*/
int b_scan_and_flip(struct symbol* symbol, size_t start, size_t cnt, bool value)
{
	if (DEBUG_MODE)
		printf("--func:b_scan_and_flip		para:%s %d %d %d\n", symbol->name, start, cnt, value);

	if (start >= bitmap_size(symbol->data) || start + cnt - 1 >= bitmap_size(symbol->data))
		return 0;

	printf("%u\n", bitmap_scan_and_flip(symbol->data, start, cnt, value));

	return 1;
}

/*	Dump the contest of bitmap to console as hexadecimal
	parameter : symbol of bitmap
*/
void b_dump(struct symbol* symbol)
{
	if (DEBUG_MODE)
		printf("--func:b_dump		para:%s\n", symbol->name);

	bitmap_dump(symbol->data);
}
/*	Expand B to be a bitmap of bit_cnt + size bits
	parameter : symbol of bitmap, size
	return : true if no error, otherwise false
*/
int b_expand(struct symbol* symbol, int size)
{
	if (DEBUG_MODE)
		printf("--func:b_expand		para:%s %d\n", symbol->name, size);

	struct bitmap *new_b = bitmap_expand(symbol->data, size);
	symbol->data = new_b;
	if (new_b)
		return 1;
	return 0;
}

