#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_info
{
    int *fork;
    int *each_life;
    int time;
    int start_time;

    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_philo;
    int num_must_eat;

    pthread_mutex_t *forks;
    pthread_mutex_t print;
} t_info;

typedef struct s_pman
{
    pthread_t tid;
    int philo_id;
    t_info *info;
} t_pman;

//どうやって共有資源を作るのか？

//前処理
t_info *set_starttime(t_info *info);
t_info *store_rule (t_info *info, char **av);
long now_time(t_info *info);
void wait_tid(t_pman *pmans, int num);

//共有してるのはinfo
//