/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:38:48 by dyao              #+#    #+#             */
/*   Updated: 2024/11/14 22:06:34 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				t_t_eat;		//time to eat
	int				n_t_eat;		//number to eat
	int				t_t_sleep;		//time to sleep
	int				t_t_death;		//time to death
	int				t_t_live;		//time to live
	bool			fork;			//fork in 0 and 1
	int				n_philo;		//the number of the philo
	bool			next_fork;
	bool			live_status;
	int				last_sleep_time;
	struct timeval	t_last_check;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*mutex_for_fork;
	pthread_mutex_t	*mutex_for_death;
	struct s_philo	*pre;
	struct s_philo	*next;
}	t_philo;

t_philo	*ft_input(char **argv, pthread_mutex_t *mutex,
			pthread_mutex_t *mutex_for_fork, pthread_mutex_t *mutex_for_death);
int		ft_atoi(const char *str);
void	ft_start(int argc, t_philo *philo);
void	ft_print_thinking(struct timeval start_time, t_philo *philo);
int		ft_print_sleeping(struct timeval start_time, t_philo *philo);
void	ft_print_eating(struct timeval start_time, t_philo *philo);
void	ft_taken_fork(struct timeval start_time, t_philo *philo);
void	ft_usleep(int time);
int		ft_check_all_fork(t_philo *philo);
void	ft_stop_all(t_philo *philo);
int		ft_check_death_v2(struct timeval start_time, t_philo *philo);
void	ft_print_everything(t_philo *philo, int current_status, int time);

#endif