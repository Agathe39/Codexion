/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 15:26:50 by aeuvrard          #+#    #+#             */
/*   Updated: 2026/10/05 16:41:25 by aeuvrard         ###   ########.fr       */
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
