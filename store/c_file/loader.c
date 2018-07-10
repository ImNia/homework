#include "./include/loader.h"

int store_selection()
{
	int number_store = 0 + rand() % 5;
	return number_store;	
}

int init_content()
{
	int content = 50;
	content += -5 + rand() % 5;
	return content;
}

int working(int *store, int *number_store)
{
	int content_store = init_content();
	store[*number_store] += content_store;
    return content_store;
}
