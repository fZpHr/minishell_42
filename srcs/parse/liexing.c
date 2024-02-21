#include "../../includes/minishell.h"

void	add_token(char **command_split, t_token_list **head, t_mini *m)
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
			{
				append_token_node(head, HERE_DOC, command_split[i + 1]);
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
	int		fd;
	
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
	int		fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void do_append(char *file)
{
	int		fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

t_token_list	*group_command_args(t_token_list *current, t_mini *mini)
{
	int		i;
	
	i = 0;
	mini->status_redir_out = 0;
	mini->status_append = 0;
	mini->cmd = (char **)malloc(sizeof(char *) * (get_number_of_args(current) + 2));
	while (current->token != END && current->token != PIPE)
	{
		if (current->token == COMMAND)
			mini->cmd[i++] = ft_strdup(current->value);
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
			mini->cmd[i++] = ft_strdup(current->value);
		current = current->next;
	}
	mini->cmd[i] = NULL;
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