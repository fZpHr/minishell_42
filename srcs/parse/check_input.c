/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/24 17:54:20 by tmekhzou         ###   ########.fr       */
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
		error_handle(m, "", "", 9999);
	else if (m->heredoc_status == 1)
		here_doc(m, m->cmd[0]);
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

int	here_doc_check(t_mini *m, char *cmd)
{
	char	**tmp;

	tmp = ft_split(cmd, " ");
	if (ft_strcmp(tmp[0], "<<") == 0)
	{
		m->heredoc_status = 1;
		free_split(tmp);
		return (1);
	}
	m->heredoc_status = 0;
	free_split(tmp);
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
