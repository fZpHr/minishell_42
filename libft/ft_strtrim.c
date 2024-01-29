/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:30:52 by hbelle            #+#    #+#             */
/*   Updated: 2023/11/06 13:54:51 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	loop(char *ptr, size_t i, const char *s1, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		ptr[j] = s1[i + j];
		j++;
	}
}

static char	*empty(void)
{
	char	*ptr;

	ptr = (char *)malloc(1);
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	return (ptr);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (s1[i] == '\0')
		return (empty());
	j = ft_strlen(s1);
	while (j > 0 && ft_strchr(set, s1[j - 1]))
		j--;
	len = j - i;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	j = 0;
	loop(ptr, i, s1, len);
	ptr[len] = '\0';
	return (ptr);
}
