/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:33:27 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/16 17:35:46 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_sem(t_data *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_meal_check");
	data->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, data->philo_num);
	data->write = sem_open("/philo_writing", O_CREAT, S_IRWXU, 1);
	data->meal_check = sem_open("/philo_meal_check", O_CREAT, S_IRWXU, 1);
	if (data->forks <= 0 || data->write <= 0 || data->meal_check <= 0)
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = data->philo_num;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * i);
	if (data->philo == NULL)
		return (1);
	while (--i >= 0)
	{
		data->philo[i].id = i;
		data->philo[i].x_ate = 0;
		data->philo[i].t_last_meal = 0;
		data->philo[i].data = data;
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
	if (ft_init_sem(data) || init_philo(data))
		return (1);
	return (0);
}
