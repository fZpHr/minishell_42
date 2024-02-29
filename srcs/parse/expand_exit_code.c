/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:38:34 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/29 14:01:07 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(t_mini *m)
{
	char	*value;

	if (m->exit_status >= 1000 && m->exit_status < 1500)
		value = ft_itoa(m->exit_status - 1000);
	else if (m->exit_status >= 1500)
		value = ft_itoa(m->exit_status >> 8);
	else
	{
		if (m->exit_status >= 256)
			value = ft_itoa(m->exit_status >> 8);
		else
			value = ft_itoa(m->exit_status);
	}
	return (value);
}

char	*create_new_str(char *str, char *value, int i)
{
	char	*new_str;
	char	*temp;

	temp = ft_substr(str, 0, i);
	new_str = ft_strjoin(temp, value);
	free(temp);
	return (new_str);
}

char	*update_str(char *str, char *new_str, int i)
{
	char	*temp;

	temp = ft_strdup(str + i + 2);
	free(str);
	str = ft_strjoin(new_str, temp);
	free(new_str);
	free(temp);
	return (str);
}

char	*expand_exit_code(char *str, t_mini *m)
{
	int		i;
	char	*value;
	char	*new_str;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
			i++;
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			value = get_value(m);
			new_str = create_new_str(str, value, i);
			str = update_str(str, new_str, i);
			free(value);
		}
		i++;
	}
	return (str);
}
