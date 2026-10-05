/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:25:25 by agathe            #+#    #+#             */
/*   Updated: 2026/10/05 16:37:19 by aeuvrard         ###   ########.fr       */
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
	if (!heap->asks)
		return (NULL);
	heap->size = 0;
	return (heap);
}

void	init_data_coders(struct s_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_coders)
	{
		data->coders[i].data = data;
		data->coders[i].last_compile_start = calculate_time(data);
		i++;
	}
}

struct s_data	*recup_data(char **arg, struct s_coder **coder,
	struct s_dungle **dungle)
{
	struct s_data	*data;

	data = malloc(sizeof(struct s_data) * 1);
	if (!data)
		return (NULL);
	data->start_time = now_ms();
	data->coders = *coder;
	data->dungles = *dungle;
	data->heap = creat_heap(atoi(arg[1]));
	data->nbr_coders = atoi(arg[1]);
	data->time_to_burnout = atoi(arg[2]);
	data->time_to_compile = atoi(arg[3]);
	data->time_to_debug = atoi(arg[4]);
	data->time_to_refactor = atoi(arg[5]);
	data->nbr_compilation_required = atoi(arg[6]);
	data->dungle_cooldown = atoi(arg[7]);
	data->stopped = 0;
	pthread_mutex_init(&data->log_mutex, NULL);
	pthread_mutex_init(&data->mutex_ask, NULL);
	pthread_cond_init(&data->cond, NULL);
	data->algo_choice = arg[8];
	init_data_coders(data);
	return (data);
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
		coders[i - 1].nbr_compiles = 0;
		coders[i - 1].dungle_left = &dongles[i - 1];
		coders[i - 1].dungle_right = &dongles[(i - 2 + nbr_coder) % nbr_coder];
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
