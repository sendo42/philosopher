#include "philo.h"

void printable(t_pman *pman)
{
    pthread_mutex_lock(&pman->info->print);
    printf("%li %i has taken a fork\n",now_time(pman->info),pman->philo_id);
    pthread_mutex_unlock(&pman->info->print);
}

void    print_message(const char *msg, t_pman *pman)
{
    pthread_mutex_lock(&pman->info->print);
    pthread_mutex_lock(&pman->info->dead);
    if (pman->info->is_dead == false)
        printf("%ld %d %s\n", now_time(pman->info),
            pman->philo_id, msg);
    pthread_mutex_unlock(&pman->info->dead);
    pthread_mutex_unlock(&pman->info->print);
}

t_info *store_rule (t_info *info, int ac, char **av)
{
    info->num_philo = atoi(av[1]);
    info->time_to_die = atoi(av[2]);
    info->time_to_eat = atoi(av[3]);
    info->time_to_sleep = atoi(av[4]);
    if(ac == 6)
        info->num_must_eat = atoi(av[5]);
    // printf("num_must_eat %i\n",info->num_must_eat);
    return info;
}

long get_current_time()
{
    long time;
    struct timeval tv;

    gettimeofday(&tv,NULL);
    time = tv.tv_usec / 1000 + tv.tv_sec * 1000;
    //https://labo.utsubopeo.com/archives/915
    //https://funini.com/kei/c/time.shtml m秒に変換
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

void wait_tid(t_pman *pmans)
{
    int i;

    i = 0;
    while(i < pmans->info->num_philo)
    {
        pthread_join(pmans[i].tid ,NULL);
        i++;
    }
}

// void myprintf(t_info *info,int philo_id, bool is_dead, char *str)
// {
//     if(is_dead != true)
//     {
//         pthread_mutex_lock(&info->print);
//             printf("%li %i %s",now_time(info),philo_id, str);
//         pthread_mutex_unlock(&info->print);
//     }
// }//これはわかってないやつ、ちがうやろ