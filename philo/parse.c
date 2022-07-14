/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:33:27 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/12 17:56:17 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_sale(int i, int philo_num, t_philo *philo)
{
	if (i == philo_num - 1)
	{
		philo[i].left_fork_id = (i + 1) % philo_num;
		philo[i].right_fork_id = i;
	}
	else
	{
		philo[i].left_fork_id = i;
		philo[i].right_fork_id = (i + 1) % philo_num;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	i = data->philo_num;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i);
	if (data->forks == NULL)
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->write), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(data->all_ate_m), NULL))
		return (1);
	if (pthread_mutex_init(&(data->died_m), NULL))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = data->philo_num;
	data->philosophers = (t_philo *)malloc(sizeof(t_philo) * i);
	if (data->philosophers == NULL)
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->philosophers[i].x_ate_m), NULL))
			return (1);
		data->philosophers[i].id = i;
		data->philosophers[i].x_ate = 0;
		data->philosophers[i].t_last_meal = 0;
		data->philosophers[i].data = data;
		forks_sale(i, data->philo_num, data->philosophers);
	}
	return (0);
}

int	parse(t_data *data, char **s)
{
	data->philo_num = ft_atoi(s[1]);
	data->time_death = ft_atoi(s[2]);
	data->time_eat = ft_atoi(s[3]);
	data->time_sleep = ft_atoi(s[4]);
	data->died = 0;
	data->all_ate = 0;
	if (data->philo_num < 1 || data->time_death < 0
		|| data->time_eat < 0 || data->time_sleep < 0)
		return (1);
	if (s[5])
	{
		data->num_eat = ft_atoi(s[5]);
		if (data->num_eat <= 0)
			return (1);
	}
	else
		data->num_eat = -1;
	if (init_mutex(data) || init_philo(data))
		return (1);
	return (0);
}
