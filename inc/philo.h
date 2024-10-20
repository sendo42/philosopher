#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>


typedef struct s_info
{
    long start_time;

    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_philo;
    int num_must_eat;

    bool is_dead;
    bool is_full;

    pthread_mutex_t dead;
    pthread_mutex_t *pfork;
    pthread_mutex_t print;
} t_info;

typedef struct s_pman
{
    pthread_t tid;
    int philo_id;
    int rfork;
    int lfork;
    t_info *info;
    
    long last_eattime;
    int count_eat;
    bool is_fulleat;

    pthread_mutex_t last_time;
} t_pman;

// pfork[rfork]
// pfork[lfork]

//どうやって共有資源を作るのか？

//前処理
t_info *set_starttime(t_info *info);
t_info *store_rule (t_info *info, int ac, char **av);
long now_time(t_info *info);
void wait_tid(t_pman *pmans);
long get_current_time();
void    ft_msleep(long time);
void observe(t_pman *pmans);

void monitor_end(t_pman *pman);

bool is_full_eat(t_pman *pman);
bool is_died(t_pman *pman);
void *lonely_stop(t_pman *pman);
void p_think(t_pman *pman);


bool check_input(int ac, char **av);

// main.c
void *dining_algo(void *args);

// observe.c

bool is_hold_die(int time_to_die, long last_eattime);
bool is_died(t_pman *pman);
bool is_full_eat(t_pman *pman);
bool is_anyone_dead(t_pman *pman);
void monitor_end(t_pman *pman);

// philo_action.c
void take_fork(t_pman *pman);
void p_eat(t_pman *pman);
void p_think(t_pman *pman);
void p_sleep(t_pman *pman);



// philo_init.c
t_pman *start_pmans(t_pman *pmans, char **av);
t_pman *pman_setrule (int ac, char **av);
t_pman *pman_init(int ac, char **av);



// check_input.c
bool check_input(int ac, char **av);

// philo_utils.c
void    print_message(const char *msg, t_pman *pman);
void printable(t_pman *pman);



//共有してるのはinfo
/*
共有資源ができた
右手と左手の両方が使えそうなら取る

右手と左手に、共有資源で確保したforksの配列を与える

死んだかどうかを判断する。各ピーマンの構造体に最後にくった時間の時間を格納するか

一回死んだかどうかをメインスレッドで10ms以内に判断できるかを試す。
もしだめそうならそれぞれをスレッドで監視する


死亡フラグを立てる。
死亡フラグを参照して、printしていいかを判断する

そもそも食べさせないとか寝させないで終了させるのもよき

何回食べたかみたいなやつを全員分用意し、それが終わったら終了させるやつも必要

なぜeatingやhas taken a forkがされないときがあるのか？

*/

// void take_rfork(t_pman *pman)
// {
//     // printf("philo_id %i rfork %i lfork %i last eattime %li\n",pman->philo_id, pman->rfork,pman->lfork,get_current_time() - pman->last_eattime);
//     pthread_mutex_lock(&pman->info->pfork[pman->rfork]);
//     pthread_mutex_lock(&pman->info->print);
//     myprintf(pman->info,pman->philo_id, pman->is_dead, "has taken a fork\n");
//     // pman->last_eattime = get_current_time();
// }
// void take_lfork(t_pman *pman)
// {
//     pthread_mutex_lock(&pman->info->pfork[pman->lfork]);
//     myprintf(pman->info,pman->philo_id, pman->is_dead, "has taken a fork\n");
//     pthread_mutex_unlock(&pman->info->print);
// }

// void handoff(pthread_mutex_t *pfork, int fork_id)
// {
//     pthread_mutex_unlock(&pfork[fork_id]);
// }

// void p_eat(t_pman *pman)
// {   
//     take_rfork(pman);
//     take_lfork(pman);
//         pman->last_eattime = get_current_time();
//         myprintf(pman->info,pman->philo_id, pman->is_dead, "is eating\n");
//         pman->count_eat++;
//         ft_msleep(pman->info->time_to_eat);
//     handoff(pman->info->pfork, pman->rfork);
//     handoff(pman->info->pfork, pman->lfork);
//     // pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);
//     // pthread_mutex_unlock(&pman->info->pfork[pman->lfork]);
// }

// void take_fork(t_pman *pman)
// {
//     // printf("philo_id %i rfork %i lfork %i last eattime %li\n",pman->philo_id, pman->rfork,pman->lfork,get_current_time() - pman->last_eattime);
//     pthread_mutex_lock(&pman->info->pfork[pman->rfork]);
//     myprintf(pman->info,pman->philo_id, pman->is_dead, "has taken a fork\n");
//     pthread_mutex_lock(&pman->info->pfork[pman->lfork]);
//     pman->last_eattime = get_current_time();
//     myprintf(pman->info,pman->philo_id, pman->is_dead, "has taken a fork\n");
//     myprintf(pman->info,pman->philo_id, pman->is_dead, "is eating\n");
//     ft_msleep(pman->info->time_to_eat);
//     // pman->last_eattime = get_current_time();
//     pthread_mutex_unlock(&pman->info->pfork[pman->lfork]);
//     pthread_mutex_unlock(&pman->info->pfork[pman->rfork]);
//     pman->count_eat++;
// }

// void p_eat(t_pman *pman)
// {   
//     take_fork(pman);
// }

//いまさら理解したが、たんに囲めばいいというわけじゃない。
//mutexは共有していて初めて意味をなす。
//printのやつも、混線しないように、みんなでprintしていいかの変数の共有を行って、解放されたらだす