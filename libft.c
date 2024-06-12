/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:53:31 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/07 17:57:57 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *theString)
{
	int	s;
	int	res;
	int	i;

	s = 1;
	res = 0;
	i = 0;
	while (theString[i] == ' ' || (theString[i] >= 9 && theString[i] <= 13))
		i++;
	if (theString[i] == '-' || theString[i] == '+')
	{
		if (theString[i] == '-')
			s = -1;
		i++;
	}
	while ((theString[i] >= '0' && theString[i] <= '9') && theString[i] != '\0')
	{
		res = res * 10 + theString[i] - 48;
		i++;
	}
	return (res * s);
}

static int	ft_len(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_rev(char *str)
{
	char	tmp;
	size_t	i;
	size_t	j;

	i = ft_strlen(str);
	j = 0;
	if (str[0] == '-')
		j++;
	while (j < i)
	{
		tmp = str[j];
		str[j] = str[i - 1];
		str[i - 1] = tmp;
		i--;
		j++;
	}
}

static void	ft_test(char *arr, int i, int len, long int number)
{
	if (number < 0)
	{
		arr[0] = '-';
		number = number * (-1);
		i++;
	}
	while (i < len && number > 0)
	{
		arr[i] = (number % 10) + 48;
		number = number / 10;
		i++;
	}
	arr[i] = '\0';
}

char	*ft_itoa(int n)
{
	long int	number;
	char		*arr;
	int			len;
	int			i;

	i = 0;
	number = n;
	len = ft_len(number);
	if (number == 0)
	{
		arr = ft_strdup("0");
		return (arr);
	}
	arr = (char *)malloc(len + 1);
	if (!arr)
		return (0);
	ft_test(arr, i, len, number);
	ft_rev(arr);
	return (arr);
}

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
