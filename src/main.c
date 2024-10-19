#include "philo.h"

void take_fork(t_pman *pman)
{
    // printf("philo_id %i rfork %i lfork %i last eattime %li\n",pman->philo_id, pman->rfork,pman->lfork,get_current_time() - pman->last_eattime);
    pthread_mutex_lock(&pman->info->pfork[pman->rfork]);
    if(pman->info->is_dead == true)
    {
        // pthread_mutex_unlock(&pman->info->print);
        pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);
        return ;
    }
    else
        printf("%li %i has taken a fork\n",now_time(pman->info),pman->philo_id);
    pthread_mutex_lock(&pman->info->pfork[pman->lfork]);
    pman->last_eattime = get_current_time();
    if(pman->info->is_dead == true)
    {
        // pthread_mutex_unlock(&pman->info->print);
        pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);
        return ;
    }
    else
    {
    pthread_mutex_lock(&pman->info->print);
        printf("%li %i has taken a fork\n",now_time(pman->info),pman->philo_id);
        printf("%li %i is eating\n",now_time(pman->info),pman->philo_id);
    pthread_mutex_unlock(&pman->info->print);
    }
    ft_msleep(pman->info->time_to_eat);
    pthread_mutex_unlock(&pman->info->pfork[pman->lfork]);
    pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);
    pman->count_eat++;
    // printf("count eat = %i\n",pman->count_eat);
}

void p_eat(t_pman *pman)
{   
    take_fork(pman);
}

void p_think(t_pman *pman)
{        
    // printf("pm %i is_dead %i\n",pman->philo_id, pman->info->is_dead);
    // if(pman->info->is_dead == false)
    // {
        // printf("bool %i %i\n",true ,false);
        pthread_mutex_lock(&pman->info->print);
        // pman->info->is_dead = true;
        // printf("pm %i is_dead %i\n",pman->philo_id, pman->info->is_dead);
        printf("%li %i is thinking\n",now_time(pman->info),pman->philo_id);
        pthread_mutex_unlock(&pman->info->print);
    // }
    // else
    //     return ;
}

void    ft_msleep(long time)
{
    //現時点での時間に待ちたい秒数を加えてそこまで待つ。
    //m秒単位に直す
    long    end_time;

    end_time = get_current_time() + time;
    while (end_time > get_current_time())
    {
        usleep(((end_time - get_current_time()) / 4) * 1000);
    }
    
}

void p_sleep(t_pman *pman)
{
    if(pman->info->is_dead == 0)
    {
        // pthread_mutex_lock(&pman->info->print);
        printf("%li %i is sleeping\n",now_time(pman->info),pman->philo_id);
        // pthread_mutex_unlock(&pman->info->print);
    }
    else
        return ;
    ft_msleep(pman->info->time_to_sleep);

}

void *dining_algo(void *args)
{
    t_pman *pman;

    pman = (t_pman *)args;
    if(pman->info->num_philo == 1)
        return lonely_stop(pman);
    if((pman->philo_id + 1) % 2 == 0)
    {
        usleep(300);//これ10とかだと全然入れ替わって死ぬ
        // printf("I am %i\n",pman->philo_id);x
    }
    while(1)
    {
        p_think(pman);
        if(pman->info->is_dead == true || pman->info->is_full == true)
            break;
        p_eat(pman);
        // printf("pman is fulleat = %i\n",pman->info->is_full);
        if(pman->info->is_dead == true || pman->info->is_full == true)
            break;
        p_sleep(pman);
        // printf("pman->is_dead%i\n",pman->is_dead);
        if(pman->info->is_dead == true || pman->info->is_full == true)
        {
            // printf("count eat = %i \n",pman->count_eat);
            break;
        }

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
    info = store_rule(info, av);
    info = set_starttime(info);
    
    while (i < num)
    {
        pmans[i].info = info;
        i++;
    }

    return pmans;
}

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

    if(check_input(ac, av) == true)
    {
        pmans = pman_init(av);
        pmans = start_pmans(pmans, av);
    }
    //joinfree;//スレッドの終わりを待ち、解放


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

