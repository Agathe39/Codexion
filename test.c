/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:11:08 by agathe            #+#    #+#             */
/*   Updated: 2026/09/16 17:11:43 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct{
	int billet;
	pthread_mutex_t lock;
} billetterie;

typedef struct{
	char id;
	billetterie *bank;
} seller;


void* send_billet(void *arg)
{
    seller *s = (seller *)arg;

    while (1)
    {
        pthread_mutex_lock(&s->bank->lock);
        if (s->bank->billet <= 0)
        {
            pthread_mutex_unlock(&s->bank->lock);
            break;
        }
        int value = s->bank->billet;
        printf("%c : ", s->id);
        printf("%d\n", s->bank->billet);
        s->bank->billet = value - 1;
        usleep(1000);
        pthread_mutex_unlock(&s->bank->lock);
    }
    return (NULL);
}

int	main(int argc, char **argv)
{
	billetterie bank;
	bank.billet = 100;
	
	seller seller_1;
	seller_1.id = 'a';
	seller_1.bank = &bank;

	seller seller_2;
	seller_2.id = 'b';
	seller_2.bank = &bank;
	
	pthread_t sold_1;
	pthread_t sold_2;

	pthread_mutex_init(&bank.lock, NULL);

	pthread_create(&sold_1, NULL, &send_billet, &seller_1); 
	pthread_create(&sold_2, NULL, &send_billet, &seller_2);
	pthread_join(sold_1, NULL);
	pthread_join(sold_2, NULL);

	pthread_mutex_destroy(&bank.lock);

	return (0);
}
