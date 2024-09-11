/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:36:54 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/06 11:09:45 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (!(philo->id % 2))
		usleep(100);
	while (ft_ff2(philo))
	{
		if (philo->monitor->number_of_philo == 1)
		{
			pthread_mutex_lock(philo->fork_right);
			ft_print_message("has taken a fork", philo);
			pthread_mutex_unlock(philo->fork_right);
			ft_usleep(philo->monitor->time_to_die);
			ft_print_message("dead", philo);
			return (NULL);
		}
		ft_fork(philo);
		ft_print_message("is sleeping", philo);
		ft_usleep(philo->monitor->time_to_sleep);
		usleep(1000);
	}
	return (NULL);
}

void	*ft_monitor(void *ff)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ff;
	i = 0;
	while (1 && philo->monitor->number_of_philo > 1)
	{
		if (i == philo->monitor->number_of_philo)
			i = 0;
		if (ft_ff1(&philo[i]) && time_of_day()
			- ft_ff1(&philo[i]) > philo[i].monitor->time_to_die)
		{
			ft_print_message("dead", &philo[i]);
			ft_edit(philo);
			break ;
		}
		if (ft_check_die(philo) && philo->monitor->eat)
		{
			ft_edit(philo);
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
	ft_destory(philo);
}

int	main(int ac, char **av)
{
	(void)ac;
	if (check_is_number(av) || ac > 6 || ac < 5)
	{
		write(2, "Error\n", ft_strlen("Error\n"));
		return (1);
	}
	ft_philo(av);
}
