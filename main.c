/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/29 19:25:05 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exec(t_mini *m, char **cmd)
{
	pid_t	pid;
	int		status;

	(void)m;
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			printf("error\n");
	}
	else if (pid < 0)
		printf("error\n");
	else
		wait(&status);
}

void	ft_cd(t_mini *m, char **cmd)
{
	(void)m;
	if (cmd[1] == NULL)
		chdir(getenv("HOME"));
	else
	{
		if (chdir(cmd[1]) == -1)
			printf("error\n");
	}
}

void	ft_env(t_mini *m , char **env)
{
	int		i;
	
	i = 0;
	m->cur_env = (char **)malloc(sizeof(char *) * 10000);
	while (env[i])
	{
		m->cur_env[i] = ft_strdup(env[i]);
		i++;
	}
	m->cur_env[i] = NULL;
	i = 0;
	while (m->cur_env[i])
	{
		printf("%s\n", m->cur_env[i]);
		i++;
	}
}



int	main(int ac, char **av, char **env)
{

	char	*input;
	char 	**cmd;
	
	ac = 0;
	av = NULL;
	t_mini	m;
	while (1)
	{
		ft_printf("$> ");
		input = get_next_line(0);
		cmd = ft_split(input, ' ');
		if (ft_strcmp(cmd[0], "exit") == 0)
			exit(0);
		else if (ft_strcmp(cmd[0], "cd") == 0)
			ft_cd(&m, cmd);
		else if (ft_strcmp(cmd[0], "env") == 0)
			ft_env(&m, env);
		else
			ft_exec(&m ,cmd);
		free(input);
	}
	
	return (0);
}
