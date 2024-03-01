/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:12:53 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/24 17:01:24 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_list	*create_token_node(t_token token, char *value)
{
	t_token_list	*node;

	node = (t_token_list *)ft_calloc(sizeof(t_token_list), 1);
	if (node)
	{
		node->token = token;
		if (value)
			node->value = ft_strdup(value);
		node->next = NULL;
	}
	return (node);
}

void	append_token_node(t_token_list **head, t_token token, char *value)
{
	t_token_list	*new_node;
	t_token_list	*current;

	new_node = create_token_node(token, value);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	free_token_list(t_token_list *head)
{
	t_token_list	*current;
	t_token_list	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	ft_listclear(t_token_list **lst, void (*del)(void *))
{
	t_token_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp = (*lst)->next;
		if ((*lst)->value)
			del((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	count_pipe(t_token_list *current)
{
	int	count;

	count = 0;
	while (current->token != END)
	{
		if (current->token == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}
