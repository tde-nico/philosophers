/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:27:20 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/24 15:02:41 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_arg_valid(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0 * printf("Error\n[!!] wrong argument number\n"));
	while (++i < argc)
		if (argv[i][0] == '-' || !is_number(argv[i])
			|| !ft_atoi(argv[i]))
			return (0 * printf("Error\n[!!] Invalid Arguments\n"));
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!is_arg_valid(argc, argv))
		return (1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	table->finish = 1;
	table->start = get_time();
	start_life(table);
	while (table->finish)
		;
	usleep(1000);
	return (0);
}
