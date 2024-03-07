/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liexing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:18:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/06 16:18:21 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_less_than(char **command_split, t_token_list **head, t_mini *m,
		int *i)
{
	int	j;

	j = 0;
	if (command_split[*i][j + 1] == '<')
	{
		append_token_node(head, HERE_DOC, command_split[*i + 1]);
		m->heredoc_status = 1;
	}
	else
		append_token_node(head, REDIR_IN, command_split[*i + 1]);
	(*i)++;
}

void	handle_greater_than(char **command_split, t_token_list **head,
		t_mini *m, int *i)
{
	int	j;

	j = 0;
	if (command_split[*i][j + 1] == '>')
	{
		append_token_node(head, APPEND, command_split[*i + 1]);
		m->status_append = 1;
		(*i)++;
	}
	else
	{
		append_token_node(head, REDIR_OUT, command_split[*i + 1]);
		m->status_redir_out = 1;
		(*i)++;
	}
}

void	add_token(char **command_split, t_token_list **head, t_mini *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command_split[i])
	{
		if (command_split[i][j] == '<')
		{
			handle_less_than(command_split, head, m, &i);
		}
		else if (command_split[i][j] == '>')
		{
			handle_greater_than(command_split, head, m, &i);
		}
		else if (command_split[i][j] == '|')
			append_token_node(head, PIPE, 0);
		else
			append_token_node(head, COMMAND, command_split[i]);
		i++;
	}
	append_token_node(head, END, 0);
}
