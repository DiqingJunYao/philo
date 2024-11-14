/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:56:33 by dyao              #+#    #+#             */
/*   Updated: 2024/11/14 18:57:40 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_everything(t_philo *philo, int current_status, int time)
{
	pthread_mutex_lock(philo->mutex);
	pthread_mutex_lock(philo->mutex_for_death);
	if (philo->live_status == 0)
	{
		pthread_mutex_unlock(philo->mutex_for_death);
		if (current_status == 0)
			printf("%d %d has taken a fork\n",
				time + philo->t_t_live, philo->n_philo);
		else if (current_status == 1)
			printf("%d %d is eating\n", time + philo->t_t_live, philo->n_philo);
		else if (current_status == 2)
			printf("%d %d is sleeping\n",
				time + philo->t_t_live, philo->n_philo);
		else if (current_status == 3)
			printf("%d %d is thinking\n",
				time + philo->t_t_live, philo->n_philo);
		else if (current_status == 4)
			printf("%d %d is DEAD\n", time + philo->t_t_live, philo->n_philo);
	}
	else
		pthread_mutex_unlock(philo->mutex_for_death);
	pthread_mutex_unlock(philo->mutex);
}
