/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:49:22 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/27 17:35:45 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != 0)
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == 0)
		return (1);
	return (0);
}

int	count(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (separator(str[i + 1], charset) == 1 && separator(str[i],
				charset) == 0)
			count++;
		i++;
	}
	return (count);
}

void	putword(char *dest, char *src, char *charset)
{
	int	i;

	i = 0;
	while (separator(src[i], charset) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

void	putsplit(char **split, char *str, char *charset)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (separator(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (separator(str[i + j], charset) == 0)
				j++;
			split[count] = (char *)malloc(sizeof(char) * (j + 1));
			putword(split[count], str + i, charset);
			i = i + j;
			count++;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**data;
	int		i;

	i = count(str, charset);
	data = (char **)malloc(sizeof(char *) * (i + 1));
	if (data == NULL)
		return (NULL);
	data[i] = 0;
	putsplit(data, str, charset);
	return (data);
}
