/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:55:36 by agathe            #+#    #+#             */
/*   Updated: 2026/10/15 16:25:44 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	dongle_is_ready(struct s_dongle *dongle, struct s_data *data)
{
	if (dongle->available == 1)
		return (0);
	return (calculate_time(data) >= dongle->cooldown_end);
}

long	dongle_cooldown_deadline(struct s_coder *coder, struct s_data *data)
{
	long		now;
	long		deadline;
	t_dongle	*d;

	now = calculate_time(data);
	deadline = -1;
	d = coder->dongle_left;
	if (d->available == 0 && d->cooldown_end > now)
		deadline = d->cooldown_end;
	d = coder->dongle_right;
	if (d->available == 0 && d->cooldown_end > now
		&& d->cooldown_end > deadline)
		deadline = d->cooldown_end;
	return (deadline);
}
