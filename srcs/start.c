/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:25:34 by dyao              #+#    #+#             */
/*   Updated: 2024/11/24 22:38:26 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_thread(t_philo *philo)
{
	struct timeval	start_time;
	struct timeval	temp;
	int				time;

	gettimeofday(&start_time, NULL);
	ft_taken_fork(start_time, philo);
	if (ft_check_death(start_time, philo))
		return (1);
	ft_print_eating(start_time, philo);
	gettimeofday(&temp, NULL);
	time = ft_print_sleeping(start_time, philo);
	if (ft_check_death_v2(temp, philo))
		return (1);
	pthread_mutex_lock(philo->mutex);
	philo->t_t_live += time;
	philo->t_last_check = temp;
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->mutex_for_death);
	if (philo->live_status == 1)
	{
		pthread_mutex_unlock(philo->mutex_for_death);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex_for_death);
	return (0);
}

void	*ft_print(void *args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)args;
	if (philo->n_philo % 2 == 1)
	{
		ft_print_everything(philo, 3, philo->t_t_live);
		usleep(philo->t_t_eat / 2);
	}
	while (1)
	{
		if (philo->n_t_eat != 0 && i == philo->n_t_eat)
			break ;
		if (ft_print_thread(philo) == 1)
			return (NULL);
		i++;
	}
	return (NULL);
}

void	ft_start(int number, t_philo *philo)
{
	pthread_t		*threads;
	int				i;

	i = 0;
	threads = malloc(number * sizeof(pthread_t));
	while (i < number)
	{
		while (1)
		{
			if (philo->n_philo == i + 1)
				break ;
			philo = philo->next;
		}
		if (pthread_create(&threads[i], NULL, ft_print, (void *)philo) != 0)
			perror("Thread creation failed");
		i++;
	}
	i = 0;
	while (i < number)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return ;
}

// int	ft_print_thread(t_philo *philo)
// {
// 	struct timeval	start;
// 	struct timeval	end;
// 	pthread_mutex_t	mutex;
// 	static int		time;

// 	if (pthread_mutex_init(&mutex, NULL) != 0)
// 	{
// 		printf("Mutex initialization failed\n");
// 		return (1);
// 	}
// 	if (philo->t_t_live > philo->t_t_death)
// 		return (1);
// 	gettimeofday(&start, NULL);
// 	pthread_mutex_lock(&mutex);
// 	philo->next->fork++;
// 	philo->fork++;
// 	gettimeofday(&end, NULL);
// 	time = end.tv_usec - start.tv_usec;
// 	printf("%d %d has taken a fork\n", time, philo->n_philo);
// 	gettimeofday(&end, NULL);
// 	time = end.tv_usec - start.tv_usec;
// 	printf("%d %d is		eating\n", time, philo->n_philo);
// 	ft_usleep(philo->t_t_eat);
// 	gettimeofday(&end, NULL);
// 	time = end.tv_usec - start.tv_usec;
// 	philo->next->fork--;
// 	philo->fork--;
// 	printf("%d %d is			sleeping\n", time, philo->n_philo);
// 	ft_usleep(philo->t_t_sleep);
// 	gettimeofday(&end, NULL);
// 	time = end.tv_usec - start.tv_usec;
// 	printf("%d %d is				thinking\n", time, philo->n_philo);
// 	pthread_mutex_unlock(&mutex);
// 	return (0);
// }