/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:22:29 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/18 10:22:29 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	init_semaphores(t_table *table)
{
	sem_unlink("fork");
	table->forks = sem_open("fork", O_CREAT, 0644, table->philos);
	if (table->forks == SEM_FAILED)
		return (0);
	sem_unlink("print");
	table->print = sem_open("print", O_CREAT, 0644, 1);
	if (table->print == SEM_FAILED)
		return (0);
	sem_unlink("meal");
	table->meal = sem_open("meal", O_CREAT, 0644, 1);
	if (table->meal == SEM_FAILED)
		return (0);
	sem_unlink("death");
	table->death = sem_open("death", O_CREAT, 0644, 0);
	if (table->death == SEM_FAILED)
		return (0);
	return (1);
}

t_philo	**init_philo(t_table *table)
{
	t_philo	**philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo *) * table->philos);
	if (!philo)
		return (NULL);
	while (++i < table->philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		sem_unlink("eat");
		philo[i]->eat = sem_open("eat", O_CREAT, 0644, 1);
		if (philo[i]->eat == SEM_FAILED)
			return (NULL);
		philo[i]->n = i;
		philo[i]->table = table;
	}
	return (philo);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philos = ft_atoi(argv[1]);
	table->die = (u_int64_t)ft_atoi(argv[2]);
	table->eat = (u_int64_t)ft_atoi(argv[3]);
	table->sleep = (u_int64_t)ft_atoi(argv[4]);
	if (!table->philos || !table->die || !table->eat || !table->sleep)
	{
		printf("Error\n[!!] Invalid Arguments\n");
		return (NULL);
	}
	table->meals = 0;
	if (argc == 6)
		table->meals = ft_atoi(argv[5]);
	if (!init_semaphores(table))
		return (NULL);
	table->philo = init_philo(table);
	return (table);
}
