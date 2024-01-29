/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:16:25 by hbelle            #+#    #+#             */
/*   Updated: 2023/11/05 20:58:52 by zeph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	long int	max;
	void		*ptr;

	max = nmemb * size;
	if (max < 0 || ((int)nmemb < 0 && (int)size < 0))
		return (NULL);
	ptr = malloc(max);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, max);
	return (ptr);
}
