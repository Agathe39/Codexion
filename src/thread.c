/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:49:28 by agathe            #+#    #+#             */
/*   Updated: 2026/10/09 17:49:54 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	create_threads(struct s_data *data)
{
	int	i;
	int threads_create;

	i = 0;
	threads_create = 0;
	while (i < data->nbr_coders)
	{
		if (pthread_create(&data->coders[i].thread, NULL, &coder_routine,
			&data->coders[i]) == 0)
				threads_create += 1;
		i++;
	}
	return (threads_create);
}
int	create_thread_mutex(struct s_data *data)
{
	pthread_mutex_init(&data->log_mutex, NULL);
	data->mutex_init += 1;
	pthread_mutex_init(&data->mutex_ask, NULL);
	data->mutex_init += 1;
	pthread_cond_init(&data->cond, NULL);
	data->mutex_init += 1;
	if (pthread_create(&data->monitor, NULL, &monitor_control, data) != 0)
		return (1);
	data->monitor_created += 1;
	data->nbr_threads = create_threads(data);
	if (data->nbr_threads != data->nbr_coders)
		return (1);
	return (0);
}
