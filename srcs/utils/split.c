/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:41:43 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/27 13:19:06 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quotes_split(const char *command, t_split_command *sc)
{
	if (command[sc->i] == '\'')
		sc->in_single_quotes = !(sc->in_single_quotes);
	else if (command[sc->i] == '\"')
		sc->in_double_quotes = !(sc->in_double_quotes);
}

void	handle_special_chars(const char *command, t_split_command *sc)
{
	if ((command[sc->i] == '<' || command[sc->i] == '>') && command[sc->i
			+ 1] == command[sc->i])
		handle_double_chars(command, sc);
	else if (command[sc->i] == '<' || command[sc->i] == '>'
		|| command[sc->i] == '|')
		handle_single_char(command, sc);
	else if (command[sc->i] == ' ')
		handle_space(command, sc);
	else
		handle_regular_char(command, sc);
}

char	**ft_split_command(const char *command)
{
	t_split_command	sc;

	sc.result_size = 0;
	sc.result_capacity = count_word_command(command) + 2;
	sc.result = ft_calloc(sc.result_capacity, sizeof(char *) + 1);
	sc.i = 0;
	sc.j = 0;
	sc.command_length = strlen(command);
	sc.current_group = NULL;
	sc.in_single_quotes = 0;
	sc.in_double_quotes = 0;
	while (sc.i < sc.command_length)
	{
		handle_quotes_split(command, &sc);
		if (!sc.in_single_quotes && !sc.in_double_quotes)
			handle_special_chars(command, &sc);
		else
			handle_regular_char(command, &sc);
		sc.i++;
	}
	handle_end(&sc);
	sc.result[sc.result_size] = NULL;
	return (sc.result);
}

void	handle_end(t_split_command *sc)
{
	if (sc->current_group != NULL)
	{
		add_current_group_result(sc);
	}
}
