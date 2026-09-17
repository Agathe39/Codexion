/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __main__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 15:26:50 by aeuvrard          #+#    #+#             */
/*   Updated: 2026/09/17 17:18:26 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	if (parsing(argc, argv) == 0)
		return (0);
	else
		printf("%s", "\nparsing ok\n\n");

	return (0);
}
