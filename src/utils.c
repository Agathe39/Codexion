/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:59:40 by agathe            #+#    #+#             */
/*   Updated: 2026/09/28 17:20:51 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
        return (NULL);
    while (i < size)
    {
        data->heap->asks[i] = data->heap->asks[i + 1];
        i++;
    }
    data->heap->size--;
    pthread_cond_broadcast(&data->cond);
}
