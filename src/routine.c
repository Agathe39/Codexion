/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 18:30:48 by agathe            #+#    #+#             */
/*   Updated: 2026/09/26 19:03:13 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void    ask_to_compile(struct s_coder *coder, struct s_data *data)
{
    pthread_mutex_lock(&data->mutex_ask);
    data->heap->asks[data->heap->size].coder_id = coder->id;
    data->heap->asks[data->heap->size].arrival_time = calculate_time();
    data->heap->asks[data->heap->size].deadline = coder->last_compile_start + data->time_to_burnout;
    data->heap->size += 1;
    pthread_mutex_unlock(&data->mutex_ask);
}

void    coder_routine(struct s_coder *coder, struct s_data *data)
{
    ask_to_compile(coder, data);
}
