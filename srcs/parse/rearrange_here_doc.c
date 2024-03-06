/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:01:28 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/03/06 15:00:58 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	swap_nodes(t_token_list **head_ref, t_token_list *node1,
		t_token_list *node2)
{
	t_token_list	*prev;
	t_token_list	*cur;
	t_token_list	*temp;

	prev = NULL;
	cur = *head_ref;
	while (cur != node1)
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev != NULL)
		prev->next = node2;
	else
		*head_ref = node2;
	temp = node2->next;
	node2->next = node1;
	node1->next = temp;
}

void	process_tokens(t_token_list **current, t_token_list **tmp,
		t_token_list **next_here_doc)
{
	while ((*tmp)->token != PIPE && (*tmp)->token != END)
	{
		if ((*tmp)->token == COMMAND && (*tmp)->next->token == HERE_DOC)
		{
			*next_here_doc = is_here_doc_after(*tmp);
			if (*next_here_doc != 0)
			{
				swap_nodes(current, *tmp, *next_here_doc);
				*tmp = *next_here_doc;
			}
		}
		*tmp = (*tmp)->next;
	}
}

void	rearrange_token_list(t_token_list **current)
{
	t_token_list	*tmp;
	t_token_list	*next_here_doc;

	tmp = (*current);
	process_tokens(current, &tmp, &next_here_doc);
	if (tmp->token == PIPE)
		tmp = tmp->next;
	process_tokens(current, &tmp, &next_here_doc);
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
