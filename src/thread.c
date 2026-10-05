/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:49:28 by agathe            #+#    #+#             */
/*   Updated: 2026/10/05 16:04:44 by aeuvrard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	create_threads(struct s_data *data)
{
	int	i;

	i = 0;

	while (i < data->nbr_coders)
	{
		pthread_create(&data->coders[i].thread, NULL, &coder_routine,
			&data->coders[i]);
		i++;
	}

	return ;
}
