/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:44:00 by agathe            #+#    #+#             */
/*   Updated: 2026/10/18 16:04:00 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

typedef struct s_ask
{
	int		coder_id;
	long	arrival_time;
	long	deadline;
}	t_ask;

typedef struct s_heap
{
	t_ask	*asks;
	int		size;
}	t_heap;

typedef struct s_dongle
{
	int		nbr;
	int		available;
	long	cooldown_end;
}	t_dongle;

typedef struct s_data
{
	int				nbr_threads;
	int				monitor_created;
	int				mutex_init;
	long			start_time;
	struct s_coder	*coders;
	t_dongle		*dongles;
	t_heap			*heap;
	int				nbr_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	int				nbr_compilation_required;
	long			dongle_cooldown;
	int				stopped;
	pthread_t		monitor;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	mutex_ask;
	pthread_cond_t	cond;
	char			*algo_choice;
}	t_data;

typedef struct s_coder
{
	int				id;
	long int		last_compile_start;
	int				nbr_compiles;
	t_dongle		*dongle_right;
	t_dongle		*dongle_left;
	pthread_t		thread;
	struct s_data	*data;
}	t_coder;

int				parsing(int nbr_arg, char **args);
long			calculate_time(struct s_data *data);
long			now_ms(void);
void			ft_sleep_ms(long ms);
void			cond_wait_until(struct s_data *data, long deadline);
struct s_coder	*create_coder(int nbr_coder, struct s_dongle *dongles);
struct s_dongle	*create_dongle(int nbr_dongle);
void			*monitor_control(void *arg);
int				is_stopped(struct s_data *data);
struct s_data	*recup_data(struct s_data *data, char **arg);
void			init_args(struct s_data *data, char **arg);
struct s_heap	*creat_heap(int nbr_coders);
void			init_data_coders(struct s_data *data);
int				create_thread_mutex(struct s_data *data);
struct s_coder	*algorithm(struct s_data *data);
int				create_threads(struct s_data *data);
void			*coder_routine(void *arg);
void			delete_ask(struct s_coder *coder, struct s_data *data);
int				initiate_steps(struct s_data *data, struct s_coder *coder);
void			compile(struct s_coder *coder, struct s_data *data);
int				dongle_is_ready(struct s_dongle *dongle, struct s_data *data);
long			dongle_cooldown_deadline(struct s_coder *coder,
					struct s_data *data);
void			debug(struct s_coder *coder, struct s_data *data);
void			refactor(struct s_coder *coder, struct s_data *data);
void			take_dongles(struct s_coder *coder);
void			let_dongles(struct s_coder *coder, struct s_data *data);
void			stop(struct s_data *data, struct s_coder *coder);
void			clean_up(struct s_data *data);

#endif
