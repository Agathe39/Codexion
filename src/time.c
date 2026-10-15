/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 16:25:10 by aeuvrard          #+#    #+#             */
/*   Updated: 2026/10/15 16:23:34 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	now_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void	ft_sleep_ms(long ms)
{
	struct timespec	ts;

	if (ms <= 0)
		return ;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

long	calculate_time(struct s_data *data)
{
	return (now_ms() - data->start_time);
}

void	cond_wait_until(struct s_data *data, long deadline)
{
	struct timespec	ts;
	long			remaining;

	if (deadline < 0)
	{
		pthread_cond_wait(&data->cond, &data->mutex_ask);
		return ;
	}
	remaining = deadline - calculate_time(data);
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += remaining / 1000;
	ts.tv_nsec += (remaining % 1000) * 1000000;
	if (ts.tv_nsec >= 1000000000L)
	{
		ts.tv_sec += 1;
		ts.tv_nsec -= 1000000000L;
	}
	pthread_cond_timedwait(&data->cond, &data->mutex_ask, &ts);
}
