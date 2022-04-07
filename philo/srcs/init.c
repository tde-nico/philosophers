/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:27:54 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/18 09:27:54 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	*init_fork(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	if (!table->philos || !table->die || !table->eat || !table->sleep)
	{
		printf("Error\n[!!] Invalid Arguments\n");
		return (NULL);
	}
	forks = malloc(sizeof(pthread_mutex_t) * table->philos);
	if (!forks)
		return (NULL);
	while (++i < table->philos)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
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
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (NULL);
		if (pthread_mutex_init(&philo[i]->eating, NULL))
			return (NULL);
		philo[i]->n = i;
		philo[i]->table = table;
		philo[i]->is_eating = 0;
		philo[i]->meal_counter = 0;
		philo[i]->l_fork = i;
		philo[i]->r_fork = (i + 1) % table->philos;
	}
	return (philo);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	table->philos = ft_atoi(argv[1]);
	table->die = (u_int64_t)ft_atoi(argv[2]);
	table->eat = (u_int64_t)ft_atoi(argv[3]);
	table->sleep = (u_int64_t)ft_atoi(argv[4]);
	table->meals = 0;
	if (argc == 6)
		table->meals = ft_atoi(argv[5]);
	table->forks = init_fork(table);
	table->philo = init_philo(table);
	if (!table->forks || !table->philo)
		return (NULL);
	return (table);
}
