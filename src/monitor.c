/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:00:00 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/12 21:51:10 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NOTE: MONITOR THREAD */

#include "../include/philo.h"
/*
 * NOTE:
 * This function is the monitor routine. 
 * First part : check if a philo died
 * Second part : cehck if all philos ended their routine
 */

static bool	ft_mon_routine(t_monitor *mon)
{
	int	i;
	int	wait_philos;

	i = 0;
	while (i < mon->rdonly->num_philo)
	{
		if (ft_check_if_dead(&mon->simu->philos[i]))
			return (false);
		i++;
	}
	pthread_mutex_lock(&mon->mtdata->end_mutex);
	wait_philos = mon->mtdata->end_count;
	pthread_mutex_unlock(&mon->mtdata->end_mutex);
	if (wait_philos == mon->rdonly->num_philo)
	{
		pthread_mutex_lock(&mon->mtdata->stop_mutex);
		mon->mtdata->stop_flag = true;
		pthread_mutex_unlock(&mon->mtdata->stop_mutex);
		return (false);
	}
	return (true);
}

/*
 * NOTE:
 * This function is the monitor thread. 
 * First part : sync start loop
 * Second part : monitor routine
 * Last part : sync stop loop and print unlock
 * 	-> Monitor thread is stopped after all the philos are joined
 * 	-> This let us protect the print after a philo died by unlocking 
 * 	the print mutex after all philos are joined.
 */

void	*ft_monitor(void *arg)
{
	t_monitor	*mon;

	mon = (t_monitor *)arg;
	if (!mon)
		return (NULL);
	mtx_increment_int(&mon->mtdata->go_mutex, &mon->mtdata->go_count);
	ft_wait_for_start(&mon->mtdata->start_mutex, &mon->mtdata->start_flag);
	while (1)
	{
		if (!ft_mon_routine(mon))
			break ;
		ft_precise_usleep(100);
	}
	mtx_increment_int(&mon->mtdata->end_mutex, &mon->mtdata->end_count);
	ft_wait_threads_to_stop(mon->simu);
	if (mon->rdonly->num_philo > 1)
		ft_wait_for_stop(&mon->mtdata->start_mutex, &mon->mtdata->start_flag);
	if (mon->mtdata->print_mutex.is_locked == true)
		pthread_mutex_unlock(&mon->mtdata->print_mutex.pmutex);
	return (NULL);
}

void	ft_wait_for_stop(t_mtx *mutex, bool *start)
{
	pthread_mutex_lock(mutex);
	while ((*start) == true)
	{
		pthread_mutex_unlock(mutex);
		ft_precise_usleep(100);
		pthread_mutex_lock(mutex);
	}
	pthread_mutex_unlock(mutex);
}

/*
 * NOTE:
 * This function checks is the philo died. 
 * First function : used to be sure not to check after a philo 
 * 					finished its routine
 * Second function : time comparison.
 */

bool	ft_check_if_already_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->finish_mutex);
	if (philo->finish_flag == true)
	{
		pthread_mutex_unlock(&philo->finish_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->finish_mutex);
	return (true);
}

bool	ft_check_if_dead(t_philo *philo)
{
	long long	time;
	long long	last_meal;

	if (!ft_check_if_already_finished(philo))
		return (false);
	pthread_mutex_lock(&philo->time_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_lock(&philo->mtdata->stop_mutex);
	if (philo->mtdata->stop_flag == true)
		return (true);
	pthread_mutex_unlock(&philo->mtdata->stop_mutex);
	if (ft_get_time_ms() - philo->rdonly->start_time <= 5)
		time = ft_get_time_ms() - philo->rdonly->start_time;
	else
		time = ft_get_time_ms() - last_meal;
	if (time >= philo->rdonly->time_to_die)
	{
		pthread_mutex_lock(&philo->mtdata->stop_mutex);
		philo->mtdata->stop_flag = true;
		pthread_mutex_unlock(&philo->mtdata->stop_mutex);
		ft_print_state(philo, DEAD);
		return (true);
	}
	return (false);
}
