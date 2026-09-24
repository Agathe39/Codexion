/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 15:26:50 by aeuvrard          #+#    #+#             */
/*   Updated: 2026/09/24 17:48:54 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int main(int argc, char **argv)
{
	if (parsing(argc, argv) == 0)
		return (0);
	
	struct s_coder	*coders;
	struct s_dungle	*dungles;
	struct s_data	*data;

	dungles = create_dungle(atoi(argv[1]));
	if (dungles == NULL)
	{
		printf("%s", "ERROR: dungles structure can't be initialised\n");
		return (0);
	}

	coders = create_coder(atoi(argv[1]), dungles);
	if (coders == NULL)
	{
		printf("%s", "ERROR: coders structure can't be initialised\n");
		return (0);
	}

	data = recup_data(argv, &coders, &dungles);
	if (data == NULL)
	{
		printf("%s", "ERROR: data structure can't be initialised\n");
		return (0);
	}

	int i = 0;
	while (i < atoi(argv[1]))
	{
		printf("%d%c", coders[i].id, '\n');
		printf("%ld%c", coders[i].last_compile_start, '\n');
		printf("%d%c", coders[i].nbr_compiles, '\n');
		printf("%d%c", coders[i].dungle_left->nbr, '\n');
		printf("%d%c", coders[i].dungle_right->nbr, '\n');
		printf("%s%c", coders[i].state, '\n');
		printf("%s", "\n\n");
		i++;
	}

	pthread_t monitor;
	
	pthread_create(&monitor, NULL, &monitor_control, data);
	pthread_join(monitor, NULL);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->mutex_dungles);

	return (0);
}
