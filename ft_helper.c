/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:31:33 by abquaoub          #+#    #+#             */
/*   Updated: 2024/07/06 13:48:13 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strdup(const char *source)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = ft_strlen(source);
	i = 0;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (0);
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_ff(t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(philo->monitor->counter);
	tmp = philo->counter;
	pthread_mutex_unlock(philo->monitor->counter);
	return (tmp);
}

int	ft_check_die(t_philo *philo)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (i < philo->monitor->number_of_philo)
	{
		if (ft_ff(&philo[i]) < philo->monitor->eat)
			flag = 0;
		i++;
	}
	return (flag);
}
