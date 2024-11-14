/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:35:28 by dyao              #+#    #+#             */
/*   Updated: 2024/11/14 18:09:46 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_all_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_for_fork);
	if (philo->fork == true || philo->next->fork == true)
	{
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (0);
	}
}

int	ft_check_next_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_for_fork);
	if (philo->next->fork == true)
	{
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex_for_fork);
		return (0);
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
