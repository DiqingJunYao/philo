/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:37:53 by dyao              #+#    #+#             */
/*   Updated: 2024/11/13 22:41:39 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_nod(t_philo *philo)
{
	while (philo)
	{
		printf("this is the time to eat :%d\n", philo->t_t_eat);
		printf("this is the number to eat :%d\n", philo->n_t_eat);
		printf("this is the time to sleep :%d\n", philo->t_t_sleep);
		printf("this is the time to death :%d\n", philo->t_t_death);
		printf("this is the time to live :%d\n", philo->t_t_live);
		printf("this is the fork :%d\n", philo->fork);
		printf("this is the number of philo :%d\n", philo->n_philo);
		philo = philo->next;
	}
}

void	ft_free(t_philo *philo)
{
	t_philo	*temp;

	while (philo)
	{
		temp = philo->next;
		free(philo);
		philo = temp;
	}
}

void	ft_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Mutex initialization failed\n");
		return ;
	}
}

int	main(int argc, char	**argv)
{
	t_philo			*philo;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_for_fork;
	pthread_mutex_t	mutex_for_death;

	ft_mutex_init(&mutex);
	ft_mutex_init(&mutex_for_fork);
	ft_mutex_init(&mutex_for_death);
	if (argc == 6 || argc == 5)
	{
		if (ft_atoi(argv[1]) < 1)
			return (0);
		philo = ft_input(argv, &mutex, &mutex_for_fork, &mutex_for_death);
		ft_start(ft_atoi(argv[1]), philo);
		pthread_mutex_destroy(&mutex);
	}
	else
	{
		printf("you need to input everthing correct!\n");
		return (0);
	}
}
