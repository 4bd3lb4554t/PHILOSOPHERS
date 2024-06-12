/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:37:23 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/11 09:24:39 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct monitor
{
	int				flag;
	int				number_of_philo;

	size_t			time;
	int			eat;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	pthread_mutex_t	*mxt;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*counter;
	pthread_mutex_t	*mutex_time;
	pthread_mutex_t	*mutex_flag;

}					t_monitor;

typedef struct s_philo
{
	t_monitor		*monitor;
	int				id;
	size_t			time;
	size_t			last_eat;
	int			full_eat;
	int counter;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		thread;
}					t_philo;

int					ft_atoi(const char *theString);
char				*ft_itoa(int n);
char				*ft_strdup(const char *source);
size_t				ft_strlen(const char *s);
void				ft_usleep(size_t time);
void				ft_print_message(char *str, t_philo *head);
size_t				time_of_day(void);
t_philo				*ft_creat_data(char **av);
char				*ft_remove_0(char *str);
int					check_is_number(char **str);

#endif