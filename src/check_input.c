#include "philo.h"

/*

input
->check_error->pman_init->startpman

インプットチェック

何人か　if 200 弾く || is_digit
何秒で餓死するか　 is_digit || 正 
何秒で食べ終わるか　is_digit || 正　
何秒間寝るか



◦ number_of_philosophers: The number of philosophers and also the number of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

もしやばければ途中でreturn falseで返して終わらせる。
全部通過したらtrueを返す

*/

int	is_over(long num, int count)
{
	if (count == 0 && (num > INT_MAX || num < INT_MIN))
		return (1);
	else if (count == 1 && ((-1 * num) > INT_MAX || (-1 * num) < INT_MIN))
		return (1);
	return (0);
}

int	ft_check_str_l(const char *str, int count)
{
	long	num;

	num = 0;
	if (*str == '\0' || count > 1)
        return 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		if (is_over(num, count) == 1)
			return 0;
		str++;
	}
	if (*str != '\0')
		return (0);
	return num;
}

int	ft_advanced_atoi(char *str)
{
	int		count;
	long	num;

	num = 0;
	count = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			count++;
		str++;
	}
	num = ft_check_str_l(str, count);
	if (count == 1)
		num *= -1;
	return (num);
}

bool has_char(char *str)
{
	// printf("nooo\n");
	if(str == NULL)
		return true;
	while(*str)
	{
		if(*str < 48 || *str > 57)
			return true;
		str++;
	}
	return false;
} 


bool check_input(int ac, char **av)
{
	if(ac < 5 || ac > 6)
	{
		printf("too few or many args %i %s\n",ac, av[1]);
		return false;
	}
	printf("%i %i %i %i %i \n",ft_advanced_atoi(av[1]),ft_advanced_atoi(av[2]),ft_advanced_atoi(av[3]),ft_advanced_atoi(av[4]),ft_advanced_atoi(av[4]));
    if(ft_advanced_atoi(av[1]) > 200 || ft_advanced_atoi(av[1]) <= 0 || has_char(av[1]) == true)
        return false;
    if(has_char(av[2]) == true || ft_advanced_atoi(av[2]) <= 0)
        return false;
	if(has_char(av[3]) == true || ft_advanced_atoi(av[3]) <= 0)
        return false;
	if(has_char(av[4]) == true || ft_advanced_atoi(av[4]) <= 0)
        return false;
	if(ac == 6)
	{
		if(has_char(av[5]) == true || ft_advanced_atoi(av[5]) <= 0)
        	return false;
	}
    return true;
}


