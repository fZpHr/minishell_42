#include "../../includes/minishell.h"

int		count_word_command(const char *command)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (command[i] != '\0')
    {
        if (command[i] == '|' && command[i + 1] != '|')
            count++;
        else if (command[i] == '>' && command[i + 1] != '>')
            count++;
        else if (command[i] == '<' && command[i + 1] != '<')
            count++;
        else if (command[i] == '>' && command[i + 1] == '>')
        {	
            count++;
            i++;
        }
        else 
            count_word_command_2(command, &i, &count);
        i++;
    }
    return count;
}

void	count_word_command_2(const char *command, int* i, int* count)
{
    if (command[*i] == '<' && command[*i + 1] == '<')
    {
        (*count)++;
        (*i)++;
    }
    else if (ft_isalnum(command[*i]) && !ft_isalnum(command[*i + 1]))
        (*count)++;
    else if (command[*i] == '\"' && command[*i + 1] != '\"')
    {	
        (*count)++;
        *i = skip_char('\"', command, *i);
    }
    else if (command[*i] == '\'' && command[*i + 1] != '\'')
    {	
        (*count)++;
        *i = skip_char('\'', command, *i);
    }
}

char** ft_split_command(const char* command)
{
	int result_size = 0;
	int result_capacity = count_word_command(command) + 1;
    char** result = malloc(result_capacity * sizeof(char*));
	int i = 0;
	int j = 0;
	int command_length = strlen(command);
	char* current_group = NULL;
	int in_single_quotes = 0;
	int in_double_quotes = 0;

	while (i < command_length)
	{
		if (command[i] == '\'')
		{
			in_single_quotes = !in_single_quotes;
		}
		else if (command[i] == '\"')
		{
			in_double_quotes = !in_double_quotes;
		}
		if (!in_single_quotes && !in_double_quotes)
		{
			if ((command[i] == '<' || command[i] == '>') && command[i + 1] == command[i])
			{
				if (current_group != NULL)
				{
					if (result_size >= result_capacity)
					{
						result_capacity += 10;
						//result = realloc(result, result_capacity * sizeof(char*));
					}
					result[result_size] = ft_strdup(current_group);
					result_size++;
					free(current_group); // Free current_group here
					current_group = NULL;
				}

				if (result_size >= result_capacity)
				{
					result_capacity += 10;
					//result = realloc(result, result_capacity * sizeof(char*));
				}
				result[result_size] = malloc(3);
				result[result_size][0] = command[i];
				result[result_size][1] = command[i + 1];
				result[result_size][2] = '\0';
				result_size++;
				i++; // Skip the next character
			}
			else if (command[i] == '<' || command[i] == '>' || command[i] == '|')
			{
				if (current_group != NULL)
				{
					if (result_size >= result_capacity)
					{
						result_capacity += 10;
						//result = realloc(result, result_capacity * sizeof(char*));
					}
					result[result_size] = ft_strdup(current_group);
					result_size++;
					free(current_group); // Free current_group here
					current_group = NULL;
				}

				if (result_size >= result_capacity)
				{
					result_capacity += 10;
					//result = realloc(result, result_capacity * sizeof(char*));
				}
				result[result_size] = malloc(2);
				result[result_size][0] = command[i];
				result[result_size][1] = '\0';
				result_size++;
			}
			else if (command[i] == ' ')
			{
				if (current_group != NULL)
				{
					if (result_size >= result_capacity)
					{
						result_capacity += 10;
						//result = realloc(result, result_capacity * sizeof(char*));
					}
					result[result_size] = ft_strdup(current_group);
					result_size++;
					free(current_group); // Free current_group here
					current_group = NULL;
				}
			}
			else
			{
				if (current_group == NULL)
				{
					current_group = malloc(command_length - i + 2);
					j = 0;
				}
				current_group[j] = command[i];
				j++;
				current_group[j] = '\0';
			}
		}
		else
		{
			if (current_group == NULL)
			{
				current_group = malloc(command_length - i + 2);
				j = 0;
			}
			current_group[j] = command[i];
			j++;
			current_group[j] = '\0';
		}
		i++;
	}
	if (current_group != NULL)
	{
		if (result_size >= result_capacity)
		{
			result_capacity += 10;
			//result = realloc(result, result_capacity * sizeof(char*));
		}
		result[result_size] = ft_strdup(current_group);
		result_size++;
		free(current_group); // Free current_group here
		current_group = NULL;
	}
	if (result_size >= result_capacity)
	{
		result_capacity += 10;
		//result = realloc(result, result_capacity * sizeof(char*));
	}
	result[result_size] = NULL;
	return result;
}
 
int	skip_char(char c, const char *command, int i)
{
	i++;
	while (command[i] != c)
		i++;
	i++;
	return (i);
}