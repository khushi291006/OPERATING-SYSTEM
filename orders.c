
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TOTAL_ORDERS 5

volatile int order = 0;       
volatile int order_ready = 0;  

void* take_orders(void* arg) {
    for (int i = 1; i <= TOTAL_ORDERS; i++) {
        while (order_ready == 1) {
            usleep(1000);
        }

        order = i;
        order_ready = 1; 
        printf("Taken Order-%d\n", i);
        
        usleep(500000); 
    }
    return NULL;
}

void* prepare_food(void* arg) {
    int prepared = 0;
    while (prepared < TOTAL_ORDERS) {
        if (order_ready == 1) {
            printf("Preparing Order-%d\n", order);

            usleep(1000000); 

            printf("Order-%d prepared\n", order);

            order_ready = 0; 
            prepared++;
        } else {
            usleep(1000);
        }
    }
    return NULL;
}

int main() {
    pthread_t thread_take, thread_prepare;

    pthread_create(&thread_take, NULL, take_orders, NULL);
    pthread_create(&thread_prepare, NULL, prepare_food, NULL);

    pthread_join(thread_take, NULL);
    pthread_join(thread_prepare, NULL);

    printf("All orders processed.\n");
    return 0;
}
