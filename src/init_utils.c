/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:16:43 by agathe            #+#    #+#             */
/*   Updated: 2026/10/14 16:53:50 by aeuvrard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_args(struct s_data *data, char **arg)
{
	data->nbr_coders = atoi(arg[1]);
	data->time_to_burnout = atoi(arg[2]);
	data->time_to_compile = atoi(arg[3]);
	data->time_to_debug = atoi(arg[4]);
	data->time_to_refactor = atoi(arg[5]);
	data->nbr_compilation_required = atoi(arg[6]);
	data->dongle_cooldown = atoi(arg[7]);
	data->stopped = 0;
	data->algo_choice = arg[8];
}

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
