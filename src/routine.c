/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 18:30:48 by agathe            #+#    #+#             */
/*   Updated: 2026/09/28 17:25:37 by agathe           ###   ########.fr       */
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

void    compile(struct s_coder *coder, struct s_data *data)
{
    
}

void    debug(struct s_coder *coder)
{
    
}

void    refactor(struct s_coder *coder)
{
    
}

void    coder_routine(struct s_coder *coder, struct s_data *data)
{
    // struct s_coder *coder_choice;
    
    ask_to_compile(coder, data);
    // coder_choice = ;
    // if (!coder_choice)
    //     return (NULL);
    
    pthread_mutex_lock(&data->mutex_ask);
    while (algorithm(data) != coder || (coder->dungle_right->available == 1 || coder->dungle_left->available == 1))
        pthread_cond_wait(&data->cond, &data->mutex_ask);
        //coder en wait  

    delete_ask(coder, data);
    pthread_mutex_unlock(&data->mutex_ask);

    compile(coder, data);
    debug(coder);
    refactor(coder);

    pthread_mutex_lock(&data->mutex_ask);
    //libérer les dungles
    pthread_mutex_unlock(&data->mutex_ask);
}
