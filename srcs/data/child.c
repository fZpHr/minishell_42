/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:52:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 18:22:17 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_end(t_mini *m)
{
	int	exec;

	exec = 0;
	if (build_intern(m) == 1)
	{
		ft_exec_builtin(m);
		close_fds(m);
		exit(0);
	}
	else
	{
		if (access(m->cmd[0], F_OK) == 0)
			m->tmp_end = ft_strdup(m->cmd[0]);
		else
		{
			m->tmp_end = found_cmd(m, m->envm);
			if (!m->tmp_end)
				error_handle(m, "command not found: ", m->cmd[0], 1127);
		}
		close(m->savefd[0]);
		close(m->savefd[1]);
		exec = execve(m->tmp_end, m->cmd, m->envm);
		if (exec == -1)
			error_handle(m, "error execve", m->cmd[0], 1126);
	}
}

void	end(t_mini *m)
{
	int	pid;

	pid = 0;
	if (build_intern(m) == 1)
		ft_exec_builtin(m);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			close_fds(m);
			return (error_handle(m, "error fork", "", 1));
		}
		if (pid == 0)
			child_end(m);
		waitpid(pid, &m->exit_status, 0);
	}
}

void	child_of_child_if(t_mini *m)
{
	close(m->fd[0]);
	dup2(m->fd[1], 1);
	close(m->fd[1]);
	ft_exec_builtin(m);
	close(m->savefd[0]);
	close(m->savefd[1]);
	error_handle(m, "", "", 1000);
}

void	child_of_child_else(t_mini *m)
{
	int	exec;

	exec = 0;
	if (access(m->cmd[0], F_OK) == 0)
		m->tmp_end = ft_strdup(m->cmd[0]);
	else
	{
		m->tmp_child = found_cmd(m, m->envm);
		if (!m->tmp_child)
		{
			close_fds(m);
			error_handle(m, "command not found: ", m->cmd[0], 1127);
		}
	}
	if (m->status_append == 0 && m->status_redir_out == 0)
	{
		close(m->fd[0]);
		dup2(m->fd[1], 1);
		close(m->fd[1]);
	}
	close(m->savefd[0]);
	close(m->savefd[1]);
	exec = execve(m->tmp_child, m->cmd, m->envm);
	if (exec == -1)
		error_handle(m, "error execve", m->cmd[0], 1126);
}

void	child_process(t_mini *m)
{
	int	pid;

	if (m->heredoc_status == 1)
		ft_exec_builtin(m);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			close(m->fd[0]);
			close(m->fd[1]);
			return (error_handle(m, "error fork", "", 1));
		}
		if (pid == 0)
		{
			if (build_intern(m) == 1)
				child_of_child_if(m);
			else
				child_of_child_else(m);
		}
	}
}
