/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:43:22 by hajmoham          #+#    #+#             */
/*   Updated: 2024/11/04 16:10:45 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void error_print (char *err_txt)
{
    write (2, err_txt, ft_strlen(err_txt));
    exit (EXIT_FAILURE);
}

void chk_ber (int ac, char **av)
{
    if (ac != 2)
        error_print ("You need 2 arguments!");
    if (!ft_strendcmp(av[1], ".ber", 4))
        error_print ("Check Again!! Only '.ber' type files are allowed (-_-)");
}