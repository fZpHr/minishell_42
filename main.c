/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/05 19:31:03 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal_flag[4];

void	interrupt_handle(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal_flag[2] == 1)
		{
			g_signal_flag[3] = 1;
			rl_on_new_line();
			rl_replace_line("", 0);
			g_signal_flag[2] = 0;
		}
		else if (g_signal_flag[3] == 0 || g_signal_flag[0] == 1)
		{
			g_signal_flag[1] = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
		return ;
}

void	init_parsing(t_mini *m, t_token_list **current)
{
	char	**command_split;

	command_split = ft_split_command(m->input);
	add_token(command_split, current, m);
	m->head = (*current);
	modify_linked_list(*current, m, command_split);
	(*current) = m->head;
	while ((*current)->token != END)
	{
		(*current)->value = expand_variable((*current)->value, m);
		(*current)->value = quote_things((*current)->value);
		(*current) = (*current)->next;
	}
	(*current) = m->head;
	m->ac = count_pipe(*current);
	(*current) = m->head;
	free_split(command_split);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	t_mini				m;
	t_token_list		*current;

	if (ac != 1)
	{
		ft_printf_error("minishell: too many arguments\n");
		return (0);
	}
	sa.sa_handler = interrupt_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	(void)av;
	current = NULL;
	init(&m);
	ft_env(&m, env, 0);
	m.savefd[0] = dup(0);
	m.savefd[1] = dup(1);
	loop_main(&m, current);
	close(m.savefd[0]);
	close(m.savefd[1]);
	return (0);
}
