#include "philo.h"

void take_fork(t_pman *pman)
{
    pthread_mutex_lock(&pman->info->pfork[pman->rfork]);
    if(pman->info->is_dead == true)
    {
        pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);
        return ;
    }
    else
        printf("%li %i has taken a fork\n",now_time(pman->info),pman->philo_id);
    pthread_mutex_lock(&pman->info->pfork[pman->lfork]);
    pthread_mutex_lock(&pman->last_time);
    pman->last_eattime = get_current_time();
    pthread_mutex_unlock(&pman->last_time);
    if(pman->info->is_dead == true)
    {
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

void p_sleep(t_pman *pman)
{
    if(pman->info->is_dead == 0)
    {
        pthread_mutex_lock(&pman->info->print);
        printf("%li %i is sleeping\n",now_time(pman->info),pman->philo_id);
        pthread_mutex_unlock(&pman->info->print);
    }
    else
        return ;
    ft_msleep(pman->info->time_to_sleep);

}