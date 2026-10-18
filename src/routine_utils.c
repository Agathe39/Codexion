/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:59:40 by agathe            #+#    #+#             */
/*   Updated: 2026/10/18 16:14:12 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	stop(struct s_data *data, struct s_coder *coder)
{
	delete_ask(coder, data);
	pthread_mutex_unlock(&data->mutex_ask);
}

int	initiate_steps(struct s_data *data, struct s_coder *coder)
{
	delete_ask(coder, data);
	take_dongles(coder);
	pthread_mutex_unlock(&data->mutex_ask);
	compile(coder, data);
	let_dongles(coder, data);
	if (is_stopped(data))
		return (1);
	debug(coder, data);
	if (is_stopped(data))
		return (1);
	refactor(coder, data);
	return (0);
}

void	let_dongles(struct s_coder *coder, struct s_data *data)
{
	long	release;

	pthread_mutex_lock(&data->mutex_ask);
	release = calculate_time(data) + data->dongle_cooldown;
	coder->dongle_left->available = 0;
	coder->dongle_right->available = 0;
	coder->dongle_left->cooldown_end = release;
	coder->dongle_right->cooldown_end = release;
	pthread_cond_broadcast(&data->cond);
	pthread_mutex_unlock(&data->mutex_ask);
}

void	take_dongles(struct s_coder *coder)
{
	coder->dongle_left->available = 1;
	coder->dongle_right->available = 1;
}

void	delete_ask(struct s_coder *coder, struct s_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = data->heap->size;
	while (i < size)
	{
		if (coder->id == data->heap->asks[i].coder_id)
			break ;
		i++;
	}
	if (i == size)
		return ;
	while (i < size - 1)
	{
		data->heap->asks[i] = data->heap->asks[i + 1];
		i++;
	}
	data->heap->size--;
	pthread_cond_broadcast(&data->cond);
}
