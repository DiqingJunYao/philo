/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:37:53 by dyao              #+#    #+#             */
/*   Updated: 2024/11/24 22:54:26 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_nod(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	printf("this is the time to eat :%d\n", philo->t_t_eat);
	printf("this is the number to eat :%d\n", philo->n_t_eat);
	printf("this is the time to sleep :%d\n", philo->t_t_sleep);
	printf("this is the time to death :%d\n", philo->t_t_death);
	printf("this is the time to live :%d\n", philo->t_t_live);
	printf("this is the fork :%d\n", philo->fork);
	printf("this is the number of philo :%d\n", philo->n_philo);
	printf("this is the last eat time of philo :%d\n",
		philo->last_eat_time);
	pthread_mutex_unlock(philo->mutex);
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

int	ft_check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
	{
		printf("Too many philo, please make it less than 200!\n");
		return (1);
	}
	return (0);
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
		if (ft_check_input(argv))
			return (0);
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
