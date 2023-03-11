/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:02:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/11 18:42:59 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo {
	pthread_mutex_t *fork;
	pthread_mutex_t print_die;
	int	nb_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int nb_times;
	long long time_start;
} t_philo;
typedef struct s_details {
	pthread_t thread;
	int id;
	int nb_eat;
	int is_died;
	int is_finish;
	long long last_eat_time;
	t_philo *philo;
} t_details;



int	ft_atoi(char *str);
int	ft_isdigit(int c);

void init_philo(t_philo *philo, char **av);
int check_arg(t_philo *philo);

int create_thread(t_philo *philo);

long long get_time(void);
void own_sleep(int time_to_sleep);

int mutex_lock(t_details *thread);

int ft_check_nb_eat(t_details *threads, int nb_philo);
int	init_threads(t_philo *philo, t_details *threads);
int stop_threads(t_philo *philo, t_details *threads);


#endif