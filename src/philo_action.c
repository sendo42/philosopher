#include "philo.h"

void take_fork(t_pman *pman)
{
    // ロック順序の一貫性を保つ
    pthread_mutex_lock(&pman->info->dead);
    if(pman->info->is_dead == true)
    {
        pthread_mutex_unlock(&pman->info->dead);
        return ;
    }
    pthread_mutex_unlock(&pman->info->dead);

    // 右のフォークを取る
    pthread_mutex_lock(&pman->info->pfork[pman->rfork]);
    printf("%li %i has taken a fork\n", now_time(pman->info), pman->philo_id);

    // 左のフォークを取る
    pthread_mutex_lock(&pman->info->pfork[pman->lfork]);
    pthread_mutex_lock(&pman->last_time);
    pman->last_eattime = get_current_time();
    pthread_mutex_unlock(&pman->last_time);
    pthread_mutex_lock(&pman->info->print);
    printf("%li %i has taken a fork\n", now_time(pman->info), pman->philo_id);
    printf("%li %i is eating\n", now_time(pman->info), pman->philo_id);
    pthread_mutex_unlock(&pman->info->print);
    // 食事のためのスリープ
    ft_msleep(pman->info->time_to_eat);

    // フォークを戻す
    pthread_mutex_unlock(&pman->info->pfork[pman->lfork]);
    pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);

    // 食事回数のカウント
    pman->count_eat++;
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
    pthread_mutex_lock(&pman->info->dead);
    if(pman->info->is_dead == 0)
    {
        pthread_mutex_unlock(&pman->info->dead);
        pthread_mutex_lock(&pman->info->print);
        printf("%li %i is sleeping\n",now_time(pman->info),pman->philo_id);
        pthread_mutex_unlock(&pman->info->print);
    }
    else
    {
        pthread_mutex_unlock(&pman->info->dead);
        return ;
    }
    ft_msleep(pman->info->time_to_sleep);

}