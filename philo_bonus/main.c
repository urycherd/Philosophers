/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:31:16 by urycherd          #+#    #+#             */
/*   Updated: 2022/07/14 14:39:58 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
