#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "./c_file/include/store.h"
#include "./c_file/include/loader.h"
#include "./c_file/include/buyer.h"

#define COUNT 2

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;
pthread_mutex_t mutex4;
pthread_mutex_t mutex5;

struct store_number{
    int *store;
    int num_b[COUNT]; 
};

void print(int *store)
{
    for(int i = 0; i < 5; i++){
        printf("%d\t", store[i]);
    }
    printf("\n");
}

void* buy_main(void *arg)
{
    struct store_number *args = (struct store_number*) arg;
    int *content_buyer = (int*)malloc(1 * sizeof(int));

    int s_num = -1;
    while(s_num == -1){
        for(int i = 0; i <= COUNT; i++){
            if(args->num_b[i] != 0){
                s_num = args->num_b[i];
                args->num_b[i] = 0;
                break;
            }else{
                continue;
            }
        }
    }

    init_buyer(content_buyer);
    printf("Лимит покупатель %d : %d\n", s_num, *content_buyer);

    while(*content_buyer > 0){
      	int store_b = store_select_buyer();
        switch(store_b){
            case 0:
                pthread_mutex_lock(&mutex1);
                buy(content_buyer, args->store, store_b);
                pthread_mutex_unlock(&mutex1);
                break;
            case 1:
                pthread_mutex_lock(&mutex2);
                buy(content_buyer, args->store, store_b);
                pthread_mutex_unlock(&mutex2);
                break;
            case 2:
                pthread_mutex_lock(&mutex3);
                buy(content_buyer, args->store, store_b);
                pthread_mutex_unlock(&mutex3);
                break;
            case 3:
                pthread_mutex_lock(&mutex4);
                buy(content_buyer, args->store, store_b);
                pthread_mutex_unlock(&mutex4);
                break;
            case 4:
                pthread_mutex_lock(&mutex5);
                buy(content_buyer, args->store, store_b);
                pthread_mutex_unlock(&mutex5);
                break;
        }
        printf("Покупатель %d забрал из магазина %d: его лимит %d\n", s_num, store_b + 1, *content_buyer);
        sleep(3);
    }
    return 0;
}

void* loader_main(void *arg)
{
    struct store_number *args = (struct store_number*) arg;
    int number_store = 6;
    int content;

    while(1){
        number_store = store_selection();
        switch(number_store){
            case 0:
                pthread_mutex_lock(&mutex1);
                content = working(args->store, number_store);
                pthread_mutex_unlock(&mutex1);
                break;
            case 1:
                pthread_mutex_lock(&mutex2);
                content = working(args->store, number_store);
                pthread_mutex_unlock(&mutex2);
                break;
            case 2:
                pthread_mutex_lock(&mutex3);
                content = working(args->store, number_store);
                pthread_mutex_unlock(&mutex3);
                break;
            case 3:
                pthread_mutex_lock(&mutex4);
                content = working(args->store, number_store);
                pthread_mutex_unlock(&mutex4);
                break;
            case 4:
                pthread_mutex_lock(&mutex5);
                content = working(args->store, number_store);
                pthread_mutex_unlock(&mutex5);
                break;
            default :
                printf("???\n");
        }
        printf("Погрузчик положил в магазин %d: столько %d\n", number_store + 1, content);
        print(args->store);
        sleep(3);
    }
}

int main()
{
    struct store_number *help;
    help = (struct store_number*)malloc(sizeof(*help));
    help->store = (int*)malloc(5 * sizeof(int));

    init_store(help->store);
    print(help->store);
    for(int i = 0; i <= COUNT; i++){
        help->num_b[i] = i + 1;
    }

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_mutex_init(&mutex3, NULL);
    pthread_mutex_init(&mutex4, NULL);
    pthread_mutex_init(&mutex5, NULL);

    pthread_t thread_buy_1;
    pthread_t thread_buy_2;
    pthread_t thread_buy_3;
    pthread_t thread_loader;

    int status;
    pthread_create(&thread_loader, NULL, loader_main, help);
    pthread_create(&thread_buy_1, NULL, buy_main, help);
    pthread_create(&thread_buy_2, NULL, buy_main, help);
    pthread_create(&thread_buy_3, NULL, buy_main, help);

    pthread_join(thread_buy_1, (void**)&status);
    pthread_join(thread_buy_2, (void**)&status);
    pthread_join(thread_buy_3, (void**)&status);
    pthread_cancel(thread_loader);

    return 0;
}
