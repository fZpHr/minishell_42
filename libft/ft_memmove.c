/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:30:27 by hbelle            #+#    #+#             */
/*   Updated: 2023/11/07 11:31:33 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char		*ptr;
	unsigned char		*ptrsrc;
	unsigned int		i;

	i = 0;
	ptr = dest;
	ptrsrc = (unsigned char *)src;
	if (dest == src)
		return (dest);
	if (dest < src)
		while (size--)
			*ptr++ = *ptrsrc++;
	else
	{
		i = size;
		while (i > 0)
		{
			ptr[i - 1] = ptrsrc[i - 1];
			i--;
		}
	}
	return (dest);
}
