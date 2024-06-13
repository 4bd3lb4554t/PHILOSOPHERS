/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:36:54 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/13 17:34:21 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	ft_edit_var(philo, 0);
	ft_print_message("is eating", philo);
	ft_usleep(philo->monitor->time_to_eat);
	ft_edit_var(philo, 2);
	pthread_mutex_unlock(first_take);
	pthread_mutex_unlock(second_take);
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(100);
	while (*(int *)return_flag(&philo->monitor->flag, philo, 0))
	{
		if (philo->monitor->number_of_philo == 1)
		{
			pthread_mutex_lock(philo->fork_right);
			ft_print_message("has taken a fork", philo);
			pthread_mutex_unlock(philo->fork_right);
			ft_usleep(philo->monitor->time_to_die);
			ft_print_message("dead", philo);
			ft_edit_var(philo, 1);
			break ;
		}
		ft_fork(philo);
		ft_print_message("is sleeping", philo);
		ft_usleep(philo->monitor->time_to_sleep);
	}
	return (NULL);
}

void	*ft_monitor(void *ff)
{
	t_philo	*philo;
	int		i;
	size_t	last;

	philo = (t_philo *)ff;
	i = 0;
	while (1 && philo->monitor->number_of_philo > 1)
	{
		if (i == philo->monitor->number_of_philo)
			i = 0;
		last = *(size_t *)return_flag(&philo[i].last_eat, philo, 1);
		if (last && time_of_day() - last > philo[i].monitor->time_to_die)
		{
			ft_print_message("dead", &philo[i]);
			ft_edit_var(philo, 1);
			break ;
		}
		if (ft_check_die(philo) && philo->monitor->eat != 0)
		{
			ft_edit_var(philo, 1);
			break ;
		}
		i++;
	}
	return (NULL);
}

void	ft_philo(char **av)
{
	t_philo		*philo;
	int			i;
	pthread_t	monitor;

	philo = ft_creat_data(av);
	i = 0;
	philo->monitor->flag = 1;
	while (i < philo->monitor->number_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&monitor, NULL, &ft_monitor, philo);
	pthread_join(monitor, NULL);
	while (i < philo->monitor->number_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	if (check_is_number(av))
		return (1);
	ft_philo(av);
}
