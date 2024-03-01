/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeterea <cpeterea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:23:34 by cpeterea          #+#    #+#             */
/*   Updated: 2024/02/24 11:33:53 by cpeterea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_u_putnbr_base(unsigned long long nbr, char *base, int *count)
{
	unsigned long long	len;

	len = ft_strlen(base);
	if (nbr == 0)
	{
		write(2, "0", 1);
		*count += 1;
		return ;
	}
	if (nbr / len != 0)
		ft_u_putnbr_base(nbr / len, base, count);
	*count += 1;
	write(2, &base[nbr % len], 1);
}

void	ft_hexa(unsigned long long nbr, char *base, int *count)
{
	unsigned long long	len;

	len = ft_strlen(base);
	if (nbr == 0)
	{
		write(1, "(nil)", 5);
		*count += 5;
		return ;
	}
	write(2, "0x", 2);
	*count += 2;
	if (nbr / len != 0)
		ft_u_putnbr_base((nbr / len), base, count);
	*count += 1;
	write(2, &base[nbr % len], 1);
}
