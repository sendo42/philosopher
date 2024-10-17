#include "philo.h"

// long get_current_time()
// {
//     long time;
//     struct timeval tv;

//     gettimeofday(&tv,NULL);
//     time = tv.tv_usec / 1000 + tv.tv_sec * 1000;
//     return time;
// }

// int main()
// {
//     long time;
//     struct timeval tv;

//     gettimeofday(&tv,NULL);
//     time = tv.tv_usec / 1000 + tv.tv_sec * 1000;

//     printf("no time %i %li\n",tv.tv_usec ,tv.tv_sec);
//     usleep(1000);
//     printf("%li\n",get_current_time() - time);
// }


#include <stdio.h>
#include <sys/time.h>
int main(int argc, char **argv) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
  gettimeofday(&tv, NULL);
  printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
  return 0;
}