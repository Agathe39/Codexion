/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 11:21:41 by agathe            #+#    #+#             */
/*   Updated: 2026/10/12 17:09:34 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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

void	*monitor_control(void *arg)
{
	t_data		*d;
	int			compile;
	long int	time;

	d = (t_data *)arg;
	while (!d->stopped)
	{
		time = calculate_time(d);
		pthread_mutex_lock(&d->mutex_ask);
		compile = verif_compile_burnout(d, time);
		if (compile == 1)
		{
			pthread_mutex_unlock(&d->mutex_ask);
			return (NULL);
		}
		if (compile >= d->nbr_coders)
		{
			d->stopped = 1;
			pthread_cond_broadcast(&d->cond);
			pthread_mutex_unlock(&d->mutex_ask);
			return (NULL);
		}
		pthread_mutex_unlock(&d->mutex_ask);
	}
	return (NULL);
}
