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

/*void	ft_exec(t_mini *m, char **cmd)
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
}*/

void	ft_cd(t_mini *m)
{
	if (m->cmd[1] == NULL)
		chdir(getenv("HOME"));
	else
	{
		if (chdir(m->cmd[1]) == -1)
			printf("error\n");
	}
}

void	ft_env(char **env)
{
	int		i;
	
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini	m;
	init(&m);
	while (1)
	{
		ft_printf("$> ");
		m.input = get_next_line(0);
		m.cmd = ft_split(m.input, ' ');
		if (ft_strcmp(m.cmd[0], "exit\n") == 0)
			error_handle(&m, "", 0);
		else if (ft_strcmp(m.cmd[0], "cd\n") == 0)
			ft_cd(&m);
		else if (ft_strcmp(m.cmd[0], "env\n") == 0)
			ft_env(env);
		/*else
			ft_exec(&m);*/
		free_split(&m);
		free(m.input);
	}
	return (0);
}
