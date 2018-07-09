#include "./include/store.h"

void init_store(int *store)
{
	for(int i = 0; i < 5; i++){
		store[i] = 100;
		store[i] += -10 + rand() % 10;
	}
}
