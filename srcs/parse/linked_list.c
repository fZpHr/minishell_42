#include "../../includes/minishell.h"

const char* get_token_name(t_token token)
{
	switch (token)
	{
		case COMMAND:
			return "COMMAND";
		case PIPE:
			return "PIPE";
		case APPEND:
			return "APPEND";
		case REDIR_IN:
			return "REDIR_IN";
		case REDIR_OUT:
			return "REDIR_OUT";
		case END:
			return "END";
		case HERE_DOC:
			return "HERE_DOC";
		default:
			return "UNKNOWN";
	}
}

t_token_list *create_token_node(t_token token, char *value)
{
	t_token_list *node = (t_token_list *)malloc(sizeof(t_token_list));
	
	if (node)
	{
		node->token = token;
		node->value = value;
		node->next = NULL;
	}
	return node;
}

void append_token_node(t_token_list **head, t_token token, char *value)
{
	t_token_list *new_node = create_token_node(token, value);
	
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		t_token_list *current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void free_token_list(t_token_list *head)
{
	t_token_list *current = head;
	
	while (current != NULL)
	{
		t_token_list *temp = current;
		current = current->next;
		free(temp);
	}
}
int	count_pipe(t_token_list *current)
{
	int count = 0;
	
	while (current->token != END)
	{
		if (current->token == PIPE)
			count++;
		current = current->next;
	}
	return count;
}

void print_list(t_token_list *head)
{
	t_token_list *current = head;
	
	while (current != NULL)
	{
		printf("Token: %s, Value: %s\n", get_token_name(current->token), current->value);
		current = current->next;
	}
}