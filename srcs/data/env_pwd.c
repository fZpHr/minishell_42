/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:51:19 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/27 17:46:37 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_mini *m)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		error_handle(m, "error", "", 1);
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	error_handle(m, "", "", 0);
}

int	env_begin(t_mini *m, char **env, int status)
{
	int	i;

	i = 0;
	m->alloc_env = 1;
	m->envm = (char **)ft_malloc(sizeof(char *) * (ft_double_char_len(env)
				+ 1));
	if (!m->envm)
	{
		error_handle(m, "error ft_malloc", "", 1);
		return (1);
	}
	while (env[i])
	{
		m->envm[i] = ft_strdup(env[i]);
		i++;
	}
	m->envm[i] = NULL;
	i = 0;
	if (status == 1)
		while (m->envm[i])
			printf("%s\n", m->envm[i++]);
	return (0);
}

void	ft_env(t_mini *m, char **env, int status)
{
	int	i;

	if (m->alloc_env == 1)
	{
		i = 0;
		if (status == 1)
			while (m->envm[i])
				printf("%s\n", m->envm[i++]);
	}
	else
	{
		if (env_begin(m, env, status) == 1)
			return ;
	}
	error_handle(m, "", "", 0);
}
