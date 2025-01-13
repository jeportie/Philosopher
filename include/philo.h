/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:23:49 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/16 09:06:21 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h> 
# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>

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
typedef pthread_mutex_t	t_mtx;

typedef struct s_forks
{
	t_mtx	fork_mutex;

	t_mtx	lock_mutex;
	bool	is_locked;
	int		philo_id;

	t_philo	*left_philo;
	t_philo	*right_philo;
	t_mtx	request_mutex;
}				t_forks;

typedef struct s_pmtx
{
	t_mtx	pmutex;
	bool	is_locked;
}				t_pmtx;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	int				meals_eaten;

	long long		last_meal_time;
	t_mtx			time_mutex;

	bool			finish_flag;
	t_mtx			finish_mutex;

	t_forks			*right_fork;
	t_forks			*left_fork;
	t_rdonly		*rdonly;
	t_sync			*mtdata;
	t_simu			*simu;
}					t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	t_rdonly		*rdonly;
	t_sync			*mtdata;
	t_simu			*simu;
}					t_monitor;

typedef struct s_rdonly
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_meals;
	long long	start_time;
}				t_rdonly;

typedef struct s_sync
{
	t_pmtx		print_mutex;

	int			philos_full;
	t_mtx		meal_mutex;

	int			go_count;
	t_mtx		go_mutex;
	bool		start_flag;
	t_mtx		start_mutex;

	bool		stop_flag;
	t_mtx		stop_mutex;
	int			end_count;
	t_mtx		end_mutex;
}				t_sync;

typedef struct s_simu
{
	t_philo		*philos;
	t_forks		*forks;
	t_rdonly	rdonly;
	t_sync		mtdata;
	t_monitor	monitor;
}				t_simu;

/*Parsing*/
bool		ft_is_int(char *nptr);
bool		ft_check_args(int ac, char **av);

/*Init*/
bool		ft_safe_simulation_init(t_simu *simu, int ac, char **av);
bool		ft_init_mtdata(t_simu *simu);
bool		ft_init_rdonly(t_simu *simu, int ac, char **av);
bool		ft_init_philos(t_simu *simu);
void		ft_init_monitor(t_simu *simu);
bool		ft_init_forks(t_simu *simu);
bool		ft_init_threads(t_simu *simu);

/*Simulation*/
void		ft_stop_threads(t_simu *simu);
void		ft_start_simulation(t_simu *simu);
void		ft_wait_threads_to_stop(t_simu *simu);
void		*ft_routine(void *arg);

/*Philosopher Threads*/
void		ft_simulation_loop(t_philo *philo);
bool		ft_pick_up_forks(t_philo *philo);
bool		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_release_forks(t_philo *philo);

/*Forks MGMT*/
void		ft_fork_pick(t_philo *philo, bool state);
bool		ft_fork_request(int philo_id, t_forks *fork);
void		ft_define_forks(t_philo *philo, t_forks **fone,
				t_forks **ftwo, bool state);
void		ft_actualise_forks(t_forks *fork, bool value, int id);
void		ft_release(t_philo *philo, bool state);

/*Monitoring thread*/
bool		ft_check_if_dead(t_philo *philo);
void		*ft_monitor(void *arg);
void		ft_wait_for_start(t_mtx *mutex, bool *start);

/*Utilities*/
void		ft_perror(char *str);
long long	ft_get_time_ms(void);
void		ft_precise_usleep(long long usec);
void		ft_free_philos(t_simu *simu);
void		ft_update_meal_time(t_philo *philo);
void		ft_wait_for_stop(t_mtx *mutex, bool *start);
void		mtx_set_llong(t_mtx *mutex, long long *dest, long long value);
void		mtx_increment_int(t_mtx *mutex, int *dest);

/*42_ft*/
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_issign(int c, int *sign);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);

/*Printing*/
void		ft_print_state(t_philo *philo, int state);
void		ft_print_intro(void);
void		ft_print_parsing(t_simu simu);
void		ft_print_start_stop(t_simu *simu, bool choice);

#endif /*PHILO_H*/
