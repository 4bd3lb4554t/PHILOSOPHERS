/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:37:23 by abquaoub          #+#    #+#             */
/*   Updated: 2024/07/07 10:14:49 by abquaoub         ###   ########.fr       */
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
	int				eat;
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
	int				counter;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		thread;
}					t_philo;

int					ft_check_die(t_philo *philo);
int					ft_atoi(const char *theString);
char				*ft_itoa(int n);
char				*ft_strdup(const char *source);
size_t				ft_strlen(const char *s);
void				ft_usleep(size_t time);
void				ft_print_message(char *str, t_philo *head);
int					ft_ff2(t_philo *philo);
size_t				time_of_day(void);
t_philo				*ft_creat_data(char **av);
int					check_is_number(char **str);
void				ft_mutexxx(t_philo *philo);
size_t				ft_ff1(t_philo *philo);
void				ft_edit(t_philo *philo);
int					ft_ff2(t_philo *philo);
void				ft_destory(t_philo *philo);
void				ft_fork(t_philo *philo);

#endif