/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/02/07 13:56:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/28 17:23:00 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_builtin(t_mini *m)
{
	if (ft_strcmp(m->cmd[0], "echo") == 0)
		ft_echo(m, m->cmd);
	else if (ft_strcmp(m->cmd[0], "cd") == 0)
		ft_cd(m, m->cmd);
	else if (ft_strcmp(m->cmd[0], "pwd") == 0)
		ft_pwd(m);
	else if (ft_strcmp(m->cmd[0], "env") == 0)
		ft_env(m, m->envm, 1);
	else if (ft_strcmp(m->cmd[0], "export") == 0)
		ft_export(m, m->envm);
	else if (ft_strcmp(m->cmd[0], "unset") == 0)
		ft_unset(m);
	else if (ft_strcmp(m->cmd[0], "exit") == 0)
		error_handle(m, "", "", 1000 + ft_atoi(m->cmd[1]));
	else if (m->heredoc_status == 1)
	{
		dup2(m->savefd[0], 0);
		dup2(m->savefd[1], 1);
		here_doc(m, m->heredoc_delimiter);
		free(m->heredoc_delimiter);
	}
	else
		error_handle(m, "Command not found", m->cmd[0], 127);
}

int	build_intern(t_mini *m)
{
	if (ft_strcmp(m->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(m->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(m->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(m->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(m->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(m->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(m->cmd[0], "exit") == 0)
		return (1);
	else if (m->heredoc_status == 1)
		return (1);
	return (0);
}

int	ft_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_if_pipe(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	cut_extra_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '\n')
		str[i - 1] = '\0';
}
