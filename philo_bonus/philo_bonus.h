/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:10:24 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/18 22:15:27 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_philo
{
	int					id;
	int					time_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_data		*data;
	pthread_t			thread_id;
	pid_t				proc_id;
}						t_philo;

typedef struct s_data
{
	int					philo_num;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					num_eat;
	int					died;
	long long			start;
	sem_t				*meal_check;
	sem_t				*forks;
	sem_t				*write;
	sem_t				*sem_died;
	sem_t				*sem_time_ate;
	t_philo				*philo;
}						t_data;

int			parse(t_data *data, char **s);
int			simulation(t_data *data);
long long	time_now(void);
void		print_action(t_data *data, int id, char *string);
void		ft_sleep(long long time);
int			ft_atoi(const char *str);
void		ft_death_check(t_data *data, t_philo *philo);

#endif