/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/04 20:27:10 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal_flag[4];

void	print_token(t_token token)
{
	switch (token)
	{
	case COMMAND:
		printf("COMMAND");
		break ;
	case ARGS:
		printf("ARGS");
		break ;
	case PIPE:
		printf("PIPE");
		break ;
	case REDIR_IN:
		printf("REDIR_IN");
		break ;
	case REDIR_OUT:
		printf("REDIR_OUT");
		break ;
	case APPEND:
		printf("APPEND");
		break ;
	case HERE_DOC:
		printf("HERE_DOC");
		break ;
	case END:
		printf("END");
		break ;
	default:
		printf("UNKNOWN");
		break ;
	}
}

void	print_token_list(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		print_token(current->token);
		printf(": %s\n", current->value);
		current = current->next;
	}
}

void	interrupt_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("g_signal_flag[2] = %d\n", g_signal_flag[2]);
		if (g_signal_flag[2] == 1)
		{
			g_signal_flag[3] = 1;
			g_signal_flag[2] = 0;
		}
		else if (g_signal_flag[3] == 0)
		{
			g_signal_flag[0] = 1;
			g_signal_flag[1] = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
			g_signal_flag[0] = 0;
		}
	}
	else if (sig == SIGQUIT)
	{
		return ;
	}
}

void	check_error_quotes(t_mini *m)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (m->input && m->input[i])
	{
		if (m->input[i] == '\'' && is_between_double_quotes(m->input, i) == 0)
			single_quotes++;
		if (m->input[i] == '\"' && is_between_quotes(m->input, i) == 0)
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		m->parse_error = 1;
	}
	else
		m->parse_error = 0;
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
		/* 	if ((*current)->token == HERE_DOC
				&& (*current)->next->next->token != COMMAND)
				m->ac = 0; */
		(*current) = (*current)->next;
	}
	(*current) = m->head;
	// print_token_list(*current);
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
