/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:31:16 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/16 17:39:45 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	main(int agc, char **argv)
{
	t_data	data;

	if (agc != 5 && agc != 6)
		return (write_error("Wrong amount of arguments"));
	if (parse(&data, argv))
		return (write_error("Init error"));
	if (simulation(&data))
		return (write_error("Thread error"));
	free(data.philo);
	return (0);
}
