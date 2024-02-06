/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/06 19:22:29 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end(t_mini *m, char *cmd, char **envp)
{
	int	exec;

	m->tmp_end = found_cmd(m, envp, cmd);
	if (!m->tmp_end)
	{
		error_handle(m, "command not found: ", cmd, 126);
		return ;
	}
	m->cmd1 = ft_split(cmd, ' ');
	exec = execve(m->tmp_end, m->cmd1, envp);
	if (exec == -1)
	{
		error_handle(m, "error execve", cmd, 127);
		return ;
	}
}


void	child_process(t_mini *m, int fd[2], char **envp, char *cmd)
{
	int	exec;

	exec = 0;
	m->tmp_child = found_cmd(m, envp, cmd);
	if (!m->tmp_child)
	{
		close(fd[1]);
		close(fd[0]);
		error_handle(m, "command not found: ", cmd, 127);
		return ;
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	m->cmd1 = ft_split(cmd, ' ');
	exec = execve(m->tmp_child, m->cmd1, envp);
	if (exec == -1)
	{
		error_handle(m, "error execve", cmd, 126);
		return ;
	}
}

void	pipex(t_mini *m, char *cmd, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error_handle(m, "error pipe", "", 1);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error_handle(m, "error fork", "", 1);
		return ;
	}
	if (pid == 0)
		child_process(m, fd, envp, cmd);
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}
int pipex_multi(t_mini *m, int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	while (i < argc - 1)
		pipex(m, argv[i++], envp);
	end(m, argv[i], envp);
	return (0);
}
void	ft_exec(t_mini *m, char *input, char **envp)
{
	int		i;
	int	pid;
	int argc;
	char **argv;
	
	argv = ft_split(input, '|');
	argc = ft_count_cmd(input, '|');
	pid = fork();
	i = 0;
	if (argc > 1)
	{
		if (pid == -1)
		{
			error_handle(m, "error fork", "", 1);
			return;
		}
		if (pid == 0)
			pipex_multi(m, argc, argv, envp);
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		if (pid == -1)
			error_handle(m, "error fork", "", 1);
		if (pid == 0)
		{
			m->tmp = found_cmd(m, envp, argv[0]);
			if (!m->tmp)
			{
				error_handle(m, "command not found: ", argv[0], 127);
				return;
			}
			m->cmd1 = ft_split(argv[0], ' ');	
			i = execve(m->tmp, m->cmd1, envp);
			if (i == -1)
			{
				error_handle(m, "error execve", argv[0], 126);
				return;
			}
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	error_handle(m, "", "", 0);
	printf("\n");
}