/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathe <agathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:44:00 by agathe            #+#    #+#             */
/*   Updated: 2026/09/22 16:28:29 by agathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <unistd.h>
# include <pthread.h>

typedef struct s_dungle {

    int nbr;
    char *available;

} dungle;

typedef struct s_coder {

    int id;
    long int last_compile_start;
    int nbr_compiles;
    dungle *dungle_right;
    dungle *dungle_left;
    char *state;
    pthread_t thread;

} coder;

int parsing(int nbr_arg, char **args);
long calculate_time();
struct s_coder *create_coder(int nbr_coder, struct s_dungle *dongles);
struct s_dungle *create_dungle(int nbr_dungle);

#endif