#include "philo.h"

t_info *store_rule (t_info *info, char **av)
{
    info->num_philo = atoi(av[1]);
    info->time_to_die = atoi(av[2]);
    info->time_to_eat = atoi(av[3]);
    info->time_to_sleep = atoi(av[4]);
    info->num_must_eat = atoi(av[5]);
    return info;
}

t_info *set_starttime(t_info *info)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    info->start_time = tv.tv_usec;
    // printf("%i\n",info.start_time);
    return info;
}

long now_time(t_info *info)
{
    struct timeval tv;
    long time;

    gettimeofday(&tv,NULL);
    time = tv.tv_usec - info->start_time;
    printf("the time is %lims\n",time);
    return time;
}

void wait_tid(t_pman *pmans, int num)
{
    int i;

    i = 0;
    while(i < num)
    {
        pthread_join(pmans[i].tid ,NULL);
        i++;
    }
}
