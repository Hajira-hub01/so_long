/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:48:24 by hajmoham          #+#    #+#             */
/*   Updated: 2024/10/30 13:27:06 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strendcmp(char *str1, char *str2, int n)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str1) - n;
	while (str2[i])
	{
		if (str1[len] == str2[i])
		{
			i++;
			len++;
		}
		else
			return (0);
	}
	if (i == n)
		return (1);
	else
		return (0);
}
