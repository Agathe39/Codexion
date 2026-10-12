/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 15:26:50 by aeuvrard          #+#    #+#             */
/*   Updated: 2026/10/12 17:11:00 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	struct s_data	*data;

	if (parsing(argc, argv) == 0)
		return (0);
	data = malloc(sizeof(struct s_data) * 1);
	if (!data)
	{
		clean_up(NULL);
		return (0);
	}
	data->coders = NULL;
	data->dungles = NULL;
	data->heap = NULL;
	if (recup_data(data, argv) == NULL)
	{
		write(2, "ERROR: data structure can't be initialised\n", 44);
		return (0);
	}
	pthread_join(data->monitor, NULL);
	data->monitor_created = 0;
	clean_up(data);
	return (0);
}
