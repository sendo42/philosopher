#include "philo.h"

void *lonely_stop(t_pman *pman)
{
    p_think(pman);
    printf("%li %i has taken a fork\n",now_time(pman->info),pman->philo_id);
    ft_msleep(pman->info->time_to_die);
    
    return NULL;
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

void *dining_algo(void *args)
{
    t_pman *pman;

    pman = (t_pman *)args;
    if(pman->info->num_philo == 1)
        return lonely_stop(pman);
    if((pman->philo_id + 1) % 2 == 0)
    {
        usleep(pman->info->time_to_eat / 2);//これ10とかだと全然入れ替わって死ぬ
        // printf("I am %i\n",pman->philo_id);x
    }
    while(1)
    {
        p_think(pman);
        pthread_mutex_lock(&pman->info->dead);
        if(pman->info->is_dead == true || pman->info->is_full == true)
        {
            // printf("pman->is_dead = %i\n",pman->info->is_dead);
            // printf("pman is fulleat = %i\n",pman->info->is_full);
            // printf("count eat = %i \n",pman->count_eat);
            pthread_mutex_unlock(&pman->info->dead);
            break;
        }
        pthread_mutex_unlock(&pman->info->dead);
        p_eat(pman);
        pthread_mutex_lock(&pman->info->dead);
        if(pman->info->is_dead == true || pman->info->is_full == true)
        {
            // printf("pman->is_dead = %i\n",pman->info->is_dead);
            // printf("pman is fulleat = %i\n",pman->info->is_full);
            // printf("count eat = %i \n",pman->count_eat);
            pthread_mutex_unlock(&pman->info->dead);
            break;
        }
        pthread_mutex_unlock(&pman->info->dead);
        p_sleep(pman);
        pthread_mutex_lock(&pman->info->dead);
        if(pman->info->is_dead == true || pman->info->is_full == true)
        {
            // printf("pman->is_dead =%i\n",pman->info->is_dead);
            // printf("pman is fulleat = %i\n",pman->info->is_full);
            // printf("count eat = %i \n",pman->count_eat);
                pthread_mutex_unlock(&pman->info->dead);
            break;
        }
        pthread_mutex_unlock(&pman->info->dead);

    }
    return NULL;
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
