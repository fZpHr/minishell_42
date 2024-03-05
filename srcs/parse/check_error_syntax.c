/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:14:19 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/03/05 18:21:32 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_error_syntax_command(char **cmd, t_mini *m)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<')
			process_less_than(cmd, &i, &j, m);
		else if (cmd[i][0] == '>')
			process_greater_than(cmd, &i, &j, m);
		if (j > 1)
		{
			error_syntax(m, cmd[i - 1]);
			return ;
		}
		j = 0;
		i++;
	}
}

void	process_less_than(char **cmd, int *i, int *j, t_mini *m)
{
	while (cmd[*i] && cmd[*i][0] == '<')
	{
		(*j)++;
		(*i)++;
		check_error(cmd, i, m);
	}
}

void	process_greater_than(char **cmd, int *i, int *j, t_mini *m)
{
	while (cmd[*i] && cmd[*i][0] == '>')
	{
		(*j)++;
		(*i)++;
		check_error(cmd, i, m);
	}
}

void	check_error(char **cmd, int *i, t_mini *m)
{
	if (cmd[*i] && (cmd[*i][0] == '>' || cmd[*i][0] == '|'))
		error_syntax(m, cmd[*i]);
	else if (cmd[*i] == 0)
		error_syntax(m, cmd[*i - 1]);
}
