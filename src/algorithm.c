/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:16:26 by agathe            #+#    #+#             */
/*   Updated: 2026/10/17 13:44:48 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	verif_diponibility_dongles(int coder_id, struct s_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_coders)
	{
		if (data->coders[i].id == coder_id)
		{
			// if ((data->coders[i].dongle_left->available == 0 && data->coders[i].dongle_left->cooldown_end >= calculate_time(data))
			//  && (data->coders[i].dongle_right->available == 0 && data->coders[i].dongle_right->cooldown_end >= calculate_time(data)))
			if (dongle_is_ready(data->coders[i].dongle_left, data) == 1 && dongle_is_ready(data->coders[i].dongle_right, data) == 1)
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}

struct s_coder	*search_coder(int coder_id, struct s_coder *coders,
	int nbr_coders)
{
	int	i;

	i = 0;
	while (i < nbr_coders)
	{
		if (coder_id == coders[i].id)
			return (&coders[i]);
		i++;
	}
	return (NULL);
}

int	use_edf(struct s_data *data)
{
	int		i;
	int		best;
	long	min_deadline;

	if (data->heap->size <= 0)
		return (-1);
	best = 0;
	min_deadline = data->heap->asks[0].deadline;
	i = 1;
	while (i < data->heap->size)
	{
		if (data->heap->asks[i].deadline < min_deadline)
		{
			min_deadline = data->heap->asks[i].deadline;
			best = i;
		}
		i++;
	}
	return (data->heap->asks[best].coder_id);
}

int	use_fifo(struct s_data *data)
{
	int		i;
	int		best;
	long	min_arrival;

	if (data->heap->size <= 0)
		return (-1);
	best = -1;
	min_arrival = data->heap->asks[0].arrival_time;
	i = 0;
	while (i < data->heap->size)
	{
		if (verif_diponibility_dongles(data->heap->asks[i].coder_id, data) == 0)
		{
			if (best == -1)
				best = i;
			if (data->heap->asks[i].arrival_time < min_arrival)
			{
				min_arrival = data->heap->asks[i].arrival_time;
				best = i;
			}
		}
		i++;
	}
	if (best == -1)
		return (best);
	return (data->heap->asks[best].coder_id);
}

struct s_coder	*algorithm(struct s_data *data)
{
	struct s_coder	*coder;
	int				coder_id;

	if (strcmp(data->algo_choice, "fifo") == 0)
		coder_id = use_fifo(data);
	else
		coder_id = use_edf(data);
	coder = search_coder(coder_id, data->coders, data->nbr_coders);
	return (coder);
}
