/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:09:43 by abquaoub          #+#    #+#             */
/*   Updated: 2024/07/07 10:31:06 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_ff1(t_philo *philo)
{
	size_t	x;

	pthread_mutex_lock(philo->monitor->mutex_time);
	x = philo->last_eat;
	pthread_mutex_unlock(philo->monitor->mutex_time);
	return (x);
}

void	ft_edit(t_philo *philo)
{
	pthread_mutex_lock(philo->monitor->mutex_flag);
	philo->monitor->flag = 0;
	pthread_mutex_unlock(philo->monitor->mutex_flag);
}

int	ft_ff2(t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(philo->monitor->mutex_flag);
	tmp = philo->monitor->flag;
	pthread_mutex_unlock(philo->monitor->mutex_flag);
	return (tmp);
}

void	ft_destory(t_philo *philo)
{
	int	num;
	int	i;

	num = philo->monitor->number_of_philo;
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(philo[i].fork_right);
		i++;
	}
	pthread_mutex_destroy(philo->monitor->mutex_print);
	pthread_mutex_destroy(philo->monitor->mutex_flag);
	pthread_mutex_destroy(philo->monitor->counter);
	pthread_mutex_destroy(philo->monitor->mutex_time);
	free(philo->monitor->mutex_print);
	free(philo->monitor->mutex_flag);
	free(philo->monitor->counter);
	free(philo->monitor->mutex_time);
	free(philo->monitor->mxt);
	free(philo->monitor);
	free(philo);
}

void	ft_fork(t_philo *philo)
{
	pthread_mutex_t	*first_take;
	pthread_mutex_t	*second_take;

	ft_print_message("is thinking", philo);
	first_take = philo->fork_right;
	second_take = philo->fork_left;
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
}
