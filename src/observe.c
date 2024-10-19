#include "philo.h"

/*
概要：最後にくった時間からの経過時間を判断し、第二引数のatoiでtime_to_dieで餓死したか否かをwhile(1)で
各スレッドの哲学者ごとに確かめる。

まあbreakさせて終了させるか。

必要なのはpthreadcreate内でpmansそのものとav[2]があればまあ最低限いけるな。

bool is_full_eat(t_pman *pman)
    set
bool is_anyone_died(t_pman *pman)
    set

もしどれかに引っ掛かったら

observeには
- 全員必要な回数たべたかを判断する
    - 全員食べた状態を構造体にぶちこむ
- 餓死の時間を超えちまったか判断する
    - 死んだ状態を構造体にぶち込む

void observe(t_pman *pmans, char **av);

死んだ状態を全部に伝えてスレッドを終わらせたい
    スレッドを終わらせる
        どれかが死んだかを見てひとつでもあてはまれば
            死んだら全部にis_deadを1にする

end_thread

monitor_dead

search_dead

is_died

set_dead

is_hold_die
手に持ったまま志望時間を超えたら強制的に終わらす


*/


bool is_hold_die(int time_to_die, long last_eattime)
{
    if(time_to_die < get_current_time() - last_eattime)
        return true;
    else
        return false;
}

bool is_died(t_pman *pman)
{
    pthread_mutex_lock(&pman->last_time);
    if(pman->info->time_to_die < get_current_time() - pman->last_eattime)
    {
        pthread_mutex_unlock(&pman->last_time);
        return true;
    }
    else {
        pthread_mutex_unlock(&pman->last_time);
        return false;
    }
}

bool is_full_eat(t_pman *pman)
{
    // printf("pman->count_eat = %i must_eat = %i\n",pman->count_eat,pman->info->num_must_eat);
    if(pman->count_eat >= pman->info->num_must_eat + 1)
        return true;
    else
        return false;
}


bool is_anyone_dead(t_pman *pman)
{
    int i;

    i = 0;
    while(i < pman->info->num_philo)
    {
        pthread_mutex_lock(&pman->info->dead);
        pman->info->is_dead = is_died(&pman[i]);
        if(pman->info->is_dead == true)
        {
            pthread_mutex_unlock(&pman->info->dead);
            pthread_mutex_lock(&pman->info->print);
            printf("\x1b[31m%li %i died\n",now_time(pman->info),i);
            pthread_mutex_unlock(&pman->info->print);
            break ;
        }
        else
            pthread_mutex_unlock(&pman->info->dead);        
        i++;
    }
    return pman->info->is_dead;
}

void monitor_end(t_pman *pman)
{
    while(1)
    {
        if(is_anyone_dead(pman) == true)
        {
            break;
        }
        if(pman->info->num_must_eat > 0 && is_full_eat(pman) == true)
        {
            pman->info->is_full = true;
            break ;
        }
        // printf("pman->info->is_dead %i\n",pman->info->is_dead);
        if(pman->info->is_dead == true)
        {
            
            break ;
        }
        // write(1,"a",1);
    }
}

// bool is_full_alleat(t_pman *pman)
// {
//     int i;

//     i = 0;
//     while(i < pman->info->num_philo)
//     {
//         pman[i].info->is_full = is_full_eat(&pman[i]);
//         // printf("is_full %i\n",pman[i].info->is_full);
//         // printf("is_full %i\n",is_full_eat(&pman[i]));
//         if(pman[i].info->is_full == true)
//         {
//             // printf("philo %i last_eattime = %li\n",pman[i].philo_id, pman[i].last_eattime);
//             // printf("now_time = %li\n", get_current_time());
//             // printf("time_to die %i, now time is %li\n",pman->info->time_to_die, get_current_time() - pman[i].last_eattime);
//             // printf("\x1b[31m%li %i died\n",now_time(pman->info),i);
//             break ;
//         }
//         i++;
//     }
//     return true;    
// }


// void set_all_died(t_pman *pman)
// {
//     int i;

//     i = 0;

//     while(i < pman->info->num_philo)
//     {
//         pman[i].is_dead = true;
//         i++;
//     }
// }


// void observe(t_pman *pmans)
// {
//     int i;

//     i = 0;
//     while(1)
//     {
//         if(pmans->info->time_to_die < get_current_time() - pmans[i].last_eattime)
//         {
//             printf("philo %i last_eattime = %li\n",pmans[i].philo_id, pmans[i].last_eattime);
//             printf("now_time = %li\n", get_current_time());
//             printf("time_to die %i, now time is %li\n",pmans->info->time_to_die, get_current_time() - pmans[i].last_eattime);
//             printf("\x1b[31m%li %i died\n",now_time(pmans->info),i);
//             i = (i % pmans->info->time_to_die) + 1;
//             break;
//         }
//     }
// }

