/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:02:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/11 19:07:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo {
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_die;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_times;
	long long		time_start;
}	t_philo;

typedef struct s_details {
	pthread_t	thread;
	int			id;
	int			nb_eat;
	int			is_died;
	int			is_finish;
	long long	last_eat_time;
	t_philo		*philo;
}	t_details;

// check_nb_eat.c
int			ft_check_nb_eat(t_details *threads, int nb_philo);

// create_threads.c
void		*simulation_fct(void *p);
int			create_thread(t_philo *philo);

// mutex_lock.c
int			one_philo(t_details *thread);
int			mutex_lock(t_details *thread);

// philo.c
void		init_philo(t_philo *philo, char **av);
int			check_arg(t_philo *philo);

// threads_fct.c
int			init_threads(t_philo *philo, t_details *threads);
int			stop_threads(t_philo *philo, t_details *threads);

// time.c
long long	get_time(void);
void		own_sleep(int time_to_sleep);

// tools.c
int			ft_atoi(char *str);
int			ft_isdigit(int c);
#endif