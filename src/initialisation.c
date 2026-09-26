/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:25:25 by agathe            #+#    #+#             */
/*   Updated: 2026/09/26 16:10:31 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


struct s_heap	*creat_heap(int nbr_coders)
{
	struct s_heap	*heap;

	heap = malloc(sizeof(struct s_heap) * 1);
	if (!heap)
		return (NULL);
	heap->asks = malloc(sizeof(struct s_ask) * nbr_coders);
	heap->size = 0;

	return (heap);
}

struct s_data	*recup_data(char **arg, struct s_coder **coder,
	struct s_dungle **dungle)
{
	struct s_data	*data;

	data = malloc(sizeof(struct s_data) * 1);
	if (!data)
		return (NULL);
	data->coders = *coder;
	data->dungles = *dungle;
	data->heap = creat_heap(atoi(arg[1]));
	data->nbr_coders = atoi(arg[1]);
	data->nbr_compilation_required = atoi(arg[6]);
	data->time_to_burnout = atoi(arg[2]);
	data->stopped = 0;
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->log_mutex, NULL);
	pthread_mutex_init(&data->mutex_dungles, NULL);
	pthread_cond_init(&data->cond, NULL);
	data->algo_choice = arg[8];

	return (data);
}

long	calculate_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

struct s_coder	*create_coder(int nbr_coder, struct s_dungle *dongles)
{
	struct s_coder	*coders;
	int				i;

	coders = malloc(sizeof(t_coder) * nbr_coder);
	if (!coders)
		return (NULL);
	i = 1;
	while (i <= nbr_coder)
	{
		coders[i - 1].id = i;
		coders[i - 1].last_compile_start = calculate_time();
		coders[i - 1].nbr_compiles = 0;
		coders[i - 1].dungle_left = &dongles[i - 1];
		coders[i - 1].dungle_right = &dongles[(i - 2 + nbr_coder) % nbr_coder];
		coders[i - 1].state = "wait";
		i++;
	}
	return (coders);
}

struct s_dungle	*create_dungle(int nbr_dungle)
{
	struct s_dungle	*dungles;
	int				i;

	dungles = malloc(sizeof(t_dungle) * nbr_dungle);
	if (!dungles)
		return (NULL);
	i = 1;
	while (i <= nbr_dungle)
	{
		dungles[i - 1].nbr = i;
		dungles[i - 1].available = 0;
		i++;
	}
	return (dungles);
}
