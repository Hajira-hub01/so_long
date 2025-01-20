/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_w_nl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:23:51 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/20 10:23:52 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_w_nl(char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	free(s);
	str[i] = '\0';
	return (str);
}
