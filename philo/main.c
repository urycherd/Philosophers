/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:31:16 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/18 21:49:24 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->meal_check));
	print_action(data, philo->id, "is eating");
	philo->t_last_meal = time_now();
	pthread_mutex_lock(&(philo->x_ate_m));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(philo->x_ate_m));
	pthread_mutex_unlock(&(data->meal_check));
	ft_sleep(data->time_eat, data);
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
}

void	death_check(t_data *d, t_philo *p)
{
	int	i;

	while (1)
	{
		if ((d->all_ate))
			return ;
		i = -1;
		while (++i < d->philo_num)
		{
			pthread_mutex_lock(&(d->meal_check));
			if (time_now() - p[i].t_last_meal > d->time_death)
			{
				print_action(d, i, "died");
				pthread_mutex_lock(&(d->died_m));
				d->died = 1;
				pthread_mutex_unlock(&(d->died_m));
				pthread_mutex_unlock(&(d->meal_check));
				return ;
			}
			pthread_mutex_unlock(&(d->meal_check));
			usleep(100);
		}
		well_fed_philo(d);
	}
}

void	*life_p(void *philo_void)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_void;
	data = philo->data;
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		philo_eat(philo);
		pthread_mutex_lock(&(data->died_m));
		pthread_mutex_lock(&(data->all_ate_m));
		if (data->all_ate || data->died == 1)
			break ;
		pthread_mutex_unlock(&(data->all_ate_m));
		pthread_mutex_unlock(&(data->died_m));
		print_action(data, philo->id, "is sleeping");
		ft_sleep(data->time_sleep, data);
		print_action(data, philo->id, "is thinking");
	}
	pthread_mutex_unlock(&(data->died_m));
	pthread_mutex_unlock(&(data->all_ate_m));
	return (0);
}

int	simulation(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philosophers;
	data->start = time_now();
	while (++i < data->philo_num)
	{
		data->philosophers[i].t_last_meal = time_now();
		if (pthread_create(&(philo[i].thread_id), NULL, life_p, &(philo[i])))
			return (1);
	}
	death_check(data, data->philosophers);
	i = -1;
	if (data->philo_num == 1)
		pthread_detach(philo[0].thread_id);
	else
		while (++i < data->philo_num)
			pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->write));
	return (0);
}

int	main(int agc, char **argv)
{
	t_data	data;

	if (agc != 5 && agc != 6)
		return (write_error("Wrong amount of arguments"));
	if (parse(&data, argv))
		return (write_error("Init error"));
	if (simulation(&data))
		return (write_error("Thread error"));
	free(data.forks);
	free(data.philosophers);
	return (0);
}
