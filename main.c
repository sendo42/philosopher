#include "philo.h"

void take_fork(t_pman *pman)
{
    pthread_mutex_lock(&pman->info->pfork[pman->rfork]);
        printf("%li %i has taken a fork\n",now_time(pman->info),pman->philo_id);
    pthread_mutex_lock(&pman->info->pfork[pman->lfork]);
        printf("%li %i has taken a fork\n",now_time(pman->info),pman->philo_id);
        printf("%li %i is eating\n",now_time(pman->info),pman->philo_id);
        ft_msleep(pman->info->time_to_eat);
    pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);
    pthread_mutex_unlock(&pman->info->pfork[pman->lfork]);

}

void p_eat(t_pman *pman)
{   
    take_fork(pman);
}

void p_think(t_pman *pman)
{
    printf("%li %i is thinking\n",now_time(pman->info),pman->philo_id);
}

void    ft_msleep(long time)
{
    long    end_time;

    end_time = get_current_time() + time;
    while (end_time > get_current_time())
    {
        usleep((end_time - get_current_time()) / 4 * 1000);
    }
}

void p_sleep(t_pman *pman)
{
    printf("%li %i is sleeping\n",now_time(pman->info),pman->philo_id);
    ft_msleep(pman->info->time_to_sleep);

}

void *dining_algo(void *args)
{
    t_pman *pman;
    int i;

    i = 0;
    pman = (t_pman *)args;
    
    if(pman->info->num_philo % 2 == 0 && pman->philo_id % 2 == 0)
    {
        usleep(500);
    }
    while(1)
    {
        p_think(pman);
        p_eat(pman);
        p_sleep(pman);
        i++;
    }
    return NULL;
}

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
        pthread_create(&pmans[i].tid, NULL, dining_algo, &pmans[i]);
        i++;
    }
    wait_tid(pmans, num);
    return pmans;
}

t_pman *pman_setrule (char **av)
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
    info->forks = malloc(sizeof(int) * num);
    info = store_rule(info, av);
    info = set_starttime(info);
    
    while (i < num)
    {
        pmans[i].info = info;
        i++;
    }

    return pmans;
}

//メモリを確保し、ルールを代入
t_pman *pman_init(char **av)
{
    t_pman *pmans;
    int i;

    i = 0;
    pmans = pman_setrule(av);
    while(i < atoi(av[1]))
    {
        pthread_mutex_init(&pmans->info->pfork[i], NULL);
        i++;
    }
    pthread_mutex_init(&pmans->info->print, NULL);

    return pmans;
}

// 引数が5つ以外は終わるやつは終了。init関数に渡す
int main(int ac, char **av)
{
    t_pman *pmans;

    if(ac == 6)
    {
        pmans = pman_init(av);
        pmans = start_pmans(pmans, av);

    //joinfree;//スレッドの終わりを待ち、解放


    }
}


// void *dining_algo(void *args)
// {
//     t_pman *pman;

//     pman = (t_pman *)args;
    
//     pthread_mutex_lock(&pman->info->print);
//     printf("address for &pman->info.print [%p]\n", &pman->info->print);
//     printf("I am %i philo, I have joycon r = %i[%p] l = %i[%p]\n", pman->philo_id, pman->rfork, &pman->rfork, pman->lfork, &pman->lfork);
//     printf("pman->info->rfork%p\npman->info->lfork%p\n",&pman->info->forks[pman->rfork],&pman->info->forks[pman->lfork]);
//     now_time(pman->info);
//     pthread_mutex_unlock(&pman->info->print);
//     return NULL;
// }
