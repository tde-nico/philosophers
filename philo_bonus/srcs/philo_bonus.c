/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:23:07 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/24 13:38:16 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

void	free_table(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals)
		pthread_detach(table->monitor);
	pthread_detach(table->kami);
	usleep(1000);
	while (++i < table->philos)
	{
		sem_close(table->philo[i]->eat);
		free(table->philo[i]);
	}
	sem_close(table->forks);
	sem_close(table->meal);
	sem_close(table->print);
	sem_close(table->death);
	free(table->philo);
	free(table);
}

void	close_processes(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		while (++i < table->philos)
			kill(table->philo[i]->pid, SIGKILL);
	}
	free_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!is_arg_valid(argc, argv))
		return (1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	table->start = get_time();
	start_life(table);
	usleep(1000);
	return (0);
}
