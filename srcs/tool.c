/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:59:06 by dyao              #+#    #+#             */
/*   Updated: 2024/11/14 22:08:19 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	long int	i;

	i = 0;
	while (i < time)
	{
		usleep(1000);
		i++;
	}
}

void	ft_taken_fork(struct timeval start_time, t_philo *philo)
{
	struct timeval	current_time;
	int				time;

	pthread_mutex_lock(philo->mutex_for_fork);
	philo->fork = true;
	philo->next_fork = false;
	pthread_mutex_unlock(philo->mutex_for_fork);
	if (ft_check_all_fork(philo))
		ft_print_thinking(start_time, philo);
	while (1)
	{
		if (!ft_check_all_fork(philo))
			break ;
		ft_usleep(1);
		if (ft_check_death_v2(start_time, philo))
			return ;
	}
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	ft_print_everything(philo, 0, time);
}

void	ft_print_eating(struct timeval start_time, t_philo *philo)
{
	struct timeval	current_time;
	int				time;

	if (ft_check_all_fork(philo))
		ft_print_thinking(start_time, philo);
	while (1)
	{
		if (!ft_check_all_fork(philo))
			break ;
		ft_usleep(1);
		if (ft_check_death_v2(start_time, philo))
			return ;
	}
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philo->mutex_for_fork);
	philo->fork = true;
	philo->next->fork = true;
	philo->next_fork = true;
	pthread_mutex_unlock(philo->mutex_for_fork);
	time = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	ft_print_everything(philo, 1, time);
	ft_usleep(philo->t_t_eat);
}

int	ft_print_sleeping(struct timeval start_time, t_philo *philo)
{
	struct timeval	current_time;
	int				time;

	pthread_mutex_lock(philo->mutex_for_fork);
	philo->fork = false;
	philo->next->fork = false;
	philo->next_fork = false;
	pthread_mutex_unlock(philo->mutex_for_fork);
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	ft_print_everything(philo, 2, time);
	philo->last_sleep_time = time + philo->t_t_live;
	if (philo->t_t_sleep < philo->t_t_death)
		ft_usleep(philo->t_t_sleep);
	else
		ft_usleep(philo->t_t_death - 30);
	ft_check_death_v2(start_time, philo);
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

void	ft_print_thinking(struct timeval start_time, t_philo *philo)
{
	struct timeval	current_time;
	int				time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	ft_print_everything(philo, 3, time);
}
