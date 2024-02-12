/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:01:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/12 15:27:36 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	first_child(t_mini *m, char *f_path, int pipe_fd[2], char **envp)
{
	int	file_fd;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		file_fd = open(f_path, O_RDONLY);
		if (file_fd == -1)
			exit(exit_file_error(cmd, pipe_fd, f_path));
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		if (cmd->command != NULL && cmd->command_path != NULL)
			execve(cmd->command_path, cmd->command, envp);
		command_error(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
	return (1);
}

int	pipe_to_pipe_child(t_mini *m, int p_fd[2], int new_fd[2], char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(p_fd[0], STDIN_FILENO);
		dup2(new_fd[1], STDOUT_FILENO);
		close_pipe(p_fd);
		close_pipe(new_fd);
		if (cmd->command != NULL && cmd->command_path != NULL)
			execve(cmd->command_path, cmd->command, envp);
		command_error(cmd);
		exit(EXIT_FAILURE);
	}
	close_pipe(p_fd);
	waitpid(pid, NULL, 0);
	p_fd[0] = new_fd[0];
	p_fd[1] = new_fd[1];
	free_cmd_struct(cmd);
	return (1);
}

int	last_child(t_mini *m, char *f_path, int p_fd[2], char **envp)
{
	int	file_fd;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		file_fd = open_outfile(f_path, cmd);
		if (file_fd == -1)
			exit(exit_file_error(cmd, p_fd, f_path));
		dup2(p_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		close_pipe(p_fd);
		close(file_fd);
		if (cmd->command != NULL && cmd->command_path != NULL)
			execve(cmd->command_path, cmd->command, envp);
		command_error(cmd);
		exit(EXIT_FAILURE);
	}
	close_pipe(p_fd);
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
	return (1);
}

void	ft_exec(t_mini *m, int argc, char **argv, char **envp)
{

	int			p_fd[2];
	int			new_p_fd[2];
	int			i;

	i = 2;
	if (pipe(p_fd) < 0)
		return ;
	while (i < argc - 1)
	{
		cmd = found_path(argv[i], envp);
		if (i == 2 && heredoc == 0)
			first_child(cmd, argv[1], p_fd, envp);
		else if (i == 2 && heredoc == 1)
			read_entry(argv[i], p_fd, cmd);
		else if (i == argc - 2)
			last_child(cmd, argv[argc - 1], p_fd, envp);
		else
		{
			if (pipe(new_p_fd) < 0)
				return ;
			pipe_to_pipe_child(cmd, p_fd, new_p_fd, envp);
		}
		i++;
	}
}
