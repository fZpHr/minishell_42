#include "../../includes/minishell.h"

char	*handle_quotes(char *str, char *new_str, int *i, int *j)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		if (str[*i] == '\\' && str[*i + 1] == quote)
			new_str[(*j)++] = str[++(*i)];
		else if (str[*i] == '\\')
			new_str[(*j)++] = str[*i];
		if (str[*i] == '$' && str[*i + 1] == quote)
		{
			new_str[(*j)++] = str[(*i)++];
			new_str[(*j)++] = str[(*i)++];
		}
		else
			new_str[(*j)++] = str[(*i)++];
	}
	(*i)++;
	return (new_str);
}

char	*quote_things(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * ((ft_strlen(str) * 2)));
	if (new_str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			new_str = handle_quotes(str, new_str, &i, &j);
		else if (str[i] == '\\' && str[i + 1] == '\"')
			new_str[j++] = str[++i];
		else
			new_str[j++] = str[i++];
	}
	free(str);
	new_str[j] = '\0';
	printf("new_str: %s\n", new_str);
	return (new_str);
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
