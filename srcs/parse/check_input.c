/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/14 19:15:00 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	ft_cut_useless(t_mini *m)
{
	ft_memmove(&m->cmd[0], &m->cmd[m->intern_last], (m->count_cmd - m->intern_last) * sizeof(m->cmd[0]));
	ft_memset(&m->cmd[m->count_cmd - m->intern_last], 0, m->intern_last * sizeof(m->cmd[0]));
}*/

void	ft_exec_builtin(t_mini *m, char *cmd, char **envp)
{
	char **tmp;

	tmp = ft_split(cmd, " ");
	if (ft_strcmp(tmp[0], "echo") == 0)
		ft_echo(m, tmp);
	else if (ft_strcmp(tmp[0], "cd") == 0)
		ft_cd(m, tmp);
	else if (ft_strcmp(tmp[0], "pwd") == 0)
		ft_pwd(m);
	else if (ft_strcmp(tmp[0], "env") == 0)
		ft_env(m, envp, 1);
	else if (ft_strcmp(tmp[0], "export") == 0)
		ft_export(m, envp);
	else if (ft_strcmp(tmp[0], "unset") == 0)
		ft_unset(m);
	else if (ft_strcmp(tmp[0], "exit") == 0)
		error_handle(m, "", "", 9999);
	else if (ft_strcmp(tmp[0], "<<") == 0)
		here_doc(m, tmp[1]);
	free_split(tmp);
}
int		build_intern(t_mini *m, char *c)
{
	char **tmp;

	(void)m;
	tmp = ft_split(c, " ");
	if (ft_strcmp(tmp[0], "echo") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "cd") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "pwd") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "env") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "export") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "unset") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "exit") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "<<") == 0)
	{
		free_split(tmp);
		return (1);
	}
	return (0);
}

int here_doc_check(t_mini *m, char *cmd)
{
	char **tmp;

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

/*void	check_input(t_mini *m)
{
	int i;
	i = 0;
	while (m->cmd[i])
	{
		m->count_cmd++;
		if (ft_strcmp(m->cmd[i], ">>") == 0)
			m->append_right = i;
		else if (ft_strcmp(m->cmd[i], "<<") == 0)
			m->append_left = i;
		else if (ft_strcmp(m->cmd[i], ">") == 0)
			m->redi_right = i;
		else if (ft_strcmp(m->cmd[i], "<") == 0)
			m->redi_left = i;
		else if (build_intern(m->cmd[i]) == 1)
			m->intern_last = i;
		i++;
	}
	if (i > 1 && m->intern_last > 0)
		ft_cut_useless(m);
}*/

/*void	check_slash(t_mini *m, char *cmd)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			i++;
			j = i;
			while (cmd[j])
			{
			
		}
		i++;
	}
}


void ft_split_path(t_mini *m, char *cmd)
{
	int i;
	int j;
	int k;
	char *tmp;

	i = 0;
	j = 0;
	k = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			tmp[j] = '/';
			j++;
			i++;
			k = i;
			while (cmd[i] != '/' && cmd[i])
			{
				tmp[j] = cmd[i];
				j++;
				i++;
			}
			tmp[j] = '\0';
			if (access(tmp, F_OK) == 0)
			{
				m->path = ft_strdup(tmp);
				free(tmp);
				return ;
			}
			else
			{
				free(tmp);
				tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd) + 1));
				j = 0;
				i = k;
			}
		}
		i++;
	}
	free(tmp);
}*/
