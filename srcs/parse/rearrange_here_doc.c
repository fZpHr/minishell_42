/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:01:28 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/03/05 19:16:26 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rearrange_token_list(t_token_list **current)
{
	t_token_list	*tmp;

	tmp = (*current);
	while (tmp->token != PIPE && tmp->token != END)
		tmp = process_token(tmp);
	if (tmp->token == PIPE)
		tmp = tmp->next;
	while (tmp->token != PIPE && tmp->token != END)
		tmp = process_token(tmp);
}

t_token_list	*process_token(t_token_list *tmp)
{
	t_token_list	*next_here_doc;

	next_here_doc = 0;
	if (tmp->token == HERE_DOC && tmp->next->token == COMMAND)
	{
		next_here_doc = is_here_doc_after(tmp);
		if (next_here_doc != 0)
			tmp = rearrange_here_doc(tmp, next_here_doc);
	}
	return (tmp->next);
}

t_token_list	*rearrange_here_doc(t_token_list *tmp,
		t_token_list *next_here_doc)
{
	t_token_list	*tmp_after_heredoc;
	t_token_list	*save_next_last_hd;

	save_next_last_hd = next_here_doc->next;
	tmp_after_heredoc = tmp->next;
	tmp->next = next_here_doc;
	next_here_doc->next = tmp_after_heredoc;
	while ((tmp->token != COMMAND || tmp->next->token == COMMAND)
		&& tmp->token != END)
		tmp = tmp->next;
	tmp->next = save_next_last_hd;
	return (tmp);
}

bool	is_sorted_command(t_token_list *current)
{
	while (current->token != END)
	{
		if (current->token == COMMAND && current->next->token == HERE_DOC)
			return (false);
		current = current->next;
	}
	return (true);
}
