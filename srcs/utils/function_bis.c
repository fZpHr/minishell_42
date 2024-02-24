/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:06:14 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/24 17:07:26 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*cut_cmd_char(t_mini *m, char *cmd)
{
	char	*tmp;
	char	*find;
	char	l;

	find = ft_strchr(cmd, '=');
	if (!find)
	{
		if (ft_isalnum(cmd[0]) != 0)
			m->status_exit = 1;
		return (NULL);
	}
	l = ft_strlen_arg(cmd, '=') + 1;
	tmp = (char *)malloc(sizeof(char) * (l + 1));
	ft_strlcpy(tmp, cmd, l + 1);
	return (tmp);
}

void	add_null(char **env, int i, int l)
{
	while (l)
	{
		env[i] = NULL;
		i++;
		l--;
	}
}
