#include <unistd.h>
#include <pthread.h>

typedef struct t_rule 
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_philo;
    int num_must_eat;
} s_rule;

typedef struct t_info
{
    s_rule rule;
    pthread_t *philo;
    int *fork;
    int *each_life;
    int time;
    int start_time;
} s_info;


