/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:06:41 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/15 15:58:06 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NOTE: PHILOSOPHERS THREADS */

#include "../include/philo.h"

void	ft_check_remaining_locks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->lock_mutex);
	if (philo->left_fork->is_locked == true
		&& philo->left_fork->philo_id == philo->id)
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->left_fork->lock_mutex);
	pthread_mutex_lock(&philo->right_fork->lock_mutex);
	if (philo->right_fork->is_locked == true
		&& philo->right_fork->philo_id == philo->id)
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->lock_mutex);
}

static bool	ft_one_philo_case(t_philo *philo)
{
	if (philo->rdonly->num_philo == 1)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		ft_print_state(philo, LEFT);
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		ft_precise_usleep(1000 * philo->rdonly->time_to_die);
		return (true);
	}
	return (false);
}

/* NOTE:
 * Last concurrence optimisation to avoid synchronisation and timming issues
 * that make a philo die when we have an odd number of philosopher and 
 * very small time gaps btwn sleep eat and die.
 * STAGGERING method (see init) : each philo philo will have a offset thinking
 * time : first philo have always an offset of 0, even philos have a 50ms
 * thinking offset and odd philos has 2 times that offset.
 * Avoid the non_deterministic behavious of philos to optimise thinking time.
 * next step after STAGGERING is SCHEDULING like in os systems.
 */

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo)
		return (NULL);
	mtx_increment_int(&philo->mtdata->go_mutex, &philo->mtdata->go_count);
	ft_wait_for_start(&philo->mtdata->start_mutex, &philo->mtdata->start_flag);
	if (philo->start_offset > 0)
		ft_precise_usleep(philo->start_offset * 1000);
	mtx_set_llong(&philo->time_mutex, &philo->last_meal_time, ft_get_time_ms());
	if (ft_one_philo_case(philo))
		return (NULL);
	ft_simulation_loop(philo);
	ft_check_remaining_locks(philo);
	mtx_increment_int(&philo->mtdata->end_mutex, &philo->mtdata->end_count);
	if (DEBUG == true)
		ft_print_state(philo, STOP);
	return (NULL);
}
