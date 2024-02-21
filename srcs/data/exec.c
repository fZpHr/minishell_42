/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/21 14:07:36 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end(t_mini *m)
{
	int	exec;
	int pid;
	
	if (build_intern(m) == 1)
	{
		ft_exec_builtin(m);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			error_handle(m, "error fork", "", 1);
			return ;
		}
		if (pid == 0)
		{
			if (access(m->cmd[0], F_OK) == 0)
				m->tmp_end = ft_strdup(m->cmd[0]);
			else
			{
				m->tmp_end = found_cmd(m, m->envm);
				if (!m->tmp_end)
				{
					error_handle(m, "command not found: ", m->cmd[0], 127);
					exit(0);
				}
			}
			exec = execve(m->tmp_end, m->cmd, m->envm);
			if (exec == -1)
			{
				error_handle(m, "error execve",  m->cmd[0], 126);
				exit(0);
			}
		}
		waitpid(pid, &m->exit_status, 0);
	}
}


void	child_process(t_mini *m)
{
	int	exec;
	int pid;

	exec = 0;
	pid = fork();
	if (pid == -1)
	{
		close(m->fd[0]);
		close(m->fd[1]);
		error_handle(m, "error fork", "", 1);
		return ;
	}
	if (pid == 0)
	{
		if (build_intern(m) == 1)
		{
			close(m->fd[0]);
			dup2(m->fd[1], 1);
			close(m->fd[1]);
			ft_exec_builtin(m);
			exit(0);
		}
		else
		{
			if (access(m->cmd[0], F_OK) == 0)
				m->tmp_end = ft_strdup(m->cmd[0]);
			else
			{
				m->tmp_child = found_cmd(m, m->envm);
				if (!m->tmp_child)
				{
					close(m->fd[1]);
					close(m->fd[0]);
					error_handle(m, "command not found: ", m->cmd[0], 127);
					exit(0);
				}
			}
			if (m->status_append == 0 && m->status_redir_out == 0)
			{
				close(m->fd[0]);
				dup2(m->fd[1], 1);
				close(m->fd[1]);
			}
			exec = execve(m->tmp_child, m->cmd, m->envm);
			if (exec == -1)
			{
				error_handle(m, "error execve", m->cmd[0], 126);
				exit(0);
			}
		}
	}
	//waitpid(pid, &m->exit_status, 0);
}

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
	dup2(m->fd[0], 0);
	close(m->fd[0]);
}

/* int	check_redir(t_mini *m)
{

} */


void	ft_exec(t_mini *m, t_token_list *current)
{
	int		i;

	i = 0; 
	if (m->ac == 0)
		end(m);
	else
	{
		while (i < m->ac)
		{
			pipex(m);
			if (m->status_redir_out == 1 || m->status_append == 1)
			{
				dup2(m->savefd[0], 0);
				dup2(m->savefd[1], 1);
			}
			if (current)
				current = current->next;
			current = group_command_args(current, m);
			i++;
		}
		end(m);
		if (m->status_redir_out == 1 || m->status_append == 1)
		{
			dup2(m->savefd[0], 0);
			dup2(m->savefd[1], 1);
		}
		//waitpid(m->pid, &m->exit_status, 0);
	}
}


