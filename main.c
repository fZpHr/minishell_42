/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/29 18:14:44 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exec(char **cmd)
{
	pid_t	pid;
	int		status;

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

void	ft_cd(char **cmd)
{
	if (cmd[1] == NULL)
		chdir(getenv("HOME"));
	else
	{
		if (chdir(cmd[1]) == -1)
			printf("error\n");
	}
}

/*void	ft_env(char **cmd)
{
	int		i;
	char	**env;

	i = 0;
	env = (char **)malloc(sizeof(char *) * 100);
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_setenv(char **cmd)
{
	int		i;
	char	**env;

	i = 0;
	env = (char **)malloc(sizeof(char *) * 100);
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}*/

void	start_term(void)
{
	char	*input;
	char 	**cmd;

	while (1)
	{
		ft_printf("$> ");
		input = get_next_line(0);
		cmd = ft_split(input, ' ');
		if (ft_strcmp(cmd[0], "exit") == 0)
			exit(0);
		else if (ft_strcmp(cmd[0], "cd") == 0)
			ft_cd(cmd);
		else if (ft_strcmp(cmd[0], "env") == 0)
			ft_env(cmd);
		else if (ft_strcmp(cmd[0], "setenv") == 0)
			ft_setenv(cmd);
		else if (ft_strcmp(cmd[0], "unsetenv") == 0)
			ft_unsetenv(cmd);
		else
			ft_exec(cmd);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{

	ac = 0;
	av = NULL;
	start_term();
	
	return (0);
}