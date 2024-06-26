/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:15:14 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/03/06 15:16:55 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_error_parsing_list(t_mini *m, t_token_list *current)
{
	while (current->token != END)
	{
		if (current->token == PIPE && current->next->token == PIPE)
			error_syntax(m, "|");
		else if (current->token == PIPE && current->next->token == END)
			error_syntax(m, "|");
		current = current->next;
	}
}

void	error_syntax(t_mini *m, char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	m->parse_error = 1;
	m->parse = 1;
	m->exit_status = 2;
}

void	check_error_quotes(t_mini *m)
{
	int		i;
	int		single_quotes;
	int		double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (m->input && m->input[i])
	{
		if (m->input[i] == '\'' && is_between_double_quotes(m->input, i) == 0)
			single_quotes++;
		if (m->input[i] == '\"' && is_between_quotes(m->input, i) == 0)
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
	{
		if (single_quotes % 2 != 0)
			error_syntax(m, "\'");
		else
			error_syntax(m, "\"");
	}
}
