#include "../../includes/minishell.h"

bool	is_meta_char_quote(char c, char quote)
{
	if (quote == '\'')
		return (c == '|' || c == '>' || c == '<' || c == ';' || c == '&'
			|| c == '(' || c == ')' || c == '\"' || c == '\\' || c == '$');
	else
		return (c == '|' || c == '>' || c == '<' || c == ';' || c == '&'
			|| c == '(' || c == ')' || c == '\'' || c == '\\');
}

bool	check_wrong_command(t_token_list *current)
{
	bool	command;

	while (current && current->token != END)
	{
		command = false;
		while (current && current->token != PIPE)
		{
			if (current->token == COMMAND)
				command = true;
			current = current->next;
		}
		if (command == false)
			return (false);
		if (current && current->next)
			current = current->next;
		else
			break ;
	}
	return (command);
}

char	*expand_variable_value(char *str, int i, int j, t_mini *m)
{
	char	*var;
	char	*value;
	char	*new_str;

	var = ft_strdup(str + i + 1);
	while (var[j] && (ft_isalnum(var[j]) || var[j] == '_'))
		j++;
	var[j] = '\0';
	value = target_path(m, m->envm, var, 1);
	if (value)
	{
		new_str = ft_strjoin(ft_substr(str, 0, i), value + 1);
		new_str = ft_strjoin(new_str, ft_strdup(str + i + j + 1));
		free(str);
		str = new_str;
	}
	else
	{
		free(var);
		return (NULL);
	}
	free(var);
	return (str);
}

char	*expand_variable(char *str, t_mini *m)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '$' && is_between_quotes(str, i) == false && str[i
			+ 1] != '?')
		{
			str = expand_variable_value(str, i, 0, m);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}
