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

bool	count_quotes(const char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;
	
	single_quote = 0;
	double_quote = 0;
	if (!str)
		return (true);
	i = 0;
	while(str[i])
	{
		if (str[i] == '\'')
			single_quote++;
		if (str[i] == '\"')
			double_quote++;
		i++;
	}
	if (single_quote % 2 == 1 || double_quote % 2 == 1)
		return (false);
	return (true);
}


bool check_wrong_command(t_token_list* current)
{
	bool	command;

	while (current && current->token != END) {
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
            break;
    }
    return command;
}

char *quote_things(char *str)
{
	int i = 0;
	int j = 0;
	char *new_str;
	char quote;

	if (str == NULL)
		return NULL; 
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_str == NULL)
		return NULL;
	while (str[i] != '\0') 
	{
		if (str[i] == '\'' || str[i] == '\"')
		{   
			quote = str[i++];
			while (str[i] && str[i] != quote) 
			{
				if (str[i] == '\\' && str[i + 1] == quote)
					new_str[j++] = str[++i];
				else if (str[i] == '$' && str[i + 1] == quote)
				{
					new_str[j++] = str[i++];
					new_str[j++] = str[i++];
				}
				else
					new_str[j++] = str[i++];
			}
			i++;
		}
		else if (str[i] == '\\' && str[i + 1] == '\"')
			new_str[j++] = str[++i];
		else
			new_str[j++] = str[i++];
	}
	free(str);
	new_str[j] = '\0';
	return new_str;
}

bool	is_between_quotes(char *str, int i)
{
	int	quote;
	int	j;

	quote = 0;
	j = 0;
	while (j < i)
	{
		if (str[j] == '\'' && is_between_double_quotes(str, j) == false)
			quote++;
		j++;
	}
	return (quote % 2 == 1);
}

bool	is_between_double_quotes(char *str, int i)
{
	int	quote;
	int	j;

	quote = 0;
	j = 0;
	while (j < i)
	{
		if (str[j] == '\"')
			quote++;
		j++;
	}
	return (quote % 2 == 1);
}

char	*expand_variable(char *str, t_mini *m)
{
	int		i;
	int		j;
	char	*var;
	char	*value;
	char	*new_str;
	
	 if (!str)
		return (NULL); 
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '$' && is_between_quotes(str, i) == false)
		{
			var = ft_strdup(str + i + 1);
			while (var[j] && (ft_isalnum(var[j]) || var[j] == '_'))
				j++;
			var[j] = '\0';
			value = target_path(m->envm, var);
			if (value)
			{
				new_str = ft_strjoin(ft_substr(str, 0, i), value + 1);
				new_str = ft_strjoin(new_str, ft_strdup(str + i + j + 1));
				free(str);
				str = new_str;
			}
			else
				return (NULL);
			free(var);
		}
		i++;
	}
	return (str);
}