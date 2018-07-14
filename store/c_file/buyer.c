#include "./include/buyer.h"

void init_buyer(int *content_buyer)
{
	*content_buyer = rand() % 1000;
	*content_buyer += -10 + rand() % 10;
}

int store_select_buyer()
{
	int store = 0 + rand() % 5;
	return store;	
}

void buy(int *content_buyer, int *store, int store_b)
{
	if(*content_buyer > store[store_b]){
		*content_buyer -= store[store_b];
		store[store_b] = 0;
	}else{
		store[store_b] -= *content_buyer;
		*content_buyer = 0;
	}
}
