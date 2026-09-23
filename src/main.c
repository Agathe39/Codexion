/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 15:26:50 by aeuvrard          #+#    #+#             */
/*   Updated: 2026/09/22 16:42:56 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (parsing(argc, argv) == 0)
		return (0);
	
	struct s_coder *coders;
	struct s_dungle *dungles;

	dungles = create_dungle(atoi(argv[1]));
	coders = create_coder(atoi(argv[1]), dungles);

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

	return (0);
}
