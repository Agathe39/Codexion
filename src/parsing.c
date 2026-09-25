/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeuvrard <aeuvrard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:13:01 by agathe            #+#    #+#             */
/*   Updated: 2026/09/25 16:23:07 by aeuvrard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	valid_scheduler(char **args)
{
	if (strcmp(args[8], "fifo") != 0 && strcmp(args[8], "edf") != 0)
	{
		write(2, "\nError: last argument must be 'fifo' or 'edf'\n\n", 48);
		return (0);
	}
	return (1);
}

int	is_int(char **args)
{
	int	i;
	int	y;

	i = 0;
	while (i++ < 7)
	{
		y = -1;
		while (args[i][++y] != '\0')
		{
			if (ft_len(args[i]) == 1 && args[i][0] == '0')
			{
				write(2, "\nError: integer must be superior to 0\n\n", 40);
				return (0);
			}
			if ((args[i][y] < '0' || args[i][y] > '9') || args[i][y] == '-')
			{
				write(2, "\nError: seven thirst argument must be positive \
					integer\n\n", 57);
				return (0);
			}
		}
	}
	return (1);
}

int	parsing(int nbr_arg, char **args)
{
	if (nbr_arg != 9)
	{
		write(2, "\nError: numbers arguments is not valid\n\n", 41);
		return (0);
	}
	else
	{
		if (is_int(args) == 0)
			return (0);
		if (valid_scheduler(args) == 0)
			return (0);
	}
	return (1);
}
