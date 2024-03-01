/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:34:48 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/23 20:22:40 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*found_var(char **envp, char *target)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], target, ft_strlen(target)) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			return (path);
		}
		i++;
	}
	return (NULL);
}
