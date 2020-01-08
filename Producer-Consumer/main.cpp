#include <semaphore.h>
#include <cstring>
#include <cstdio>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


pthread_mutex_t lock;
pthread_t tid[7];
sem_t producerSem;
sem_t concumerSem;

int BUFFER[N];

void * producerFunc(void * v)
{
    for(int i = 0; i < 40; ++i)
    {
        sem_wait(&producerSem);       /* down semaphore */
        pthread_mutex_lock(&lock);
        
        int r = rand() % 1000000;
        printf("producer %d\n", r);
        
        pthread_mutex_unlock(&lock);
        sem_post(&concumerSem);       /* up semaphore */
    }
    return NULL;
}

void * consumerFunc(void * v)
{
    for(int i = 0; i < 30; ++i)
    {
        sem_wait(&concumerSem);       /* down semaphore */
        pthread_mutex_lock(&lock);
        int r = rand() % 1000000;
        printf("consumer %d\n", r);
        pthread_mutex_unlock(&lock);
        sem_post(&producerSem);       /* up semaphore */
    }
    return NULL;
}


int main()
{
    sem_init(&producerSem, 0, 6);
    sem_init(&concumerSem, 0, 0);
    int i = 0;
    int err;
    
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    
    while(i < 3)
    {
        err = pthread_create(&tid[i], NULL, producerFunc, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    
    while(i < 7)
    {
        err = pthread_create(&tid[i], NULL, consumerFunc, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    
    for( i = 0; i < 7; ++i)
    {
        pthread_join(tid[i],NULL);
    }
    
    sem_destroy(&producerSem);
    sem_destroy(&concumerSem);
    pthread_mutex_destroy(&lock);
    
    return 0;
}
