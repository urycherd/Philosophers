/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:02:05 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/18 12:42:54 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_data *data, int id, char *str)
{
	sem_wait(data->sem_died);
	if (!(data->died)) // защитить надо - датарейсы
	{
		printf("%lli ", time_now() - data->start);
		printf("%i %s\n", id + 1, str);
	}
	sem_post(data->sem_died);
}

int	write_error(char *s)
{
	printf("Error: %s\n", s);
	return (1);
}

long long	time_now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(long long time)
{
	long long	i;

	i = time_now();
	while (time_now() - i < time)
		usleep(50);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = -1;
	if (*str == '-')
		str++;
	else
		sign = 1;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			return (-1);
		str++;
	}
	return (num * sign);
}