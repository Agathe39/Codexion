/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 18:30:48 by agathe            #+#    #+#             */
/*   Updated: 2026/09/29 18:20:47 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
    long    time;
    
    pthread_mutex_lock(&data->log_mutex);
    time = calculate_time();
    printf("%ld %d %s\n", time, coder->id, "is compiling");
    pthread_mutex_unlock(&data->log_mutex);

    ft_sleep_ms(data->time_to_compile);

    pthread_mutex_lock(&data->mutex_ask);
    coder->last_compile_start = time;
    coder->nbr_compiles += 1;
    pthread_mutex_unlock(&data->mutex_ask);
}

void    debug(struct s_coder *coder, struct s_data *data)
{
    long    time;

    time = calculate_time();

    pthread_mutex_lock(&data->log_mutex);
    printf("%ld %d %s\n", time, coder->id, "is debugging");
    pthread_mutex_unlock(&data->log_mutex);

    ft_sleep_ms(data->time_to_debug);
}

void    refactor(struct s_coder *coder, struct s_data *data)
{
    long    time;

    time = calculate_time();

    pthread_mutex_lock(&data->log_mutex);
    printf("%ld %d %s\n", time, coder->id, "is refactoring");
    pthread_mutex_unlock(&data->log_mutex);

    ft_sleep_ms(data->time_to_refactor);
}

void    coder_routine(struct s_coder *coder, struct s_data *data)
{
    // if (coder->nbr_compiles == data->nbr_compilation_required)
    //     data->stopped = 1;
    
    ask_to_compile(coder, data);
    
    pthread_mutex_lock(&data->mutex_ask);

    while (algorithm(data) != coder || (coder->dungle_right->available == 1 || coder->dungle_left->available == 1) || data->stopped)
        pthread_cond_wait(&data->cond, &data->mutex_ask);

    if (data->stopped)
    {
        delete_ask(coder, data);
        pthread_mutex_unlock(&data->mutex_ask);
        return;
    }

    delete_ask(coder, data);
    take_dungles(coder, data);

    pthread_mutex_unlock(&data->mutex_ask);

    compile(coder, data);
    let_dungles(coder, data);
    debug(coder, data);
    refactor(coder, data);
}
