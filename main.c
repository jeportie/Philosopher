/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:50:00 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/20 12:57:18 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int ac, char **av)
{
	t_simu		simu;

	if (!ft_safe_simulation_init(&simu, ac, av))
		return (-1);
	if (DEBUG == true)
		ft_print_parsing(simu);
	ft_start_simulation(&simu);
	ft_free_philos(&simu);
	return (0);
}
