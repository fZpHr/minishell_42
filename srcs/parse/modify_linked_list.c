/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:17:12 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/03/05 17:24:01 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_list	*is_here_doc_after(t_token_list *current)
{
	current = current->next;
	while (current->token != PIPE && current->token != END)
	{
		if (current->token == HERE_DOC)
			return (current);
		current = current->next;
	}
	return (0);
}

void	rearrange_token_list(t_token_list **current)
{
	t_token_list	*tmp;
	t_token_list	*tmp_after_heredoc;
	t_token_list	*next_here_doc;
	t_token_list	*save_next_last_hd;
	
	tmp = (*current);
	while (tmp->token != PIPE && tmp->token != END)
	{
		next_here_doc = 0;
		if (tmp->token == HERE_DOC && tmp->next->token == COMMAND)
		{
			next_here_doc = is_here_doc_after(tmp);
			if (next_here_doc != 0)
			{
				save_next_last_hd = next_here_doc->next;
				tmp_after_heredoc = tmp->next;
				tmp->next = next_here_doc;
				next_here_doc->next = tmp_after_heredoc;
				while ((tmp->token != COMMAND || tmp->next->token == COMMAND) && tmp->token != END)
					tmp = tmp->next;
				tmp->next = save_next_last_hd;
			}
		}
		tmp = tmp->next;
	}
}

void	add_pipes_here_doc(t_token_list **head)
{
	t_token_list	*current;
	t_token_list	*save;

	current = (*head);
	while (current->token != END)
	{
		if (current->token == HERE_DOC && current->next->token != END && current->next->token != PIPE)
		{
			save = current->next;
			current->next = create_token_node(PIPE, 0);
			current->next->next = save;
		}
		current = current->next;
	}
}

void	modify_linked_list(t_token_list *head, t_mini *m, char **cmd)
{
	check_error_syntax_command(cmd, m);
	check_error_parsing_list(m, head);
	check_error_quotes(m);
	rearrange_token_list(&head);
	add_pipes_here_doc(&head);
}
