//Simulate the  Reader - Writer problem using multi-threading in Linux.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;      
pthread_mutex_t wrt;        
int read_count = 0;
void *reader(void *arg) {
    int id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&wrt); 
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader %d is reading\n", id);
    sleep(1);
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&wrt); 
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader %d finished reading\n", id);
    return NULL;
}
void *writer(void *arg) {
    int id = *((int *)arg);
    pthread_mutex_lock(&wrt);
    printf("Writer %d is writing\n", id);
    sleep(2);
    pthread_mutex_unlock(&wrt);
    printf("Writer %d finished writing\n", id);
    return NULL;
}
int main() {
    pthread_t r[5], w[2];
    int i, ids[5];
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);
    for (i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &ids[i]);
    }
    for (i = 0; i < 2; i++) {
        ids[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &ids[i]);
    }
    for (i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }
    for (i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);
    return 0;
}


