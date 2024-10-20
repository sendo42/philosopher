#include "philo.h"

t_pman *start_pmans(t_pman *pmans, char **av)
{
    int i;
    int num;

    i = 0;
    num = atoi(av[1]);
    while(i < num)
    {
        pmans[i].philo_id = i;
        if(i == 0)
            pmans[i].rfork = num - 1;
        else
            pmans[i].rfork = i - 1;
        pmans[i].lfork = i;
        pmans[i].last_eattime = get_current_time();
        pmans[i].count_eat = 0;
        pmans[i].is_fulleat = 0;
        pthread_create(&pmans[i].tid, NULL, dining_algo, &pmans[i]);
        i++;
    }
    monitor_end(pmans);
    wait_tid(pmans);
    return pmans;
}

t_pman *pman_setrule (int ac, char **av)
{
    int num;
    t_pman *pmans;
    t_info *info;
    int i;

    i = 0;
    num = atoi(av[1]);
    pmans = malloc(sizeof(t_pman) * num);
    info = malloc(sizeof(t_info));
    info->pfork = malloc(sizeof(pthread_mutex_t) * num);
    info = store_rule(info, ac, av);
    info = set_starttime(info);
    
    while (i < num)
    {
        pmans[i].info = info;
        i++;
    }

    return pmans;
}

t_pman *pman_init(int ac, char **av)
{
    t_pman *pmans;
    int i;

    i = 0;
    pmans = pman_setrule(ac, av);
    while(i < pmans->info->num_philo)
    {
        pthread_mutex_init(&pmans->info->pfork[i], NULL);
        pthread_mutex_init(&pmans[i].last_time, NULL);
        i++;
    }
    pthread_mutex_init(&pmans->info->print, NULL);
    pthread_mutex_init(&pmans->info->dead, NULL);

    return pmans;
}