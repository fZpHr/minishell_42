/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:15:34 by cpeterea          #+#    #+#             */
/*   Updated: 2024/02/27 15:25:21 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	word_format(const char *src, t_data *data)
{
	ft_putchar_fd(src[data->i], 2);
	if (src[data->i] == '%' && src[data->i + 1] == '%')
		data->i++;
	data->count++;
}

void	char_format(va_list param, t_data *data)
{
	data->c = va_arg(param, int);
	data->count++;
	ft_putchar_fd(data->c, 2);
	data->i++;
}

void	string_format(va_list param, t_data *data)
{
	data->str = (char *)va_arg(param, char *);
	data->count += printf_putstr(data->str);
	data->i++;
}

void	int_format(va_list param, t_data *data)
{
	data->c = va_arg(param, int);
	data->str = ft_itoa(data->c);
	data->count += printf_putstr(data->str);
	free(data->str);
	data->i++;
}

void	base_format(va_list param, t_data *data, char *base, char form)
{
	if (form == 'x' || form == 'X')
	{
		data->c = va_arg(param, int);
		ft_u_putnbr_base(data->c, base, &data->count);
		data->i++;
	}
	else if (form == 'p')
	{
		data->llu = va_arg(param, unsigned long long);
		ft_hexa(data->llu, base, &data->count);
		data->i++;
	}
	else if (form == 'u')
	{
		data->llu = va_arg(param, unsigned int);
		ft_u_putnbr_base(data->llu, base, &data->count);
		data->i++;
	}
}
