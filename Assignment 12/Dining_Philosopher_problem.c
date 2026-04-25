//Simulate the Dinning Philosophers problem using multi-threading in Linux.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 5 

pthread_mutex_t forks[N]; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void *philosopher(void *arg) {
    int id = *(int *)arg;

    while (1) {
        printf("Philosopher %d is Thinking\n", id);
        sleep(1);

        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % N]);
        pthread_mutex_unlock(&mutex);

        printf("Philosopher %d is Eating\n", id);
        sleep(2);

        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i + 1;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
