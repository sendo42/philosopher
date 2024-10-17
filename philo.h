#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

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

//共有してるのはinfo
/*
共有資源ができた
右手と左手の両方が使えそうなら取る

右手と左手に、共有資源で確保したforksの配列を与える


*/