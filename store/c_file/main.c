#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "./c_file/include/store.h"
#include "./c_file/include/loader.h"
#include "./c_file/include/buyer.h"

pthread_mutex_t mutex;
pthread_mutex_t mutex_l;

void print(int *store)
{
    for(int i = 0; i < 5; i++){
        printf("%d\t", store[i]);
    }
    printf("\n");
}

void* buy_main(void *args)
{
    int store_num;
    int *content_buyer = (int*)malloc(1 * sizeof(int));
    init_buyer(content_buyer);

    while(*content_buyer > 0){
        pthread_mutex_lock(&mutex);
        store_num = buy(content_buyer, args);
        pthread_mutex_unlock(&mutex);
        printf("Покупатель %d забрал из магазина %d: его лимит %d\n", pthread_self(), store_num + 1, *content_buyer);
//        print(args);
        sleep(3);
    }
    return 0;
}

void* loader_main(void *args)
{
    int *number_store = (int*)malloc(1 * sizeof(int));
    int content;

    while(1){
        pthread_mutex_lock(&mutex_l);
        *number_store = store_selection();
        content = working(args, number_store);
        pthread_mutex_unlock(&mutex_l);
        printf("Погрузчик положил в магазин %d: столько %d\n", *number_store + 1, content);
        print(args);
        sleep(3);
    }
}

int main()
{
    int *store = (int*)malloc(5 * sizeof(int));
    init_store(store);
    print(store);

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex_l, NULL);

    pthread_t thread_buy_1;
    pthread_t thread_buy_2;
    pthread_t thread_buy_3;
    pthread_t thread_loader;

    int status;
    pthread_create(&thread_loader, NULL, loader_main, (void *) store);
    pthread_create(&thread_buy_1, NULL, buy_main, (void *) store);
    pthread_create(&thread_buy_2, NULL, buy_main, (void *) store);
    pthread_create(&thread_buy_3, NULL, buy_main, (void *) store);

    pthread_join(thread_buy_1, (void**)&status);
    pthread_join(thread_buy_2, (void**)&status);
    pthread_join(thread_buy_3, (void**)&status);
    pthread_cancel(thread_loader);

    printf("joined with address %d\n", status);

    return 0;
}
