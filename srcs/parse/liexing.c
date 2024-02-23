#include "../../includes/minishell.h"

void	add_token(char **command_split, t_token_list **head, t_mini *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command_split[i])
	{
		if (command_split[i][j] == '<')
		{
			if (command_split[i][j + 1] == '<')
			{
				append_token_node(head, HERE_DOC, command_split[i + 1]);
				append_token_node(head, PIPE, 0);
				m->heredoc_status = 1;
			}
			else
				append_token_node(head, REDIR_IN, command_split[i + 1]);
			i++;
		}
		else if (command_split[i][j] == '>')
		{
			if (command_split[i][j + 1] == '>')
			{
				append_token_node(head, APPEND, command_split[i + 1]);
				m->status_append = 1;
				i++;
			}
			else
			{
				append_token_node(head, REDIR_OUT, command_split[i + 1]);
				m->status_redir_out = 1;
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

void	do_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	do_redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	do_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void handle_token(t_token_list *current, t_mini *mini, int *i)
{
    if (current->token == COMMAND)
        mini->cmd[(*i)++] = ft_strdup(current->value);
    else if (current->token == REDIR_IN)
        do_redir_in(current->value);
    else if (current->token == REDIR_OUT)
    {
        mini->status_redir_out = 1;
        do_redir_out(current->value);
    }
    else if (current->token == APPEND)
    {
        mini->status_append = 1;
        do_append(current->value);
    }
    else if (current->token == HERE_DOC)
    {
        mini->heredoc_status = 1;
        mini->cmd[(*i)++] = ft_strdup(current->value);
    }
	//mini->cmd[(*i)] = NULL;
}

void	group_command_args(t_token_list **current, t_mini *mini)
{
    int	i;

	if (!(*current) || !(*current)->next)
		return ;
    i = 0;
    mini->status_redir_out = 0;
    mini->status_append = 0;
    mini->heredoc_status = 0;
    mini->cmd = (char **)malloc(sizeof(char *) * (get_number_of_args(current) + 1));
    while ((*current)->token != END && (*current)->token != PIPE)
    {
        handle_token(*current, mini, &i);
        (*current) = (*current)->next;
    }
    mini->cmd[i] = NULL;
}

int	get_number_of_args(t_token_list **current)
{
	int	i;
	t_token_list *head;

	head = *current;
	i = 0;
	while ((*current) && (*current)->token != END && (*current)->token != PIPE)
	{
		if ((*current)->token == COMMAND)
			i++;
		(*current) = (*current)->next;
	}
	(*current) = head;
	return (i);
}

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
}