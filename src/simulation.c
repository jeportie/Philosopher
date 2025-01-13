/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:51:38 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/16 09:17:17 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * NOTE: THIS IS THE MASTER THREAD
 */

#include "../include/philo.h"

static void	ft_wait_threads_to_start(t_simu *simu)
{
	pthread_mutex_lock(&simu->mtdata.go_mutex);
	while (simu->mtdata.go_count != simu->rdonly.num_philo + 1)
	{
		pthread_mutex_unlock(&simu->mtdata.go_mutex);
		ft_precise_usleep(100);
		pthread_mutex_lock(&simu->mtdata.go_mutex);
	}
	pthread_mutex_unlock(&simu->mtdata.go_mutex);
}

void	ft_wait_threads_to_stop(t_simu *simu)

{
	pthread_mutex_lock(&simu->mtdata.stop_mutex);
	while (simu->mtdata.stop_flag == false)
	{
		pthread_mutex_unlock(&simu->mtdata.stop_mutex);
		ft_precise_usleep(100);
		pthread_mutex_lock(&simu->mtdata.stop_mutex);
	}
	pthread_mutex_unlock(&simu->mtdata.stop_mutex);
}

/* NOTE:
 * MASTER THREAD SYNC ALL THE SLAVE THREADS.
 * 
 * start_flag = false is used to signal the monitor thread to stop
 * ->usefull to lock the print mutex after a philo died and to safely 
 *  unlock it after all philo have been joined.
 */

void	ft_start_simulation(t_simu *simu)
{
	ft_wait_threads_to_start(simu);
	if (DEBUG == true)
		ft_print_start_stop(simu, true);
	pthread_mutex_lock(&simu->mtdata.start_mutex);
	simu->mtdata.start_flag = true;
	simu->rdonly.start_time = ft_get_time_ms();
	pthread_mutex_unlock(&simu->mtdata.start_mutex);
	ft_wait_threads_to_stop(simu);
	ft_stop_threads(simu);
	pthread_mutex_lock(&simu->mtdata.start_mutex);
	simu->mtdata.start_flag = false;
	pthread_mutex_unlock(&simu->mtdata.start_mutex);
	if (simu->monitor.thread)
		pthread_join(simu->monitor.thread, NULL);
	if (DEBUG == true)
		ft_print_start_stop(simu, false);
}
