/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:28:00 by hbelle            #+#    #+#             */
/*   Updated: 2023/12/21 18:36:57 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_loop(int bytes, char *buff, int fd)
{
	char	*line;

	line = ft_strdup_gnl(buff);
	if (!line)
		return (NULL);
	while (bytes != 0 && ft_checkline(line) == 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(line);
			return (NULL);
		}
		buff[bytes] = '\0';
		line = ft_strjoin_gnl(line, buff);
		if (!line)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

void	ft_nextline(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == '\n')
		i++;
	j = 0;
	while (str[i + j])
	{
		str[j] = str[i + j];
		j++;
	}
	str[j] = 0;
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE + 1];
	int				bytes;
	char			*line;

	bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_loop(bytes, buff, fd);
	ft_nextline(buff);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
