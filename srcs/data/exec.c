/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 17:52:12 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipex(t_mini *m)
{
	if (pipe(m->fd) == -1)
	{
		close(m->fd[0]);
		close(m->fd[1]);
		error_handle(m, "error pipe", "", 1);
		return ;
	}
	child_process(m);
	close(m->fd[1]);
	if (m->heredoc_status == 0)
		dup2(m->fd[0], 0);
	else
		m->heredoc_status = 0;
	close(m->fd[0]);
}

void	loop_exec(t_mini *m, t_token_list *current)
{
	int	i;

	i = 0;
	while (i < m->ac)
	{
		pipex(m);
		if (m->status_redir_out == 1 || m->status_append == 1
			|| m->heredoc_status == 1)
		{
			dup2(m->savefd[0], 0);
			close(m->savefd[0]);
			dup2(m->savefd[1], 1);
			close(m->savefd[1]);
		}
		free_split(m->cmd);
		if (current)
			current = current->next;
		group_command_args(&current, m);
		i++;
	}
}

void	ft_exec(t_mini *m, t_token_list *current)
{
	if (m->ac == 0)
		end(m);
	else
	{
		loop_exec(m, current);
		end(m);
		if (m->status_redir_out == 1 || m->status_append == 1
			|| m->heredoc_status == 1)
		{
			dup2(m->savefd[0], 0);
			close (m->savefd[0]);
			dup2(m->savefd[1], 1);
			close(m->savefd[1]);
		}
	}
}
