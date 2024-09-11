/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mutix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:13:26 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/06 11:09:08 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->monitor->mutex_print);
	time = time_of_day() - philo->time;
	if (ft_ff2(philo))
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

	prev = time_of_day();
	while (time_of_day() - prev < time)
	{
		usleep(500);
	}
}

void	ft_mutexxx(t_philo *philo)
{
	int				philos;
	pthread_mutex_t	*mxt;
	int				i;

	i = 0;
	philos = philo->monitor->number_of_philo;
	mxt = malloc(sizeof(pthread_mutex_t) * philos);
	philo->monitor->mxt = mxt;
	while (i < philos)
	{
		pthread_mutex_init(&mxt[i], NULL);
		i++;
	}
	i = 0;
	while (i < philos)
	{
		if (philos > 1)
			philo[i].fork_left = &(mxt[(i + 1) % philos]);
		philo[i].fork_right = &(mxt[i]);
		i++;
	}
}
