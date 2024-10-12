何をするか


thread系の挙動を知る
    どういう状況でデータの競合やデッドロックをするのかを知る
哲学者問題の概要を知る。
    どういうアルゴリズムで考えればいいのかを知る
    ウェイターの解法でやる。
    
順番的には哲学者問題の解法を知ることが先、そこから進めていった方が必要な関数を浚える


一旦　哲学者　を別々にプリントさせるプログラムを書く


グローバル変数が禁止なので、mallocかstaticのどちらかを使う。

哲学者の数だけスレッドを作る。

この課題は共有資源のデッドロックを避ける問題である

よって、はじめにmallocで作る必要がありそう？








Your(s) program(s) should take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: The number of philosophers and also the number of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

Each philosopher has a number ranging from 1 to number_of_philosophers.
• Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philoso- pher number N + 1.

About the logs of your program:
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork 
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
• A displayed state message should not be mixed up with another message.
• A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
• Again, philosophers should avoid dying!

Program name Turn in files Makefile
Libft authorized Description
philo
Makefile, *.h, *.c, in directory philo/
NAME, all, clean, fclean, re
No
Philosophers with threads and mutexes
Arguments
number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
External functs.
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
The specific rules for the mandatory part are:
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.




小さく始める

簡易的に。まずは2人

2人をするには、スレッドを使って、

まずはスレッドを作る.

持ってるかどうかをどうやって識別するかは、



void *observe_philo(s_box philo_info)
{
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    while(1)
    {
        if(philo_info.fork[1] == 0 && philo_info.fork[0] == 0)
        {
            philo_info.fork[1] = 1;
            philo_info.fork[0] = 1;
            pthread_mutex_lock(&mutex);
            printf("time is %i, I am ",philo_info.time);
            philo_info.time = philo_info.time + 10;
            usleep(10);
            pthread_mutex_unlock(&mutex);
            philo_info.fork[1] = 0;
            philo_info.fork[0] = 0;
        }
        if(philo_info.time > 500)
            break;
    }


    return 0;
}

int sit_philo(int num, s_box philo_info)
{
    pthread_t philo[num];
    int i;

    i = 0;
    while(i < 2)
    {
        pthread_create(&philo[i],NULL,observe_philo,&philo_info);
        i++;
    }
    return 0;
}

int main(int ac ,char **av)
{
    int i;
    s_box philo_info;

    i = 0;
    philo_info.fork[0] = 0;
    philo_info.fork[1] = 0;/*人数文を増やすので、たぶんここで構造体をmallocしておきたい*/
    philo_info.time_to_eat = 100; 
    philo_info.time = 0;
    sit_philo(ac, philo_info);

}


