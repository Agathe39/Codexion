/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:49:28 by agathe            #+#    #+#             */
/*   Updated: 2026/09/30 19:10:21 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    create_threads(struct s_data *data)
{
    int i;

    i = 0;

    while (i < data->nbr_coders)
    {
        pthread_create(&data->coders[i].thread, NULL, &coder_routine, &data->coders[i]);
        i++;
    }
        
    return;
}