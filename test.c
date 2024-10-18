
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


/*
終わらせるやつ作りたい
break;
if(pman->is_dead == true)
    break;

*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("aiueo\n");
    write(1,"aaaaa\n",6);
}