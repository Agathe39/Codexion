/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:25:25 by agathe            #+#    #+#             */
/*   Updated: 2026/10/12 17:36:18 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_dungles_coders_heap(struct s_data *data, char **arg)
{
	data->dungles = create_dungle(atoi(arg[1]));
	if (!data->dungles)
	{
		clean_up(data);
		return (1);
	}
	data->coders = create_coder(atoi(arg[1]), data->dungles);
	if (!data->coders)
	{
		clean_up(data);
		return (1);
	}
	data->heap = creat_heap(atoi(arg[1]));
	if (!data->heap)
	{
		clean_up(data);
		return (1);
	}
	return (0);
}

struct s_data	*recup_data(struct s_data *data, char **arg)
{
	data->nbr_threads = 0;
	data->monitor_created = 0;
	data->mutex_init = 0;
	data->start_time = now_ms();
	data->dungles = create_dungle(atoi(arg[1]));
	if (init_dungles_coders_heap(data, arg) == 1)
	{
		clean_up(data);
		return (NULL);
	}
	init_args(data, arg);
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
