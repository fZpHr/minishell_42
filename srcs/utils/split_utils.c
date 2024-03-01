/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:41:36 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/29 16:38:02 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_word_command(const char *command)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '|' && command[i + 1] != '|')
			count++;
		else if (command[i] == '>' && command[i + 1] != '>')
			count++;
		else if (command[i] == '<' && command[i + 1] != '<')
			count++;
		else if (command[i] == '>' && command[i + 1] == '>')
		{
			count++;
			i++;
		}
		else
			count_word_command_2(command, &i, &count);
		if (command[i] != '\0')
			i++;
	}
	return (count);
}

void	count_word_command_2(const char *command, int *i, int *count)
{
	if (command[*i] == '<' && command[*i + 1] == '<')
	{
		(*count)++;
		(*i)++;
	}
	else if (ft_isalnum(command[*i]) && !ft_isalnum(command[*i + 1]))
		(*count)++;
	else if (command[*i] == '\"' && command[*i + 1] != '\"')
	{
		(*count)++;
		*i = skip_char('\"', command, *i);
	}
	else if (command[*i] == '\'' && command[*i + 1] != '\'')
	{
		(*count)++;
		*i = skip_char('\'', command, *i);
	}
	else if (command[*i] == ' ' && command[*i + 1] != ' ')
		(*count)++;
}

int	skip_char(char c, const char *command, int i)
{
	if (command[i] != '\0')
		i++;
	while (command[i] != '\0' && command[i] != c)
		i++;
	if (command[i] != '\0')
		i++;
	return (i);
}
