/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:53:05 by hbelle            #+#    #+#             */
/*   Updated: 2023/11/02 15:08:44 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*rtr;

	if ((s == NULL || f == NULL))
		return (NULL);
	rtr = (char *)malloc(ft_strlen(s) + 1);
	if (rtr == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	while (i < j)
	{
		rtr[i] = f(i, s[i]);
		i++;
	}
	rtr[j] = '\0';
	return (rtr);
}
