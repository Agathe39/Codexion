/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 17:48:49 by agathe            #+#    #+#             */
/*   Updated: 2026/10/09 17:52:14 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	clean_up(struct s_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;

	if (data->mutex_init > 2)
	{
		pthread_mutex_lock(&data->mutex_ask);
		data->stopped = 1;
		pthread_cond_broadcast(&data->cond);
		pthread_mutex_unlock(&data->mutex_ask);
	}
	
	if (data->monitor_created == 1)
		pthread_join(data->monitor, NULL);

	while (i < data->nbr_threads)
	{
		pthread_join(data->coders[i].thread, NULL);
		i++;
	}

	if (data->mutex_init >= 1)
		pthread_mutex_destroy(&data->log_mutex);
	if (data->mutex_init >= 2)
		pthread_mutex_destroy(&data->mutex_ask);
	if (data->mutex_init >= 3)
		pthread_cond_destroy(&data->cond);
	
	if (data->heap)
	{
		free(data->heap->asks);
		free(data->heap);
	}
	if (data->coders)
		free(data->coders);
	if (data->dungles)
		free(data->dungles);

	free(data);
}
