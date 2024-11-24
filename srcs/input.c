/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:56:19 by dyao              #+#    #+#             */
/*   Updated: 2024/11/24 21:33:43 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_fill(char **argv, int i)
{
	t_philo			*temp;

	temp = malloc(sizeof(t_philo));
	if (!temp)
		return (NULL);
	temp->t_t_eat = ft_atoi(argv[3]);
	if (argv[5])
		temp->n_t_eat = ft_atoi(argv[5]);
	else
		temp->n_t_eat = 0;
	temp->t_t_sleep = ft_atoi(argv[4]);
	temp->t_t_death = ft_atoi(argv[2]);
	temp->t_t_live = 0;
	temp->fork = 0;
	temp->last_sleep_time = 0;
	temp->n_philo = i;
	temp->live_status = 0;
	temp->next = NULL;
	return (temp);
}

void	ft_fill_mutex(t_philo *philo, pthread_mutex_t *mutex,
			pthread_mutex_t *mutex_for_fork, pthread_mutex_t *mutex_for_death)
{
	philo->mutex = mutex;
	philo->mutex_for_fork = mutex_for_fork;
	philo->mutex_for_death = mutex_for_death;
}

t_philo	*ft_input(char **argv, pthread_mutex_t *mutex,
			pthread_mutex_t *mutex_for_fork, pthread_mutex_t *mutex_for_death)
{
	t_philo	*first;
	t_philo	*temp;
	t_philo	*temp1;
	int		i;
	int		j;

	j = 2;
	i = ft_atoi(argv[1]);
	temp = ft_fill(argv, 1);
	ft_fill_mutex(temp, mutex, mutex_for_fork, mutex_for_death);
	first = temp;
	while (i > 1)
	{
		temp1 = temp;
		temp = ft_fill(argv, j);
		ft_fill_mutex(temp, mutex, mutex_for_fork, mutex_for_death);
		temp->pre = temp1;
		temp1->next = temp;
		i--;
		j++;
	}
	temp->next = first;
	first->pre = temp;
	return (first);
}

int	ft_atoi(const char *str)
{
	int				num;
	int				i;
	int				np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			np = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return ((np * num));
}
