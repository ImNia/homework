#include <stdio.h>
#include <pthread.h>
#include "./c_file/include/store.h"
#include "./c_file/include/loader.h"
#include "./c_file/include/buyer.h"

void print(int *store)
{
    for(int i = 0; i < 5; i++){
        printf("%d\t", store[i]);
    }
    printf("\n");
}

int main()
{
    int *store = (int*)malloc(5 * sizeof(int));
    init_store(store);
    print(store);

    int *content_buyer = (int*)malloc(1 * sizeof(int));
    init_buyer(content_buyer);

    printf("%d\n", *content_buyer);
    buy(content_buyer, store);
    printf("%d\n", *content_buyer);
    print(store);

/*    while(1){
        working(store);
        print(store);
    }
*/

    return 0;
}
