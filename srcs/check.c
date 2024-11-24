/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:35:28 by dyao              #+#    #+#             */
/*   Updated: 2024/11/24 21:33:32 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_all_fork(t_philo *philo)
{
	if (philo->next == philo)
		return (1);
	pthread_mutex_lock(philo->mutex_for_fork);
	if (philo->next->next_fork == true && philo->pre->next_fork == true)
	{
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (1);
	}
	else if (philo->next->next_fork == true && philo->pre->next_fork == false
		&& philo->fork == true)
	{
		philo->fork = false;
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (1);
	}
	else if (philo->next->next_fork == false && philo->pre->next_fork == false)
	{
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (1);
	}
}

void	ft_stop_all(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_for_death);
	while (philo->live_status != 1)
	{
		philo->live_status = 1;
		philo = philo->next;
	}
	pthread_mutex_unlock(philo->mutex_for_death);
}

void	ft_check_death_v3(struct timeval start_time, t_philo *philo)
{
	struct timeval	current_time;
	int				time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	if ((time + philo->t_t_live - philo->last_sleep_time
			+ philo->t_t_eat) >= philo->t_t_death)
	{
		ft_usleep(philo->t_t_death - time);
		gettimeofday(&current_time, NULL);
		time = (current_time.tv_sec - start_time.tv_sec) * 1000
			+ (current_time.tv_usec - start_time.tv_usec) / 1000;
		ft_print_everything(philo, 4, time);
		ft_stop_all(philo);
	}
	else
		return ;
}

int	ft_check_death(struct timeval start_time, t_philo *philo)
{
	struct timeval	current_time;
	int				time;

	gettimeofday(&current_time, NULL);
	if (!philo->t_last_check.tv_usec)
		time = (current_time.tv_sec - start_time.tv_sec) * 1000
			+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	else
		time = (current_time.tv_sec - philo->t_last_check.tv_sec) * 1000
			+ (current_time.tv_usec - philo->t_last_check.tv_usec) / 1000;
	if (time >= philo->t_t_death)
	{
		ft_print_everything(philo, 4, time);
		ft_stop_all(philo);
		return (1);
	}
	return (0);
}

int	ft_check_death_v2(struct timeval start_time, t_philo *philo)
{
	struct timeval	current_time;
	int				time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	if (time >= philo->t_t_death || (time + philo->t_t_live
			- philo->last_sleep_time) >= philo->t_t_death)
	{
		ft_print_everything(philo, 4, time);
		ft_stop_all(philo);
		return (1);
	}
	return (0);
}
