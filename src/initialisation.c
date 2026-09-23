/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:25:25 by agathe            #+#    #+#             */
/*   Updated: 2026/09/22 16:34:27 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long calculate_time()
{
	struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

struct s_coder *create_coder(int nbr_coder, struct s_dungle *dongles)
{
	struct s_coder *coders;
	coders = malloc(sizeof(coder) * nbr_coder);
	if (!coders)
		return (NULL);
	
	int i = 1;

	while (i <= nbr_coder)
	{
		coders[i - 1].id = i;
		coders[i - 1].last_compile_start = calculate_time();
		coders[i - 1].nbr_compiles = 0;
		coders[i - 1].dungle_left = &dongles[i - 1];
    	coders[i - 1].dungle_right = &dongles[(i - 2 + nbr_coder) % nbr_coder];
		coders[i - 1].state = "wait";
		i++;
	}
	
	return coders;
}

struct s_dungle *create_dungle(int nbr_dungle)
{
	struct s_dungle *dungles;
	dungles = malloc(sizeof(dungle) * nbr_dungle);
	int i = 1;

	while (i <= nbr_dungle)
	{
		dungles[i - 1].nbr = i;
		dungles[i - 1].available = "True";
		i++;
	}	
	
	return dungles;
}
