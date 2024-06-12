/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:51 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/11 09:47:07 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

char	*ft_remove_0(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (&str[i]);
		i++;
	}
	return (str);
}

int	check_is_number(char **str)
{
	int		i;
	char	*it;

	i = 1;
	while (str[i])
	{
		str[i] = ft_remove_0(str[i]);
		it = ft_itoa(ft_atoi(str[i]));
		if (strcmp(it, str[i]))
			return (free(it), 1);
		free(it);
		i++;
	}
	return (0);
}

t_monitor	*ft_ini(int number_of_philo, char **av)
{
	t_monitor		*monitor;
	pthread_mutex_t	*mutex;

	monitor = malloc(sizeof(t_monitor));
	mutex = malloc(sizeof(pthread_mutex_t));
	monitor->mutex_flag = mutex;
	monitor->time_to_eat = ft_atoi(av[3]);
	monitor->time_to_sleep = ft_atoi(av[4]);
	monitor->time_to_die = ft_atoi(av[2]);
	if (!av[5])
		monitor->eat = 0;
	else
		monitor->eat = ft_atoi(av[5]);
	monitor->number_of_philo = number_of_philo;
	return (monitor);
}

t_philo	*ft_creat_data(char **av)
{
	int				number_of_philo;
	int				i;
	size_t			time;
	t_philo			*philo;
	t_monitor		*monitor;
	pthread_mutex_t	*mxt;

	i = 0;
	time = time_of_day();
	number_of_philo = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * number_of_philo);
	mxt = malloc(sizeof(pthread_mutex_t) * number_of_philo);
	i = 0;
	while (i < number_of_philo)
	{
		pthread_mutex_init(&mxt[i], NULL);
		i++;
	}
	monitor = ft_ini(number_of_philo, av);
	monitor->mxt = mxt;
	monitor->mutex_time = malloc(sizeof(pthread_mutex_t));
	monitor->counter = malloc(sizeof(pthread_mutex_t));
	monitor->mutex_flag = malloc(sizeof(pthread_mutex_t));
	monitor->mutex_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(monitor->mutex_time, NULL);
	pthread_mutex_init(monitor->mutex_flag, NULL);
	pthread_mutex_init(monitor->mutex_print, NULL);
	pthread_mutex_init(monitor->counter, NULL);
	i = 0;
	while (i < number_of_philo)
	{
		philo[i].monitor = monitor;
		philo[i].full_eat = 0;
		philo[i].counter = 0;
		philo[i].fork_left = &(mxt[(i + 1) % number_of_philo]);
		philo[i].fork_right = &(mxt[i]);
		philo[i].id = i + 1;
		philo[i].time = time;
		philo[i].last_eat = 0;
		i++;
	}
	return (philo);
}
