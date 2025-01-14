/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:02:44 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/12 14:04:47 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_define_forks(t_philo *philo, t_forks **fone,
		t_forks **ftwo, bool state)
{
	if (state == EVEN)
	{
		*fone = philo->left_fork;
		*ftwo = philo->right_fork;
	}
	else
	{
		*fone = philo->right_fork;
		*ftwo = philo->left_fork;
	}
}

void	ft_actualise_forks(t_forks *fork, bool value, int id)
{
	pthread_mutex_lock(&fork->lock_mutex);
	fork->is_locked = value;
	fork->philo_id = id;
	pthread_mutex_unlock(&fork->lock_mutex);
}
