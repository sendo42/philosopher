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




*/





bool is_died(t_pman *pman)
{
    if(pman->info->time_to_die < get_current_time() - pman->last_eattime)
        return true;
    else
        return false;
}

bool search_dead(t_pman *pman)
{
    int i;
    int death_flag;

    i = 0;
    death_flag = 0;
    while(i < pman->info->num_philo)
    {
        death_flag = is_died(&pman[i]);
        i++;
    }
    return death_flag;
}

void set_all_died(t_pman *pman)
{
    int i;

    i = 0;

    while(i < pman->info->num_philo)
    {
        pman->is_dead = 1;
        i++;
    }
}

void monitor_dead(t_pman *pman)
{
    while(1)
    {
        if(search_dead(pman))
            set_all_died(pman);
        break;
    }
}




void observe(t_pman *pmans, char **av)
{
    int i;
    long time_to_die;
    int philo_num;

    i = 0;
    philo_num = atoi(av[1]);
    time_to_die = atoi(av[2]);
    // printf("last_eattime = %li\n",pmans[i].last_eattime);
    // printf("now_time = %li\n", get_current_time());
    // printf("time_to die %li, now time is %li\n",time_to_die, get_current_time() - pmans[i].last_eattime);


    while(1)
    {
        // printf("time_to die %li, now time is %li\n",time_to_die, get_current_time() - pmans[i].last_eattime);
        if(time_to_die < get_current_time() - pmans[i].last_eattime)
        {
            printf("philo %i last_eattime = %li\n",pmans[i].philo_id, pmans[i].last_eattime);
            printf("now_time = %li\n", get_current_time());
            printf("time_to die %li, now time is %li\n",time_to_die, get_current_time() - pmans[i].last_eattime);
            printf("\x1b[31m%li %i died\n",now_time(pmans->info),i);
            i = (i % philo_num) + 1;
            break;
        }
    }
}

