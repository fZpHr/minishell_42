/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:48:04 by cpeterea          #+#    #+#             */
/*   Updated: 2024/02/27 17:35:45 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_format(const char *src, t_data *data, va_list param)
{
	while (src[++data->i])
	{
		if (src[data->i + 1] == 's' && src[data->i] == '%')
			string_format(param, data);
		else if (src[data->i + 1] == 'c' && src[data->i] == '%')
			char_format(param, data);
		else if ((src[data->i + 1] == 'i' || src[data->i + 1] == 'd')
			&& src[data->i] == '%')
			int_format(param, data);
		else if (src[data->i + 1] == 'x' && src[data->i] == '%')
			base_format(param, data, data->base_hex_min, 'x');
		else if (src[data->i + 1] == 'X' && src[data->i] == '%')
			base_format(param, data, data->base_hex_maj, 'X');
		else if (src[data->i + 1] == 'p' && src[data->i] == '%')
			base_format(param, data, data->base_hex_min, 'p');
		else if (src[data->i + 1] == 'u' && src[data->i] == '%')
			base_format(param, data, data->base_decimal, 'u');
		else
			word_format(src, data);
	}
	return (data->count);
}

int	ft_printf_error(const char *src, ...)
{
	va_list	param;
	t_data	*data;
	int		count;

	data = malloc(sizeof(t_data));
	data->i = -1;
	data->count = 0;
	data->base_decimal = "0123456789";
	data->base_hex_maj = "0123456789ABCDEF";
	data->base_hex_min = "0123456789abcdef";
	if (!src)
		return (-1);
	va_start(param, src);
	count = get_format(src, data, param);
	free(data);
	va_end(param);
	return (count);
}
