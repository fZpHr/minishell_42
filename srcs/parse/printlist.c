#include "../../includes/minishell.h"

const char	*get_token_name(t_token token)
{
	switch (token)
	{
	case COMMAND:
		return ("COMMAND");
	case PIPE:
		return ("PIPE");
	case APPEND:
		return ("APPEND");
	case REDIR_IN:
		return ("REDIR_IN");
	case REDIR_OUT:
		return ("REDIR_OUT");
	case END:
		return ("END");
	case HERE_DOC:
		return ("HERE_DOC");
	default:
		return ("UNKNOWN");
	}
}


void	print_list(t_token_list *head)
{
	t_token_list *current = head;

	while (current != NULL)
	{
		printf("Token: %s, Value: %s\n", get_token_name(current->token),
			current->value);
		current = current->next;
	}
	current = head;
}