/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:01:28 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/03/05 20:27:51 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void swap_nodes(t_token_list **head_ref, t_token_list *node1, t_token_list *node2) 
{
    // If the nodes are not the head node, then we need to find the previous node
    t_token_list *prev = NULL;
    t_token_list *cur = *head_ref;
    while (cur != node1) 
    {
        prev = cur;
        cur = cur->next;
    }

    // Change next of previous node
    if (prev != NULL)
        prev->next = node2;
    else  // If the node is head node, change head
        *head_ref = node2;

    // Swap next pointers of node1 and node2
    t_token_list *temp = node2->next;
    node2->next = node1;
    node1->next = temp;
}

void    rearrange_token_list(t_token_list **current)
{
    t_token_list    *tmp;

    tmp = (*current);
    while (tmp->token != PIPE && tmp->token != END)
    {
        if (tmp->token == COMMAND && tmp->next->token == HERE_DOC)
        {
            t_token_list    *next_here_doc;
            next_here_doc = is_here_doc_after(tmp);
            if (next_here_doc != 0)
            {
                swap_nodes(current, tmp, next_here_doc);
                tmp = next_here_doc;
            }
        }
        tmp = tmp->next;
    }
    if (tmp->token == PIPE)
        tmp = tmp->next;
    while (tmp->token != PIPE && tmp->token != END)
    {
        if (tmp->token == COMMAND && tmp->next->token == HERE_DOC)
        {
            t_token_list    *next_here_doc;
            next_here_doc = is_here_doc_after(tmp);
            if (next_here_doc != 0)
            {
                swap_nodes(current, tmp, next_here_doc);
                tmp = next_here_doc;
            }
        }
        tmp = tmp->next;
    }
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
