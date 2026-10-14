/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 17:48:49 by agathe            #+#    #+#             */
/*   Updated: 2026/10/14 16:48:30 by aeuvrard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	stop_generation(struct s_data *data)
{
	pthread_mutex_lock(&data->mutex_ask);
	data->stopped = 1;
	pthread_cond_broadcast(&data->cond);
	pthread_mutex_unlock(&data->mutex_ask);
}

void	clean_threads(struct s_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_threads)
	{
		pthread_join(data->coders[i].thread, NULL);
		i++;
	}
}

void	clean_mutex(struct s_data *data)
{
	if (data->mutex_init >= 1)
		pthread_mutex_destroy(&data->log_mutex);
	if (data->mutex_init >= 2)
		pthread_mutex_destroy(&data->mutex_ask);
	if (data->mutex_init >= 3)
		pthread_cond_destroy(&data->cond);
}

void	clean_up(struct s_data *data)
{
	if (!data)
		return ;
	if (data->mutex_init > 2)
		stop_generation(data);
	if (data->monitor_created == 1)
		pthread_join(data->monitor, NULL);
	clean_threads(data);
	if (data->mutex_init > 0)
		clean_mutex(data);
	if (data->heap)
	{
		free(data->heap->asks);
		free(data->heap);
	}
	if (data->coders)
		free(data->coders);
	if (data->dongles)
		free(data->dongles);
	free(data);
}
