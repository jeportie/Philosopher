/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:18:44 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/14 21:33:56 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h> 
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

# define DEBUG 0 

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define RESET   "\033[0m"

# define DEAD 0
# define THINK 1
# define LEFT 2
# define RIGHT 3
# define EAT 4
# define SLEEP 5
# define STOP 6

# define EVEN 0
# define ODD 1

typedef struct timeval	t_timeval;
typedef struct s_simu	t_simu;
typedef struct s_philo	t_philo;
typedef struct s_rdonly	t_rdonly;
typedef struct s_sync	t_sync;

typedef struct s_rdonly
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_meals;
	long long	start_time;
}				t_rdonly;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				meals_eaten;
	long long		last_meal_time;
	t_rdonly		*rdonly;
	t_simu			*simu;

	long long		start_offset;
}					t_philo;

typedef struct s_simu
{
	t_philo		*philos;
	t_rdonly	rdonly;

	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_meals;
	sem_t		*sem_death;
}				t_simu;

/* Parsing & Validation */
bool		ft_check_args(int ac, char **av);

/* Init Bonus */
bool		ft_init_bonus(t_simu *simu, int ac, char **av);
bool		ft_open_semaphores(t_simu *simu);

/* Forking & Execution */
bool		ft_launch_processes(t_simu *simu);
void		ft_wait_for_processes(t_simu *simu);
void		ft_kill_all(t_simu *simu);

/* Routine */
void		ft_routine(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep_and_think(t_philo *philo);

/* Timing & Utils */
long long	ft_get_time_ms(void);
void		ft_precise_usleep(long long usec);
int			ft_atoi(const char *nptr);
void		ft_perror(char *str);
void		ft_print_state(t_philo *philo, int state);

/* Other Helpers */
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_issign(int c, int *sign);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
bool		ft_is_int(char *nptr);

#endif /*PHILO_H*/
