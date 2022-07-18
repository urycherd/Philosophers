/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:31:16 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/18 18:40:42 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int agc, char **argv)
{
	t_data	data;

	if (agc != 5 && agc != 6)
		return (printf("Error: Wrong amount of arguments\n"));
	if (parse(&data, argv))
		return (printf("Error: Init error\n"));
	if (simulation(&data))
		return (printf("Error: Thread error\n"));
	free(data.philo);
	return (0);
}
