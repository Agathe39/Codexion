/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 11:21:41 by agathe            #+#    #+#             */
/*   Updated: 2026/09/23 14:22:27 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int verif_burn_out(int i, int time, data *d)
{
    if ((time - d->coders[i].last_compile_start) >= d->time_to_burnout)
    {
        pthread_mutex_lock(&d->stop_mutex);
        d->stopped = 1;
        pthread_mutex_unlock(&d->stop_mutex);
        pthread_mutex_lock(&d->log_mutex);
        printf("%ld %d burned out\n", time, d->coders[i].id);
        pthread_mutex_unlock(&d->log_mutex);
        return (1);
    }
    return (0);
}

void *monitor_control(void *arg)
{
    data *d = (data *)arg;
    int i;
    int compile;
    long int time;

    while (1)
    {
        i = 0;
        compile = 0;
        time = calculate_time();
        while (i < d->nbr_coders)
        {
            if (d->coders[i].nbr_compiles >= d->nbr_compilation_required)
                compile ++;

            if (verif_burn_out(i, time, &d) == 1)
                retrun (NULL);
            i++;
        }
        if (compile >= d->nbr_coders)
            return (NULL);
        usleep(1000);
    }
    return (0);
}
