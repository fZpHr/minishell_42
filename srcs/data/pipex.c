/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/01 19:52:03 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end(t_pipex *p, char *out, char *cmd, char **envp)
{
	int	fd;
	int	exec;

	fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		handle_error(p, "pipex: error fd outfile", "", 1);
	p->tmp_end = found_cmd(p, envp, cmd);
	if (!p->tmp_end)
		handle_error(p, "pipex: command not found: ", cmd, 126);
	dup2(fd, 1);
	close(fd);
	p->cmd1 = ft_split(cmd, ' ');
	exec = execve(p->tmp_end, p->cmd1, envp);
	if (exec == -1)
		handle_error(p, "pipex: error execve", cmd, 127);
}

void	begin(t_pipex *p, char *in)
{
	int	fd;

	fd = open(in, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		handle_error(p, "pipex: error fd infile", "", 1);
	}
	dup2(fd, 0);
	close(fd);
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

int	ft_exec(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	p;

	init_p(&p);
	i = 0;
	pipex(&p, argv[i++], envp);
	end(&p, argv[argc - 1], argv[argc - 2], envp);
	return (0);
}