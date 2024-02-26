/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 19:57:25 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal_flag[3];

void	interrupt_handle(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_flag[0] = 1;
		g_signal_flag[1] = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_signal_flag[0] = 0;
	}
	else if (sig == SIGQUIT)
	{
		return ;
	}
}

void	init_parsing(t_mini *m, t_token_list **current)
{
	char	**command_split;

	command_split = ft_split_command(m->input);
	add_token(command_split, current, m);
	m->head = (*current);
	while ((*current)->token != END)
	{
		(*current)->value = expand_variable((*current)->value, m);
		(*current)->value = quote_things((*current)->value);
		(*current) = (*current)->next;
	}
	(*current) = m->head;
	m->ac = count_pipe(*current);
	(*current) = m->head;
	while ((*current)->token != END)
	{
		if ((*current)->token == HERE_DOC
			&& (*current)->next->next->token != COMMAND)
			m->ac = 0;
		(*current) = (*current)->next;
	}
	(*current) = m->head;
	free_split(command_split);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	t_mini				m;
	t_token_list		*current;

	sa.sa_handler = interrupt_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	(void)ac;
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
