/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:44:00 by agathe            #+#    #+#             */
/*   Updated: 2026/09/25 16:38:05 by aeuvrard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <unistd.h>
# include <pthread.h>

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
	int				nbr_coders;
	int				nbr_compilation_required;
	long			time_to_burnout;
	int				stopped;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	mutex_dungles;
}	t_data;

int				parsing(int nbr_arg, char **args);
long			calculate_time(void);
struct s_coder	*create_coder(int nbr_coder, struct s_dungle *dongles);
struct s_dungle	*create_dungle(int nbr_dungle);
void			*monitor_control(void *arg);

#endif
