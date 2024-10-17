#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_info
{
    int *forks;
    int *each_life;
    int time;
    long start_time;

    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_philo;
    int num_must_eat;

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
    bool is_dead;
} t_pman;

// pfork[rfork]
// pfork[lfork]

//どうやって共有資源を作るのか？

//前処理
t_info *set_starttime(t_info *info);
t_info *store_rule (t_info *info, char **av);
long now_time(t_info *info);
void wait_tid(t_pman *pmans, int num);
long get_current_time();
void    ft_msleep(long time);
void observe(t_pman *pmans, char **av);


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



*/