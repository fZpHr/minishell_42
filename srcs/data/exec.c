/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/05 17:35:22 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end(t_pipex *p, char *cmd, char **envp)
{
	int	exec;

	p->tmp_end = found_cmd(p, envp, cmd);
	if (!p->tmp_end)
		handle_error(p, "pipex: command not found: ", cmd, 126);
	p->cmd1 = ft_split(cmd, ' ');
	exec = execve(p->tmp_end, p->cmd1, envp);
	if (exec == -1)
		handle_error(p, "pipex: error execve", cmd, 127);
}


void	child_process(t_pipex *p, int fd[2], char **envp, char *cmd)
{
	int	exec;

	exec = 0;
	p->tmp_child = found_cmd(p, envp, cmd);
	if (!p->tmp_child)
	{
		close(fd[1]);
		close(fd[0]);
		handle_error(p, "pipex: command not found: ", cmd, 127);
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	p->cmd1 = ft_split(cmd, ' ');
	exec = execve(p->tmp_child, p->cmd1, envp);
	if (exec == -1)
		handle_error(p, "pipex: error execve", cmd, 126);
}

void	pipex(t_pipex *p, char *cmd, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		handle_error(p, "pipex: error pipe", "", 1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		handle_error(p, "pipex: error fork", "", 1);
	}
	if (pid == 0)
		child_process(p, fd, envp, cmd);
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}
int pipex_multi(t_pipex *p, int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	while (i < argc - 1)
		pipex(p, argv[i++], envp);
	end(p, argv[i], envp);
	return (0);
}
int	ft_exec(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	p;
	int	pid;

	init_p(&p);
	pid = fork();
	i = 0;
	if (argc > 1)
	{
		if (pid == -1)
			handle_error(&p, "pipex: error fork", "", 1);
		if (pid == 0)
			pipex_multi(&p, argc, argv, envp);
		else
			waitpid(pid, NULL, 0);
		printf("\n");
	}
	else
	{
		if (pid == -1)
			handle_error(&p, "pipex: error fork", "", 1);
		if (pid == 0)
		{
			p.tmp = found_cmd(&p, envp, argv[0]);
			if (!p.tmp)
				handle_error(&p, "pipex: command not found: ", argv[0], 127);
			p.cmd1 = ft_split(argv[0], ' ');	
			i = execve(p.tmp, p.cmd1, envp);
			if (i == -1)
				handle_error(&p, "pipex: error execve", argv[0], 126);
		}
		else
			waitpid(pid, NULL, 0);
		printf("\n");
	}
	return (0);
}