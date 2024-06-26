/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:18:14 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/06 16:18:14 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_token(t_token_list *current, t_mini *mini, int *i)
{
	if (current->token == COMMAND)
	{
		if (current->value)
			mini->cmd[(*i)++] = ft_strdup(current->value);
	}
	else if (current->token == REDIR_IN)
		do_redir_in(mini, current->value);
	else if (current->token == REDIR_OUT)
		do_redir_out(mini, current->value);
	else if (current->token == APPEND)
		do_append(mini, current->value);
	else if (current->token == HERE_DOC)
	{
		mini->heredoc_status = 1;
		mini->heredoc_delimiter = ft_strdup(current->value);
		mini->cmd[(*i)++] = ft_strdup(current->value);
	}
}

void	group_command_args(t_token_list **current, t_mini *mini)
{
	int	i;

	mini->error_open = 0;
	if (!(*current) || !(*current)->next)
		return ;
	i = 0;
	mini->status_redir_out = 0;
	mini->status_append = 0;
	mini->heredoc_status = 0;
	mini->cmd = (char **)ft_malloc(sizeof(char *) * (get_number_of_args(current)
				+ 2));
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
