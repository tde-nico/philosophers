/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:10:34 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/24 13:37:41 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_philo
{
	pthread_t		monitor;
	int				pid;
	int				n;
	int				last_meal;
	sem_t			*eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	pthread_t	monitor;
	pthread_t	kami;
	int			philos;
	int			die;
	int			eat;
	int			sleep;
	int			meals;
	int			start;
	sem_t		*print;
	sem_t		*meal;
	sem_t		*forks;
	sem_t		*death;
	t_philo		**philo;
}	t_table;

t_table	*init_table(int argc, char **argv);
void	start_life(t_table *table);
void	close_processes(t_table *table);
int		get_time(void);
void	message(t_table *table, int n_philo, char *msg);
void	ft_sleep(u_int64_t time);
int		is_number(char *str);
int		ft_atoi(const char *str);

#endif
