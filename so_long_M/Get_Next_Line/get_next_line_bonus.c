/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:48:31 by hajmoham          #+#    #+#             */
/*   Updated: 2024/08/23 11:20:06 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_fd(int fd, char *temp_str, char *str)
{
	int		size;
	char	*s;

	size = 1;
	while ((!ft_strchr(str, '\n')) && size > 0)
	{
		size = read(fd, temp_str, BUFFER_SIZE);
		if (size < 0)
		{
			free(str);
			free(temp_str);
			return (NULL);
		}
		if (size == 0)
		{
			free(temp_str);
			return (str);
		}
		temp_str[size] = '\0';
		s = str;
		str = ft_strjoin(str, temp_str);
		free(s);
	}
	free(temp_str);
	return (str);
}

char	*existing_line(char *str)
{
	char	*exist_line;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	exist_line = malloc(i + 1);
	if (!exist_line)
		return (NULL);
	exist_line[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		exist_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		exist_line[i] = '\n';
	return (exist_line);
}

char	*next_line(char *str)
{
	size_t	i;
	char	*next_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	next_str = ft_strdup(str + i);
	if (!next_str)
		return (NULL);
	free(str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[1024];
	char		*temp_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	temp_str = malloc(BUFFER_SIZE + 1);
	if (!temp_str)
		return (NULL);
	str[fd] = read_fd(fd, temp_str, str[fd]);
	if (!str[fd])
		return (NULL);
	line = existing_line(str[fd]);
	str[fd] = next_line(str[fd]);
	return (line);
}
