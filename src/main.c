/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 15:26:50 by aeuvrard          #+#    #+#             */
/*   Updated: 2026/10/05 15:56:14 by aeuvrard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	struct s_coder	*coders;
	struct s_dungle	*dungles;
	struct s_data	*data;
	pthread_t		monitor;
	int				i;

	i = 0;

	if (parsing(argc, argv) == 0)
		return (0);
	dungles = create_dungle(atoi(argv[1]));
	if (dungles == NULL)
	{
		write(2, "ERROR: dungles structure can't be initialised\n", 47);
		return (0);
	}
	coders = create_coder(atoi(argv[1]), dungles);
	if (coders == NULL)
	{
		write(2, "ERROR: coders structure can't be initialised\n", 46);
		return (0);
	}
	data = recup_data(argv, &coders, &dungles);
	if (data == NULL)
	{
		write(2, "ERROR: data structure can't be initialised\n", 44);
		return (0);
	}

	// TEST ARGV
	// i = 0;
	// while (i < atoi(argv[1]))
	// {
	// 	printf("id: %d%c", coders[i].id, '\n');
	// 	printf("last compile strat : %ld%c", coders[i].last_compile_start, '\n');
	// 	printf("nbr compilation: %d%c", coders[i].nbr_compiles, '\n');
	// 	printf("dungle left: %d%c", coders[i].dungle_left->nbr, '\n');
	// 	printf("dungle right: %d%c", coders[i].dungle_right->nbr, '\n');
	// 	printf("coder state: %s%c", coders[i].state, '\n');
	// 	printf("%s", "\n\n");
	// 	i++;
	// }
	// //

	// // TEST algorithm
	// data->heap->asks[0].coder_id = 2;
	// data->heap->asks[0].arrival_time = 100;
	// data->heap->asks[0].deadline = 900;

	// data->heap->asks[1].coder_id = 3;
	// data->heap->asks[1].arrival_time = 200;
	// data->heap->asks[1].deadline = 500;

	// data->heap->size = 2;

	// chosen = algorithm(data);
	// printf("chosen coder = %d\n", chosen->id);

	//
	// while ()
	// pthread_create(&coders, NULL, &coder_routine, (coder, data));
	create_threads(data);
	pthread_create(&monitor, NULL, &monitor_control, data);
	pthread_join(monitor, NULL);
	while (i < data->nbr_coders)
	{
		pthread_join(data->coders[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->mutex_ask);
	pthread_cond_destroy(&data->cond);
	return (0);
}
