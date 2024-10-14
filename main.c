#include "philo.h"


void *dining_algo(void *args)
{
    t_pman *pman;

    pman = (t_pman *)args;
    
    pthread_mutex_lock(&pman->info->print);
    printf("address for &pman->info.print [%p]\n", &pman->info->print);
    printf("I am %i philo\n", pman->philo_id);
    now_time(pman->info);
    pthread_mutex_unlock(&pman->info->print);
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
    info->forks = malloc(sizeof(pthread_mutex_t) * num);
    info = store_rule(info, av);
    info = set_starttime(info);
    
    while (i < num)
    {
        pmans[i].philo_id = i;
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
        pthread_mutex_init(&pmans->info->forks[i], NULL);
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

