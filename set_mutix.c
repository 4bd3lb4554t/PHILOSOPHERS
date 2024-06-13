/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mutix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:13:26 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/13 17:33:34 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_edit_var(t_philo *philo, int flag)
{
	if (flag == 0)
	{
		pthread_mutex_lock(philo->monitor->mutex_time);
		philo->last_eat = time_of_day();
		pthread_mutex_unlock(philo->monitor->mutex_time);
	}
	else if (flag == 2)
	{
		pthread_mutex_lock(philo->monitor->counter);
		philo->counter++;
		pthread_mutex_unlock(philo->monitor->counter);
	}
	else
	{
		pthread_mutex_lock(philo->monitor->mutex_flag);
		philo->monitor->flag = 0;
		pthread_mutex_unlock(philo->monitor->mutex_flag);
	}
}

void	*return_flag(void *number, t_philo *philo, int flag)
{
	void			*tmp;
	pthread_mutex_t	*mutex;

	if (flag == 0)
		mutex = philo->monitor->mutex_flag;
	else if (flag == 2)
		mutex = philo->monitor->counter;
	else
		mutex = philo->monitor->mutex_time;
	pthread_mutex_lock(mutex);
	tmp = number;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

void	ft_print_message(char *str, t_philo *philo)
{
	size_t	time;
	int		ff;

	ff = *(int *)return_flag(&philo->monitor->flag, philo, 0);
	if (!ff)
		return ;
	pthread_mutex_lock(philo->monitor->mutex_print);
	time = time_of_day() - philo->time;
	printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->monitor->mutex_print);
}

size_t	time_of_day(void)
{
	size_t			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(size_t time)
{
	size_t	prev;

	prev = time_of_day() + time;
	while (1)
	{
		if (time_of_day() >= prev)
			break ;
	}
}
