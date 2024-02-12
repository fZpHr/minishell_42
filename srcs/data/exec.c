/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:15:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/12 19:49:11 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end(t_mini *m, char *cmd, char **envp)
{
	int	fd;
	int	exec;

	if (build_intern(m, cmd) == 1)
	{
		ft_exec_builtin(m, cmd, envp);
	}
	else
	{
		m->tmp_end = found_cmd(m, envp, cmd);
		if (!m->tmp_end)
		{
			error_handle(m, "command not found: ", cmd, 126);
			return ;
		}
		if (m->status_append == 1)
		{
			fd = open(m->out, O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2(fd, 1);
			close(fd);
		}
		m->cmd1 = ft_split(cmd, " ");
		exec = execve(m->tmp_end, m->cmd1, envp);
		if (exec == -1)
		{
			error_handle(m, "error execve", cmd, 127);
			return ;
		}
	}
	printf("aaaaa\n");
}

void	child_process(t_mini *m, int fd[2], char **envp, char *cmd)
{
	int	exec;

	exec = 0;
	if (build_intern(m, cmd) == 1)
	{
		ft_exec_builtin(m, cmd, envp);
		exit(0);
	}
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
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		m->cmd1 = ft_split(cmd, " ");
		exec = execve(m->tmp_child, m->cmd1, envp);
		if(exec == -1)
		{
			error_handle(m, "error execve", cmd, 126);
			return ;
		}
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
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void	pipex_multi(t_mini *m, int argc, char **argv, char **envp)
{
	int		i;
	int		pid;


	pid = fork();
	if (pid == -1)
	{
		error_handle(m, "error fork", "", 1);
		return ;
	}
	if (pid == 0)
	{
		i = 0;
		if (argc > 1)
			while (i < argc - 1)
				pipex(m, argv[i++], envp);
		end(m, argv[i], envp);
	}
	else
		waitpid(pid, NULL, 0);
	return ;
}

void	ft_exec(t_mini *m, char *input, char **envp)
{
	int		i;
	int argc;
	char **argv;

	i = 0;
	argv = ft_split(input, "|");
	argc = ft_count_cmd(input, '|');
	pipex_multi(m, argc, argv, envp);
	printf("%d", m->exit_status);
	if (m->exit == 1)
	{
		exit(0);
	}
	error_handle(m, "", "", 0);
	free_split(argv);
}

	/*else
	{
		if (pid == -1)
		{
			error_handle(m, "error fork", "", 1);
			return (free_split(argv));
		}
		if (pid == 0)
		{
			if (build_intern(m, argv[0]) == 1)
			{
				if (ft_strcmp(argv[0], "echo") == 0)
					ft_echo(m);
				else if (ft_strcmp(argv[0], "cd") == 0)
					ft_cd(m);
				else if (ft_strcmp(argv[0], "pwd") == 0)
					ft_pwd(m);
				else if (ft_strcmp(argv[0], "env") == 0)
					ft_env(m, envp, 1);
				else if (ft_strcmp(argv[0], "export") == 0)
					ft_export(m, envp);
				else if (ft_strcmp(argv[0], "unset") == 0)
					ft_unset(m);
				else if (ft_strcmp(argv[0], "exit") == 0)
					error_handle(m, "", "", 1000);
				free_split(argv);
				return ;
			}
			else
			{

				signal(SIGINT, SIG_IGN);
				if (m->tmp != NULL)
					free(m->tmp);
				m->tmp = found_cmd(m, envp, argv[0]);
				if (!m->tmp)
				{
					error_handle(m, "command not found: ", argv[0], 127);
					return (free_split(argv));
				}
				if (m->status_append == 1)
				{
					m->out = ft_strjoin(m->out, ".txt");
					m->status_append = 0;
				}
				m->cmd1 = ft_split(argv[0], " ");	
				i = execve(m->tmp, m->cmd1, envp);
				if (i == -1)
				{
					error_handle(m, "error execve", argv[0], 126);
					return (free_split(argv));
				}
			}
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}*/