/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:35:28 by dyao              #+#    #+#             */
/*   Updated: 2024/11/14 21:28:30 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_all_fork(t_philo *philo)
{
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
