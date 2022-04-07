/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:27:15 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/18 10:46:44 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		monitor;
	int				n;
	int				last_meal;
	int				meal_counter;
	int				l_fork;
	int				r_fork;
	int				is_eating;
	pthread_mutex_t	eating;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				meals;
	int				start;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	int				finish;
	t_philo			**philo;
}	t_table;

t_table	*init_table(int argc, char **argv);
void	start_life(t_table *table);
int		get_time(void);
void	message(t_table *table, int n_philo, char *msg);
void	ft_sleep(u_int64_t time);
int		is_number(char *str);
int		ft_atoi(const char *str);

#endif
