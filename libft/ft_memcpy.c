/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:52:15 by hbelle            #+#    #+#             */
/*   Updated: 2023/11/03 17:49:00 by zeph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	char	*ptr;

	if (!dest && !src)
		return (NULL);
	ptr = dest;
	while (size--)
		*ptr++ = *(char *)src++;
	return (dest);
}
