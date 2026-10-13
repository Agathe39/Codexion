/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 11:21:41 by agathe            #+#    #+#             */
/*   Updated: 2026/10/13 17:26:04 by aeuvrard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_stopped(struct s_data *data)
{
	int	res;

	pthread_mutex_lock(&data->mutex_ask);
	res = data->stopped;
	pthread_mutex_unlock(&data->mutex_ask);
	return (res);
}

int	verif_burn_out(int i, long time, t_data *d)
{
	if ((time - d->coders[i].last_compile_start) >= d->time_to_burnout)
	{
		d->stopped = 1;
		pthread_cond_broadcast(&d->cond);
		pthread_mutex_lock(&d->log_mutex);
		printf("%ld %d burned out\n", time, d->coders[i].id);
		pthread_mutex_unlock(&d->log_mutex);
		return (1);
	}
	return (0);
}

int	verif_compile_burnout(t_data *d, long int time)
{
	int			i;
	int			compile;

	i = 0;
	compile = 0;
	while (i < d->nbr_coders)
	{
		if (d->coders[i].nbr_compiles >= d->nbr_compilation_required)
		{
			i++;
			compile ++;
			continue ;
		}
		if (verif_burn_out(i, time, d) == 1)
			return (1);
		i++;
	}
	return (compile);
}

int	monitor_check(t_data *d)
{
	int	compile;

	pthread_mutex_lock(&d->mutex_ask);
	compile = verif_compile_burnout(d, calculate_time(d));
	if (compile == -1)
	{
		pthread_mutex_unlock(&d->mutex_ask);
		return (1);
	}
	if (compile >= d->nbr_coders)
	{
		d->stopped = 1;
		pthread_cond_broadcast(&d->cond);
		pthread_mutex_unlock(&d->mutex_ask);
		return (1);
	}
	pthread_mutex_unlock(&d->mutex_ask);
	return (0);
}

void	*monitor_control(void *arg)
{
	t_data	*d;

	d = (t_data *)arg;
	while (!is_stopped(d))
	{
		if (monitor_check(d) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
