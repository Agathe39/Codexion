/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:59:40 by agathe            #+#    #+#             */
/*   Updated: 2026/09/30 10:27:19 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_sleep_ms(long ms)
{
	struct timespec	ts;

	if (ms <= 0)
		return ;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void    let_dungles(struct s_coder *coder, struct s_data *data)
{
    ft_sleep_ms(data->dungle_cooldown);
    
    pthread_mutex_lock(&data->mutex_ask);    
    coder->dungle_left->available = 0;
    coder->dungle_right->available = 0;
    pthread_cond_broadcast(&data->cond);
    pthread_mutex_unlock(&data->mutex_ask);
}

void    take_dungles(struct s_coder *coder,  struct s_data *data)
{
    
    coder->dungle_left->available = 1;
    coder->dungle_right->available = 1;

    pthread_mutex_lock(&data->log_mutex);
    printf("%ld %d %s\n", calculate_time(), coder->id, "has taken a dungle");
    printf("%ld %d %s\n", calculate_time(), coder->id, "has taken a dungle");
    pthread_mutex_unlock(&data->log_mutex);
}

void    delete_ask(struct s_coder *coder, struct s_data *data)
{
    int     i;
    int     size;

    i = 0;
    size = data->heap->size;
    while (i < size)
    {
        if (coder->id == data->heap->asks[i].coder_id)
            break; 
        i++;
    }
    if (i == size)
        return;
    while (i < size - 1)
    {
        data->heap->asks[i] = data->heap->asks[i + 1];
        i++;
    }
    data->heap->size--;
    pthread_cond_broadcast(&data->cond);
}
