/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:51 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/13 17:22:10 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_monitor	*ft_init(int number_of_philo, char **av)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(t_monitor));
	monitor->time_to_eat = ft_atoi(av[3]);
	monitor->time_to_sleep = ft_atoi(av[4]);
	monitor->time_to_die = ft_atoi(av[2]);
	if (!av[5])
		monitor->eat = 0;
	else
		monitor->eat = ft_atoi(av[5]);
	monitor->number_of_philo = number_of_philo;
	monitor->mutex_time = malloc(sizeof(pthread_mutex_t));
	monitor->counter = malloc(sizeof(pthread_mutex_t));
	monitor->mutex_flag = malloc(sizeof(pthread_mutex_t));
	monitor->mutex_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(monitor->mutex_time, NULL);
	pthread_mutex_init(monitor->mutex_flag, NULL);
	pthread_mutex_init(monitor->mutex_print, NULL);
	pthread_mutex_init(monitor->counter, NULL);
	return (monitor);
}

void	ft_mutexxx(t_philo *philo)
{
	int				philos;
	pthread_mutex_t	*mxt;
	int				i;

	i = 0;
	philos = philo->monitor->number_of_philo;
	mxt = malloc(sizeof(pthread_mutex_t) * philos);
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

t_philo	*ft_creat_data(char **av)
{
	int			i;
	size_t		time;
	t_philo		*philo;
	t_monitor	*monitor;

	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	monitor = ft_init(ft_atoi(av[1]), av);
	time = time_of_day();
	i = 0;
	while (i < monitor->number_of_philo)
	{
		philo[i].monitor = monitor;
		philo[i].counter = 0;
		philo[i].id = i + 1;
		philo[i].time = time;
		philo[i].last_eat = 0;
		i++;
	}
	ft_mutexxx(philo);
	return (philo);
}
