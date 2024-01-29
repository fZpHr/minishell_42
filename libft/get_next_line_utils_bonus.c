/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:29:51 by hbelle            #+#    #+#             */
/*   Updated: 2023/12/21 18:38:35 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_end_ofthe_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int	ft_checkline(char *str)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_gnl(char *buff)
{
	char	*dest;
	int		lenght;
	int		i;

	i = 0;
	lenght = ft_end_ofthe_line(buff);
	dest = malloc(sizeof(char) * (lenght + 1));
	if (!dest)
		return (NULL);
	while (i < lenght)
	{
		dest[i] = buff[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char *line, char *buff)
{
	char	*tmp;
	int		i;
	int		j;
	int		lenght;

	i = 0;
	j = 0;
	lenght = ft_end_ofthe_line(buff);
	tmp = malloc(sizeof(char) * (ft_strlen(line) + lenght + 1));
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	while (line[i])
		tmp[i++] = line[j++];
	j = 0;
	while (buff != NULL && j < lenght)
	{
		tmp[i + j] = buff[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(line);
	return (tmp);
}
