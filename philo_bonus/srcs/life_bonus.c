/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:22:55 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/18 10:22:55 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*monitor(void *arg)
{
	t_table	*table;
	int		eats;
	int		i;

	eats = -1;
	table = (t_table *)arg;
	while (++eats < table->meals)
	{
		i = -1;
		while (++i <= table->philos)
			sem_wait(table->meal);
	}
	usleep(100);
	sem_post(table->death);
	usleep(100);
	i = -1;
	while (++i < table->philos)
		kill(table->philo[i]->pid, SIGKILL);
	exit(0);
	return (NULL);
}

void	*death(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->eat);
		if ((get_time() - philo->last_meal) >= philo->table->die)
		{
			i = -1;
			while (++i < (philo->table->meals * philo->table->philos))
				sem_post(philo->table->meal);
			message(philo->table, philo->n, "died");
			usleep(100);
			sem_close(philo->eat);
			usleep(100);
			sem_post(philo->table->death);
			exit(0);
		}
		sem_post(philo->eat);
		usleep(100);
	}
	return (NULL);
}

void	*shi(void *arg)
{
	t_table	*table;
	int		i;

	i = -1;
	table = (t_table *)arg;
	sem_wait(table->death);
	usleep(100);
	sem_wait(table->print);
	usleep(100);
	while (++i < (table->meals * (table->philos + 1)))
		sem_post(table->meal);
	exit(0);
	return (NULL);
}

void	*life(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->table->forks);
		message(philo->table, philo->n, "has taken the left fork");
		sem_wait(philo->table->forks);
		message(philo->table, philo->n, "has taken the right fork");
		message(philo->table, philo->n, "is eating");
		usleep(100);
		sem_wait(philo->eat);
		sem_post(philo->table->meal);
		philo->last_meal = get_time();
		ft_sleep(philo->table->eat);
		sem_post(philo->eat);
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
		message(philo->table, philo->n, "is sleeping");
		ft_sleep(philo->table->sleep);
		message(philo->table, philo->n, "is thinking");
		usleep(100);
	}
	return (NULL);
}

void	start_life(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals)
		pthread_create(&table->monitor, NULL, monitor, (void *)table);
	pthread_create(&table->kami, NULL, shi, (void *)table);
	while (++i < table->philos)
	{
		table->philo[i]->pid = fork();
		table->philo[i]->last_meal = get_time();
		if (!table->philo[i]->pid)
		{
			pthread_create(&table->philo[i]->monitor, NULL, death,
				(void *)table->philo[i]);
			life(table->philo[i]);
			exit(0);
		}
		usleep(100);
	}
	close_processes(table);
}
