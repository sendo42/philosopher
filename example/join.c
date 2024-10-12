#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
int counter = 0;

void *threadFunc1(void *arg) {
    printf("1 start\n");
    for(int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    printf("1 end\n");
    
    return NULL;
}

void *threadFunc2(void *arg) {
    printf("2 start\n");
    for(int i = 0; i < 50000; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
        printf("2 end\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread1, NULL, threadFunc1, NULL);
    pthread_create(&thread2, NULL, threadFunc2, NULL);
    printf("Final Counter: %d\n", counter);//こいつどこにくるかわからん
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex);
    // printf("Final Counter: %d\n", counter);//だからこいつはpthread_joinでちゃんと待ってから

    return 0;
}

//複数のスレッドが全部足し終わるのを全てのスレッドで待ち表示するやつ

// #include <stdio.h>
// #include <pthread.h>

// #define NTHREADS 10
// void *thread_function(void *);
// pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// int  counter = 0;

// main()
// {
//    pthread_t thread_id[NTHREADS];
//    int i, j;

//    for(i=0; i < NTHREADS; i++)
//    {
//       pthread_create( &thread_id[i], NULL, thread_function, NULL );
//    }

//    for(j=0; j < NTHREADS; j++)
//    {
//       pthread_join( thread_id[j], NULL); 
//    }
  
//    /* Now that all threads are complete I can print the final result.     */
//    /* Without the join I could be printing a value before all the threads */
//    /* have been completed.                                                */

//    printf("Final counter value: %d\n", counter);
// }

// void *thread_function(void *dummyPtr)
// {
//    printf("Thread number %ld\n", pthread_self());
//    pthread_mutex_lock( &mutex1 );
//    counter++;
//    pthread_mutex_unlock( &mutex1 );
// }