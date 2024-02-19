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
    int		i;
    int		j;
    char	*new_str;
	char	quote;

	i = 0;
	j = 0;
    if (str == NULL)
        return NULL; 
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) * 2 + 1));
    if (new_str == NULL)
        return NULL;
    while (str[i] != '\0') 
	{
		if (str[i] == '\'' || str[i] == '\"')
		{	
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote) 
			{
				if (is_meta_char_quote(str[i], quote)) 
					new_str[j++] = '\\';
				new_str[j++] = str[i++];
			}
			i++;
		}
		new_str[j++] = str[i++];
    }
	free(str);
    new_str[j] = '\0';
    return new_str;
}