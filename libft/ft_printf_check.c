/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:35:45 by hbelle            #+#    #+#             */
/*   Updated: 2023/12/21 18:35:48 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	print_p(va_list args, size_t count)
{
	char	*hexa_lower;
	void	*ptr;

	hexa_lower = "0123456789abcdef";
	ptr = va_arg(args, void *);
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		count += 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		ft_putnbr_fd_base_unsigned((unsigned long long int)ptr, 1, hexa_lower);
		count += ft_countdigits_base_unsigned
			((unsigned long long int)ptr, 16) + 3;
	}
	return (count);
}

size_t	print_s(va_list args, size_t count)
{
	char			*str;

	str = va_arg(args, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		count += 6;
	}
	else
	{
		ft_putstr_fd(str, 1);
		count += ft_strlen(str);
	}
	return (count);
}

size_t	print_diuc(size_t i, const char *format, va_list args, size_t count)
{
	int	num;

	if (format[i + 1] == 'd' || format[i + 1] == 'i')
	{
		num = va_arg(args, int);
		ft_putnbr_fd(num, 1);
		count += ft_countdigits(num);
	}
	else if (format[i + 1] == 'c')
	{
		num = va_arg(args, int);
		ft_putchar_fd(num, 1);
		count += 1;
	}
	else if (format[i + 1] == 'u')
	{
		num = va_arg(args, int);
		ft_putnbr_fd_unsigned((unsigned int)num, 1);
		count += ft_countdigits_unsigned((unsigned int)num);
	}
	return (count);
}

size_t	print_xx(size_t i, const char *format, va_list args, size_t count)
{
	char			*hexa_lower;
	char			*hexa_upper;
	unsigned int	num_unsigned;
	int				num;

	hexa_lower = "0123456789abcdef";
	hexa_upper = "0123456789ABCDEF";
	if (format[i + 1] == 'x' || format[i + 1] == 'X')
	{
		num_unsigned = va_arg(args, int);
		if (format[i + 1] == 'x')
			ft_putnbr_fd_base_unsigned(num_unsigned, 1, hexa_lower);
		else
			ft_putnbr_fd_base_unsigned(num_unsigned, 1, hexa_upper);
		count += ft_countdigits_base_unsigned(num_unsigned, 16);
		num = num_unsigned;
		if (num > 0 || num < 0)
			count++;
	}
	return (count);
}

size_t	ft_printf_check(size_t i, const char *format,
		va_list args, size_t *count)
{
	if (format[i + 1] == 'd' || format[i + 1] == 'i'
		|| format[i + 1] == 'u' || format[i + 1] == 'c')
		*count = print_diuc(i, format, args, *count);
	else if (format[i + 1] == 's')
		*count = print_s(args, *count);
	else if (format[i + 1] == 'p')
		*count = print_p(args, *count);
	else if (format[i + 1] == 'x' || format[i + 1] == 'X')
		*count = print_xx(i, format, args, *count);
	else if (format[i + 1] == '\n')
		ft_putchar_fd('\n', 1);
	return (*count);
}
