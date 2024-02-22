#include "../../includes/minishell.h"

t_token_list	*create_token_node(t_token token, char *value)
{
	t_token_list	*node;

	node = (t_token_list *)malloc(sizeof(t_token_list));
	if (node)
	{
		node->token = token;
		node->value = value;
		node->next = NULL;
	}
	return (node);
}

void	append_token_node(t_token_list **head, t_token token, char *value)
{
	t_token_list	*new_node;
	t_token_list	*current;

	new_node = create_token_node(token, value);
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void	free_token_list(t_token_list *head)
{
	t_token_list	*current;
	t_token_list	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

int	count_pipe(t_token_list *current)
{
	int	count;

	count = 0;
	while (current->token != END)
	{
		if (current->token == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}
