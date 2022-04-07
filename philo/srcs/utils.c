/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:28:25 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/18 09:28:25 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (u_int64_t)(1000)) + (time.tv_usec / 1000));
}

void	message(t_table *table, int n_philo, char *msg)
{
	pthread_mutex_lock(&table->print);
	printf("[%d]\tPhilo %d %s\n", get_time() - table->start, n_philo + 1, msg);
	if (msg[0] != 'd')
		pthread_mutex_unlock(&table->print);
	else
		pthread_mutex_init(&table->print, NULL);
}

void	ft_sleep(u_int64_t time)
{
	u_int64_t	start;

	start = 0;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

int	is_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int					sign;
	int					i;
	unsigned long long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		n = (n * 10) + (str[i++] - 48);
	if (n >= 9223372036854775808ULL)
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	return ((int)n * sign);
}
