/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:36:54 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/11 21:04:02 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_edit(t_philo *philo)
{
	pthread_mutex_lock(philo->monitor->mutex_flag);
	philo->monitor->flag = 0;
	pthread_mutex_unlock(philo->monitor->mutex_flag);
}

int	ft_lock_flag(int *number, pthread_mutex_t *mutex)
{
	int	tmp;

	pthread_mutex_lock(mutex);
	tmp = *number;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

size_t	ft_lock_flag_sizet(size_t *number, pthread_mutex_t *mutex)
{
	size_t	tmp;

	pthread_mutex_lock(mutex);
	tmp = *number;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

void	ft_print_message(char *str, t_philo *philo)
{
	size_t	time;

	if (!ft_lock_flag(&philo->monitor->flag, philo->monitor->mutex_flag))
		return ;
	pthread_mutex_lock(philo->monitor->mutex_print);
	time = time_of_day() - philo->time;
	printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->monitor->mutex_print);
}

void	ft_fork(t_philo *philo)
{
	pthread_mutex_t	*first_take;
	pthread_mutex_t	*second_take;

	ft_print_message("is thinking", philo);
	first_take = philo->fork_right;
	second_take = philo->fork_left;
	// if (philo->monitor->number_of_philo == 1)
	// {
	// 	pthread_mutex_lock(first_take);
	// 	ft_print_message("has taken a fork", philo);
	// 	pthread_mutex_unlock(first_take);
	// 	ft_usleep(philo->monitor->time_to_die);
	// 	ft_print_message("dead", philo);
	// 	ft_edit(philo);
	// 	return;
	// }
	if (philo->id % 2)
	{
		first_take = philo->fork_left;
		second_take = philo->fork_right;
	}
	pthread_mutex_lock(first_take);
	ft_print_message("has taken a fork", philo);
	pthread_mutex_lock(second_take);
	ft_print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->monitor->mutex_time);
	philo->last_eat = time_of_day();
	pthread_mutex_unlock(philo->monitor->mutex_time);
	ft_print_message("is eating", philo);
	ft_usleep(philo->monitor->time_to_eat);
	pthread_mutex_lock(philo->monitor->counter);
	philo->counter++;
	pthread_mutex_unlock(philo->monitor->counter);
	pthread_mutex_unlock(first_take);
	pthread_mutex_unlock(second_take);
	ft_print_message("is sleeping", philo);
	ft_usleep(philo->monitor->time_to_sleep);
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(100);
	while (ft_lock_flag(&philo->monitor->flag, philo->monitor->mutex_flag))
	{
		ft_fork(philo);
	}
	return (NULL);
}

int	ft_check(t_philo *philo)
{
	int	i;
	int	flag;
	int	count;

	
	i = 0;
	flag = 1;
	while (i < philo->monitor->number_of_philo)
	{
		count = ft_lock_flag(&philo[i].counter, philo->monitor->counter);
		if (count < philo->monitor->eat)
			flag = 0;
		i++;
	}
	return (flag);
}

void	*ft_monitor(void *ff)
{
	t_philo	*philo;
	int		number_of_philo;
	int		i;
	size_t	last;

	philo = (t_philo *)ff;
	number_of_philo = philo[0].monitor->number_of_philo;
	i = 0;
	while (1 && number_of_philo > 1)
	{
		if (i == number_of_philo)
			i = 0;
		last = ft_lock_flag_sizet(&philo[i].last_eat,
				philo->monitor->mutex_time);
		if (last && time_of_day() - last > philo[i].monitor->time_to_die)
		{
			ft_print_message("dead", &philo[i]);
			ft_edit(philo);
			break ;
		}
		if (ft_check(philo) && philo->monitor->eat != 0)
		{
			ft_edit(philo);
			break ;
		}
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	int			number_of_philo;
	int			i;
	pthread_t	monitor;

	(void)ac;
	number_of_philo = ft_atoi(av[1]);
	if (check_is_number(av))
		return (1);
	philo = ft_creat_data(av);
	i = 0;
	philo->monitor->flag = 1;
	while (i < number_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&monitor, NULL, &ft_monitor, philo);
	pthread_join(monitor, NULL);
	while (i < number_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < number_of_philo)
	{
		pthread_mutex_destroy(philo[i].fork_right);
		i++;
	}
	pthread_mutex_destroy(philo->monitor->mutex_flag);
	pthread_mutex_destroy(philo->monitor->mutex_print);
	pthread_mutex_destroy(philo->monitor->mutex_time);
}
