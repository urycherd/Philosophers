/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:10:24 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/16 17:35:42 by urycherd         ###   ########.fr       */
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
	int					x_ate;
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
	t_philo				*philo;
}						t_data;

int			init(t_data *r, char **s);
long long	timestamp(void);
void		action_print(t_data *data, int id, char *string);
void		ft_sleep(long long time, t_data *data);
int			write_error(char *s);
int			ft_atoi(const char *str);
void		exit_launcher(t_data *data);

#endif