/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:02:05 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/18 19:45:00 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_action(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&(data->write));
	pthread_mutex_lock(&(data->died_m));
	if (!(data->died))
	{
		printf("%lli ", time_now() - data->start);
		printf("%i %s\n", id + 1, str);
	}
	pthread_mutex_unlock(&(data->died_m));
	pthread_mutex_unlock(&(data->write));
}

int	write_error(char *s)
{
	printf("Error: %s\n", s);
	return (1);
}

int	well_fed_philo(t_data *d)
{
	int		i;
	int		full;
	t_philo	*p;

	full = 0;
	i = 0;
	p = d->philosophers;
	while (d->num_eat != -1 && i < d->philo_num)
	{
		pthread_mutex_lock(&(p[i].x_ate_m));
		if (p[i].x_ate >= d->num_eat)
			full++;
		pthread_mutex_unlock(&(p[i].x_ate_m));
		i++;
	}
	pthread_mutex_lock(&(d->all_ate_m));
	if (full == d->philo_num)
	{
		d->all_ate = 1;
		pthread_mutex_unlock(&(d->all_ate_m));
		return (1);
	}
	pthread_mutex_unlock(&(d->all_ate_m));
	return (0);
}
