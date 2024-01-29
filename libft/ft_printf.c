/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:45:16 by hbelle            #+#    #+#             */
/*   Updated: 2023/12/21 18:35:26 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_percent(size_t *i, const char *format, int *error, size_t *count)
{
	if (format[*i + 1] == '\0' && format[*i + 1] == '\0')
		(*error)++;
	else if (format[*i + 1] == '%')
	{
		ft_putchar_fd(format[*i], 1);
		(*count)++;
		(*i)++;
	}
	else if (format[*i + 1] != 'c' && format[*i + 1] != 's'
		&& format[*i + 1] != 'p' && format[*i + 1] != 'd'
		&& format[*i + 1] != 'i' && format[*i + 1] != 'u'
		&& format[*i + 1] != 'x' && format[*i + 1] != 'X' )
	{
		ft_putchar_fd(format[*i], 1);
		(*count)++;
	}
}

void	loop(va_list args, const char *format, int *error, size_t *count)
{
	size_t			i;

	i = 0;
	while (format[i])
	{
		if (format[i] != '%' )
		{
			ft_putchar_fd(format[i], 1);
			(*count)++;
			if (format[i] == '\0')
				(*error)++;
		}
		else
		{
			*count = ft_printf_check(i, format, args, count);
			if (format[i + 1] == 'd' || format[i + 1] == 'i'
				|| format[i + 1] == 'u' || format[i + 1] == 'c'
				|| format[i + 1] == 'p' || format[i + 1] == 'x'
				|| format[i + 1] == 'X' || format[i + 1] == 's')
				i++;
			if (format[i] == '%')
				check_percent(&i, format, error, count);
		}
		i++;
	}
}

int	ft_printf(const char *format, ...)
{
	size_t			count;
	va_list			args;
	int				error;

	va_start(args, format);
	if (format == NULL)
	{
		va_end(args);
		return (-1);
	}
	error = 0;
	count = 0;
	loop(args, format, &error, &count);
	if (error == 1)
		count = -1;
	va_end(args);
	return (count);
}
