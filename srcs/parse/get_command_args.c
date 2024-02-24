/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:34:11 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/24 11:41:27 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_token(t_token_list *current, t_mini *mini, int *i)
{
	if (current->token == COMMAND)
		mini->cmd[(*i)++] = ft_strdup(current->value);
	else if (current->token == REDIR_IN)
		do_redir_in(current->value);
	else if (current->token == REDIR_OUT)
	{
		mini->status_redir_out = 1;
		do_redir_out(current->value);
	}
	else if (current->token == APPEND)
	{
		mini->status_append = 1;
		do_append(current->value);
	}
	else if (current->token == HERE_DOC)
	{
		mini->heredoc_status = 1;
		mini->cmd[(*i)++] = ft_strdup(current->value);
	}
}

void	group_command_args(t_token_list **current, t_mini *mini)
{
	int	i;

	if (!(*current) || !(*current)->next)
		return ;
	i = 0;
	mini->status_redir_out = 0;
	mini->status_append = 0;
	mini->heredoc_status = 0;
	mini->cmd = (char **)malloc(sizeof(char *) * (get_number_of_args(current)
				+ 1));
	while ((*current)->token != END && (*current)->token != PIPE)
	{
		handle_token(*current, mini, &i);
		(*current) = (*current)->next;
	}
	mini->cmd[i] = NULL;
}

int	get_number_of_args(t_token_list **current)
{
	int				i;
	t_token_list	*head;

	head = *current;
	i = 0;
	while ((*current) && (*current)->token != END && (*current)->token != PIPE)
	{
		if ((*current)->token == COMMAND)
			i++;
		(*current) = (*current)->next;
	}
	(*current) = head;
	return (i);
}
