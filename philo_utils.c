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

long get_current_time()
{
    long time;
    struct timeval tv;

    gettimeofday(&tv,NULL);
    time = tv.tv_usec / 1000 + tv.tv_sec * 1000;
    return time;
}

t_info *set_starttime(t_info *info)
{
    info->start_time = get_current_time();
    return info;
}

long now_time(t_info *info)
{
    long time;

    time = get_current_time() - info->start_time;
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
