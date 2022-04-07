/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:28:10 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/18 09:28:10 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_meal(t_philo *philo)
{
	int	i;
	int	flag;

	i = -1;
	flag = 1;
	pthread_mutex_lock(&philo->eating);
	while (++i < philo->table->philos)
	{
		if (philo->table->philo[i]->meal_counter < philo->table->meals)
		{
			flag = 0;
			break ;
		}
	}
	if (flag)
	{
		philo->table->finish = 0;
		pthread_mutex_lock(&philo->eating);
		pthread_mutex_lock(&philo->table->print);
	}
	pthread_mutex_unlock(&philo->eating);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (philo->table->finish)
	{
		if (!philo->is_eating && (get_time() - philo->last_meal)
			>= philo->table->die)
		{
			i = -1;
			philo->table->finish = 0;
			message(philo->table, philo->n, "died");
			while (++i < philo->table->philos)
				pthread_mutex_lock(&philo->table->philo[i]->eating);
		}
		if (philo->table->meals && philo->meal_counter >= philo->table->meals)
			check_meal(philo);
		usleep(100);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (!philo->table->finish)
		return ;
	pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	if (!philo->table->finish)
		return ;
	message(philo->table, philo->n, "has taken the left fork");
	if (!philo->table->finish)
		return ;
	pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	if (!philo->table->finish)
		return ;
	message(philo->table, philo->n, "has taken the right fork");
	pthread_mutex_lock(&philo->eating);
	philo->last_meal = get_time();
	philo->is_eating = 1;
	message(philo->table, philo->n, "is eating");
	ft_sleep(philo->table->eat);
	philo->is_eating = 0;
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->eating);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->table->finish)
	{
		eat(philo);
		pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
		if (!philo->table->finish)
			break ;
		message(philo->table, philo->n, "is sleeping");
		ft_sleep(philo->table->sleep);
		if (!philo->table->finish)
			break ;
		message(philo->table, philo->n, "is thinking");
	}
	return (NULL);
}

void	start_life(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos)
	{
		table->philo[i]->last_meal = get_time();
		pthread_create(&table->philo[i]->thread, NULL,
			life, (void *)table->philo[i]);
		usleep(100);
	}
	i = -1;
	while (++i < table->philos)
	{
		pthread_create(&table->philo[i]->monitor, NULL,
			monitor, (void *)table->philo[i]);
		usleep(100);
	}
}
