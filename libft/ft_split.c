/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:49:22 by hbelle            #+#    #+#             */
/*   Updated: 2023/11/06 13:53:43 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	separator(char c, char charset)
{
	if (c == charset)
		return (1);
	if (c == 0)
		return (1);
	return (0);
}

static int	count(char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (separator(str[i + 1], charset) == 1
			&& separator(str[i], charset) == 0)
			count++;
		i++;
	}
	return (count);
}

static void	putword(char *dest, char *src, char charset)
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

static void	putsplit(char **split, char *str, char charset)
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
			if (!split[count])
				return ;
			putword(split[count], str + i, charset);
			i = i + j;
			count++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**data;
	int		i;

	if (!s)
		return (NULL);
	i = count((char *)s, c);
	data = (char **) malloc(sizeof(char *) * (i + 1));
	if (data == NULL)
		return (NULL);
	data[i] = 0;
	putsplit(data, (char *)s, c);
	return (data);
}
