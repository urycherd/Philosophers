/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:36:38 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/18 12:42:15 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->forks);
	print_action(data, philo->id, "has taken a fork");
	sem_wait(data->forks);
	print_action(data, philo->id, "has taken a fork");
	sem_wait(data->meal_check);
	print_action(data, philo->id, "is eating");
	philo->t_last_meal = time_now(); // t_last_meal семафор не работает?
	sem_post(data->meal_check);
	ft_sleep(data->time_eat);
	sem_wait(data->sem_time_ate);
	(philo->time_ate)++; // датарейсы
	sem_post(data->sem_time_ate);
	sem_post(data->forks);
	sem_post(data->forks);

}

void	*p_thread(void *tmp)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)tmp;
	data = philo->data;
	while (1)
	{
		sem_wait(data->meal_check);
		if (time_now() - philo->t_last_meal > data->time_death) // t_last_meal??? datarace почему!?
		{
			print_action(data, philo->id, "died");
			sem_wait(data->sem_died);
			data->died = 1; // датарейсы
			sem_post(data->sem_died);
			sem_post(data->meal_check);
			exit (1);
		}
		sem_post(data->meal_check);
		ft_sleep(500);
		sem_wait(data->sem_time_ate);
		if (philo->time_ate >= data->num_eat && data->num_eat != -1) //датарейсы
			break ;
		sem_post(data->sem_time_ate);
	}
	sem_post(data->sem_time_ate);
	return (NULL);
}

void	philo_process(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	philo->t_last_meal = time_now();
	pthread_create(&(philo->thread_id), NULL, p_thread, philo);
	if (philo->id % 2)
		usleep(15000); // is it necessary to sleep so much???
	while (1)
	{
		sem_wait(data->sem_died);
		if (data->died) // датарейсы
			break ;
		sem_post(data->sem_died);
		philo_eats(philo);
		sem_wait(data->sem_time_ate);
		sem_wait(data->sem_died);
		if ((philo->time_ate >= data->num_eat && data->num_eat != -1) || data->died)
			break ;
		sem_wait(data->sem_time_ate);
		sem_post(data->sem_died);
		print_action(data, philo->id, "is sleeping");
		ft_sleep(data->time_sleep);
		sem_wait(data->sem_died);
		if (data->died)
			break ;
		sem_post(data->sem_died);
		print_action(data, philo->id, "is thinking");
	}
	sem_post(data->sem_time_ate);
	sem_post(data->sem_died);
	pthread_join(philo->thread_id, NULL);
	sem_wait(data->sem_died);
	if (data->died)
	{
		sem_post(data->sem_died);
		exit (1); // why different exit?
	}
	sem_post(data->sem_died);
	exit (0);
}

void	end_simulation(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->philo_num)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < data->philo_num)
				kill(data->philo[i].proc_id, 15);
			break ;
		}
		i++;
	}
	sem_close(data->forks);
	sem_close(data->write);
	sem_close(data->meal_check);
	sem_close(data->sem_died);
	sem_close(data->sem_time_ate);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_meal_check");
	sem_unlink("/philo_died");
	sem_unlink("/philo_time_ate");
}

int	simulation(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philo;
	data->start = time_now();
	while (++i < data->philo_num)
	{
		data->philo[i].t_last_meal = time_now();
		philo[i].proc_id = fork();
		if (philo[i].proc_id < 0)
			return (1);
		else if (philo[i].proc_id == 0)
			philo_process(&(philo[i]));
		usleep(100);
	}
	end_simulation(data);
	return (0);
}
