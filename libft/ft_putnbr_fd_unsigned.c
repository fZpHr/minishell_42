/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:34:43 by hbelle            #+#    #+#             */
/*   Updated: 2023/12/21 18:34:50 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd_unsigned(unsigned long int nb, int fd)
{
	if (nb <= 9)
	{
		nb = nb + 48;
		write(fd, &nb, 1);
	}
	else
	{
		ft_putnbr_fd_unsigned((nb / 10), fd);
		nb = nb % 10 + 48;
		write(fd, &nb, 1);
	}
}
