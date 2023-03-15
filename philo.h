/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:02:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/15 12:40:41 by yajallal         ###   ########.fr       */
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
	pthread_mutex_t	m_is_dead;
	pthread_mutex_t	m_is_finish;
	pthread_mutex_t	m_last_eat_time;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				is_died;
	int				time_sleep;
	int				all_finish;
	int				nb_times;
	long long		time_start;
}	t_philo;

typedef struct s_details {
	pthread_t	thread;
	int			id;
	int			nb_eat;
	int			is_finish;
	long long	last_eat_time;
	t_philo		*philo;
}	t_details;

// check_arg.c
int			check_arg(char **av);
int			init_philo(t_philo *philo, char **av);
int			check_philo(t_philo *philo, char **av);

// check_nb_eat.c
int			ft_check_nb_eat(t_details *threads);

// create_threads.c
void		*simulation_fct(void *p);
int			create_thread(t_philo *philo);

// mutex_lock.c
int			one_philo(t_details *thread);
int			mutex_lock(t_details *thread);

// philo_death.c
int			death_checker(t_details *thread);
int			eat_checker(t_details *thread);

// threads_fct.c
int			init_mutex(t_philo *philo);
int			init_threads(t_philo *philo, t_details *threads);
int			stop_threads(t_details *threads);

// print_log
void print_log(t_details *thread, char *log);

// time.c
long long	get_time(void);
void		own_sleep(int time_to_sleep);

// tools.c
int			ft_atoi(char *str);
int			ft_isdigit(int c);

#endif