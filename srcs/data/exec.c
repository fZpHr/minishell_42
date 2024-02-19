/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/19 17:40:30 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end(t_mini *m, char **envp)
{
	int	fd;
	int	exec;
	int pid;
	
	m->end_status = 1;
	if (build_intern(m) == 1)
	{
		ft_exec_builtin(m, envp);
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
				m->tmp_end = found_cmd(m, envp);
				if (!m->tmp_end)
				{
					error_handle(m, "command not found: ", m->cmd[0], 127);
					exit(0);
				}
			}
			if (m->status_append == 1)
			{

				fd = open(m->out, O_WRONLY | O_CREAT | O_APPEND, 0777);
				dup2(fd, 1);
				close(fd);
			}
			exec = execve(m->tmp_end, m->cmd, envp);
			if (exec == -1)
			{
				error_handle(m, "error execve",  m->cmd[0], 126);
				exit(0);
			}
		}
		else
			waitpid(pid, &m->exit_status, 0);
	}
}

void	child_process(t_mini *m, char **envp)
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
			ft_exec_builtin(m, envp);
			exit(0);
		}
		else
		{
			if (access(m->cmd[0], F_OK) == 0)
				m->tmp_end = ft_strdup(m->cmd[0]);
			else
			{
				m->tmp_child = found_cmd(m, envp);
				if (!m->tmp_child)
				{
					close(m->fd[1]);
					close(m->fd[0]);
					error_handle(m, "command not found: ", m->cmd[0], 127);
					exit(0);
				}
			}
			close(m->fd[0]);
			dup2(m->fd[1], 1);
			close(m->fd[1]);
			exec = execve(m->tmp_child, m->cmd, envp);
			if (exec == -1)
			{
				error_handle(m, "error execve", m->cmd[0], 126);
				return ;
			}
		}
	}
	waitpid(pid, &m->exit_status, 0);
}

void	pipex(t_mini *m, char **envp)
{
	if (pipe(m->fd) == -1)
	{
		close(m->fd[0]);
		close(m->fd[1]);
		error_handle(m, "error pipe", "", 1);
		return ;
	}
	child_process(m, envp);
	close(m->fd[1]);
	dup2(m->fd[0], 0);
	close(m->fd[0]);
}

void	ft_exec(t_mini *m, t_token_list *current, char **envp)
{
	int		i;

	i = 0; 
	stdin_stdout_handle(m, 0);
	if (m->ac == 0)
		end(m, envp);
	else
	{
		while (i < m->ac)
		{
			pipex(m, envp);
			if (current)
				current = current->next;
			current = group_command_args(current, m);
			i++;
		}
		end(m, envp);
	}
	stdin_stdout_handle(m, 1);
}
