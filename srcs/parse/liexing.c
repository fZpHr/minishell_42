#include "../../includes/minishell.h"

void	add_token(char **command_split, t_token_list **head)
{
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while(command_split[i])
	{
		if (command_split[i][j] == '<')
		{	
			if (command_split[i][j + 1] == '<')	
				append_token_node(head, HERE_DOC, command_split[i + 1]);
			else
				append_token_node(head, REDIR_IN, command_split[i + 1]);
			i++;
		}
		else if (command_split[i][j] == '>')
		{
			if (command_split[i][j + 1] == '>')
			{
				append_token_node(head, APPEND, command_split[i + 1]);
				i++;
			}
			else
			{
				append_token_node(head, REDIR_OUT, command_split[i + 1]);
				i++;
			}
		}
		else if (command_split[i][j] == '|')
			append_token_node(head, PIPE, 0);
		else
			append_token_node(head, COMMAND, command_split[i]);
		i++;
	}
	append_token_node(head, END, 0);
}

t_token_list	*group_command_args(t_token_list *current, t_mini *mini)
{
	int		i;
	t_token_list *head;
	int		count;
	
	head = current;
	count = get_number_of_args(current);
	current = head;
	i = 0;
	mini->cmd = (char **)malloc(sizeof(char *) * (count + 2));
	while (current && current->token != PIPE)
	{
		if (current->token == COMMAND)
		{
			mini->cmd[i] = ft_strdup(current->value);
			i++;
			current = current->next;
			while (current && current->token == COMMAND)
			{
				mini->cmd[i] = ft_strdup(current->value);
				i++;
				current = current->next;
			}
			mini->cmd[i] = NULL;
			break;
		}
		current = current->next;
	}
	while (current && current->token != PIPE)
		current = current->next;
	return current;
}

int		get_number_of_args(t_token_list *current)
{
	int		i;

	i = 0;
	while (current && current->token != END && current->token != PIPE)
	{
		if (current->token == COMMAND)
		{
			i++;
			current = current->next;
			while (current->token == ARGS)
				i++;
		}
		current = current->next;
	}
	return (i);
}