/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:12:49 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/24 19:10:59 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_meta_char_quote(char c, char quote)
{
	if (quote == '\'')
		return (c == '|' || c == '>' || c == '<' || c == ';' || c == '&'
			|| c == '(' || c == ')' || c == '\"' || c == '\\' || c == '$');
	else
		return (c == '|' || c == '>' || c == '<' || c == ';' || c == '&'
			|| c == '(' || c == ')' || c == '\'' || c == '\\');
}

char	*get_variable_name(char *str, int i, int *j)
{
	char	*var;

	var = ft_strdup(str + i + 1);
	while (var[*j] && (ft_isalnum(var[*j]) || var[*j] == '_'))
		(*j)++;
	var[*j] = '\0';
	return (var);
}

char	*create_new_string(char *str, char *value, int i, int j)
{
	char	*new_str;
	char	*temp;
	char	*var;

	temp = ft_substr(str, 0, i);
	new_str = ft_strjoin(temp, value);
	free(temp);
	temp = ft_strdup(str + i + j + 1);
	var = ft_strdup(new_str);
	free(new_str);
	new_str = ft_strjoin(var, temp);
	free(var);
	free(temp);
	free(str);
	return (new_str);
}

char	*expand_variable_value(char *str, int i, int j, t_mini *m)
{
	char	*var;
	char	*value;
	char	*new_str;

	var = get_variable_name(str, i, &j);
	value = target_path(m, m->envm, var, 1);
	free(var);
	if (value)
	{
		var = ft_strdup(value);
		free(value);
		value = ft_substr(var, 1, ft_strlen(var));
		free(var);
	}
	else
	{
		free(str);
		return (NULL);
	}
	new_str = create_new_string(str, value, i, j);
	free(value);
	return (new_str);
}

char	*expand_variable(char *str, t_mini *m)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '$' && is_between_quotes(str, i) == false && str[i
			+ 1] != '?')
		{
			str = expand_variable_value(str, i, 0, m);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}
