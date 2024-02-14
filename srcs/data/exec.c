/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/14 19:26:38 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end(t_mini *m, char *cmd, char **envp)
{
	int	fd;
	int	exec;
	int pid;

	m->end_status = 1;
	if (build_intern(m, cmd) == 1)
	{
		ft_exec_builtin(m, cmd, envp);
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
			m->cmd1 = ft_split(cmd, " ");
			if (access(m->cmd1[0], F_OK) == 0)
				m->tmp_end = ft_strdup(m->cmd1[0]);
			else
			{
				m->tmp_end = found_cmd(m, envp, cmd);
				if (!m->tmp_end)
				{
					free_split(m->cmd1);
					error_handle(m, "command not found: ", cmd, 126);
					return ;
				}
			}
			if (m->status_append == 2)
			{
				fd = open(m->out, O_WRONLY | O_CREAT | O_APPEND, 0777);
				dup2(fd, 1);
				close(fd);
			}
			exec = execve(m->tmp_end, m->cmd1, envp);
			if (exec == -1)
			{
				error_handle(m, "error execve", cmd, 127);
				return ;
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void	child_process(t_mini *m, int fd[2], char **envp, char *cmd)
{
	int	exec;
	int pid;

	exec = 0;
	if (here_doc_check(m, cmd) == 1)
	{
		here_doc(m, cmd);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			close(fd[0]);
			close(fd[1]);
			error_handle(m, "error fork", "", 1);
			return ;
		}
		if (pid == 0)
		{
			if (build_intern(m, cmd) == 1)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				ft_exec_builtin(m, cmd, envp);
				exit(0);
			}
			else
			{
				m->cmd1 = ft_split(cmd, " ");
				if (access(m->cmd1[0], F_OK) == 0)
					m->tmp_end = ft_strdup(m->cmd1[0]);
				else
				{
					m->tmp_child = found_cmd(m, envp, cmd);
					if (!m->tmp_child)
					{
						close(fd[1]);
						close(fd[0]);
						error_handle(m, "command not found: ", cmd, 127);
						return ;
					}
				}
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				exec = execve(m->tmp_child, m->cmd1, envp);
				if(exec == -1)
				{
					error_handle(m, "error execve", cmd, 126);
					return ;
				}
			}
		}
		waitpid(pid, NULL, 0);
	}
}

void	pipex(t_mini *m, char *cmd, char **envp)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error_handle(m, "error pipe", "", 1);
		return ;
	}
	child_process(m, fd, envp, cmd);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	ft_exec(t_mini *m, char *input, char **envp)
{
	int		i;
	int argc;
	char **argv;

	i = 0;
	argc = ft_count_cmd(input, '|');
	argv = ft_split(input, "|");
	stdin_stdout_handle(m, 0);
	if (argc == 1)
		end(m, argv[0], envp);
	else
	{
		if (argc > 1)
		{
			while (i < argc - 1)
				pipex(m, argv[i++], envp);
			end(m, argv[i], envp);
		}
	}
	stdin_stdout_handle(m, 1);
	free_split(argv);
}