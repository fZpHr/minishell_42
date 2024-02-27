/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:06:57 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/27 17:38:47 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(long int nb, int fd)
{
	long int	a;

	a = nb;
	if (a < 0)
	{
		a = a * (-1);
		write(fd, "-", 1);
	}
	if (a <= 9)
	{
		a = a + 48;
		write(fd, &a, 1);
	}
	else
	{
		ft_putnbr_fd((a / 10), fd);
		a = a % 10 + 48;
		write(fd, &a, 1);
	}
}
