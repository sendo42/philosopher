#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


void *dining_algo(void *info_v)
{
    s_info *info_s;
    struct timeval tv;
    long time;

    info_s = (s_info *)info_v;
    gettimeofday(&tv,NULL);
    time = tv.tv_usec 
    - info_s->start_time;
    printf("time_to_die = %li\n",time);
    
    
    return NULL;
}

s_rule store_rule (char **av)
{
    s_rule rule;

    rule.num_philo = atoi(av[1]);
    rule.time_to_die = atoi(av[2]);
    rule.time_to_eat = atoi(av[3]);
    rule.time_to_sleep = atoi(av[4]);
    rule.num_must_eat = atoi(av[5]);

    return rule;
}


void wait_tid(s_info info)
{
    int i;

    i = 0;
    while(i < info.rule.num_philo)
    {
        pthread_join(info.philo[i],NULL);
        i++;
    }
}

s_info get_time(s_info info)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    info.start_time = tv.tv_usec;
    // printf("%i\n",info.start_time);
    return info;
}

s_info sit_philo(s_info info)
{
    int i;

    i = 0;
    printf("num philo= %i\n",info.rule.num_philo);
    while(i < info.rule.num_philo)
    {
        pthread_create(&info.philo[i],NULL,dining_algo,&info);
        // printf("neko\n");
        i++;
    }
    wait_tid(info);
    return info;
}

int main(int ac, char** av)
{
    int i;
    s_info info;

    i = 0;
    if(ac > 5)
    {
        info = get_time(info);
        info.rule = store_rule(av);
        sit_philo(info);
        // printf("num philo %i\n",rule.num_philo);
    }
}







// void *observe_philo(s_box philo_info)
// {
//     pthread_mutex_t mutex;

//     pthread_mutex_init(&mutex, NULL);
//     while(1)
//     {
//         if(philo_info.fork[1] == 0 && philo_info.fork[0] == 0)
//         {
//             philo_info.fork[1] = 1;
//             philo_info.fork[0] = 1;
//             pthread_mutex_lock(&mutex);
//             printf("time is %i, I am ",philo_info.time);
//             philo_info.time = philo_info.time + 10;
//             usleep(10);
//             pthread_mutex_unlock(&mutex);
//             philo_info.fork[1] = 0;
//             philo_info.fork[0] = 0;
//         }
//         if(philo_info.time > 500)
//             break;
//     }


//     return 0;
// }

// int sit_philo(int num, s_box philo_info)
// {
//     pthread_t philo[num];
//     int i;

//     i = 0;
//     while(i < 2)
//     {
//         pthread_create(&philo[i],NULL,observe_philo,&philo_info);
//         i++;
//     }
//     return 0;
// }

// int main(int ac ,char **av)
// {
//     int i;
//     s_box philo_info;

//     i = 0;
//     philo_info.fork[0] = 0;
//     philo_info.fork[1] = 0;/*人数文を増やすので、たぶんここで構造体をmallocしておきたい*/
//     philo_info.time_to_eat = 100; 
//     philo_info.time = 0;
//     sit_philo(ac, philo_info);

// }