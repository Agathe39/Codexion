/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:25:25 by agathe            #+#    #+#             */
/*   Updated: 2026/10/09 09:14:45 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

struct s_heap	*creat_heap(int nbr_coders)
{
	struct s_heap	*heap;

	heap = malloc(sizeof(struct s_heap) * 1);
	if (!heap)
	{
		free(heap);
		return (NULL);
	}
	heap->asks = malloc(sizeof(struct s_ask) * nbr_coders);
	if (!heap->asks)
	{
		free(heap);
		return (NULL);
	}
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

struct s_data	*recup_data(struct s_data *data, char **arg)
{
	data->nbr_threads = 0;
	data->monitor_created = 0;
	data->mutex_init = 0;
	data->start_time = now_ms();
	data->dungles = create_dungle(atoi(arg[1]));
	if (!data->dungles)
	{
		clean_up(data);
		return (NULL);
	}
	data->coders = create_coder(atoi(arg[1]), data->dungles);
	if (!data->coders)
	{
		clean_up(data);
		return (NULL);
	}
	data->heap = creat_heap(atoi(arg[1]));
	if (!data->heap)
	{
		clean_up(data);
		return (NULL);
	}
	data->nbr_coders = atoi(arg[1]);
	data->time_to_burnout = atoi(arg[2]);
	data->time_to_compile = atoi(arg[3]);
	data->time_to_debug = atoi(arg[4]);
	data->time_to_refactor = atoi(arg[5]);
	data->nbr_compilation_required = atoi(arg[6]);
	data->dungle_cooldown = atoi(arg[7]);
	data->stopped = 0;
	data->algo_choice = arg[8];
	init_data_coders(data);
	if (create_thread_mutex(data) != 0)
	{
		clean_up(data);
		return (NULL);
	}
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
