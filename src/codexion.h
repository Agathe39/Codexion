/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:44:00 by agathe            #+#    #+#             */
/*   Updated: 2026/09/26 15:07:39 by agathe           ###   ########.fr       */
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

typedef struct s_dungle
{
	int	nbr;
	int	available;
}	t_dungle;

typedef struct s_coder
{
	int			id;
	long int	last_compile_start;
	int			nbr_compiles;
	t_dungle	*dungle_right;
	t_dungle	*dungle_left;
	char		*state;
	pthread_t	thread;
}	t_coder;

typedef struct s_data
{
	t_coder			*coders;
	t_dungle		*dungles;
	t_heap			*heap;
	int				nbr_coders;
	int				nbr_compilation_required;
	long			time_to_burnout;
	int				stopped;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	mutex_dungles;
	pthread_cond_t	cond;
}	t_data;

int				parsing(int nbr_arg, char **args);
long			calculate_time(void);
struct s_coder	*create_coder(int nbr_coder, struct s_dungle *dongles);
struct s_dungle	*create_dungle(int nbr_dungle);
void			*monitor_control(void *arg);
struct s_data	*recup_data(char *arg, struct s_coder **coder,
					struct s_dungle **dungle);

#endif
