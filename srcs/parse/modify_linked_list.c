/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:17:12 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/03/05 19:30:32 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_list	*is_here_doc_after(t_token_list *current)
{
	current = current->next;
	while (current->token != PIPE && current->token != END)
	{
		if (current->token == HERE_DOC)
			return (current);
		current = current->next;
	}
	return (0);
}

void	add_pipes_here_doc(t_token_list **head)
{
	t_token_list	*current;
	t_token_list	*save;

	current = (*head);
	while (current->token != END)
	{
		if (current->token == HERE_DOC && current->next->token != END
			&& current->next->token != PIPE)
		{
			save = current->next;
			current->next = create_token_node(PIPE, 0);
			current->next->next = save;
		}
		current = current->next;
	}
}
void print_token(t_token token) {
    switch(token) {
        case COMMAND: printf("COMMAND"); break;
        case ARGS: printf("ARGS"); break;
        case PIPE: printf("PIPE"); break;
        case REDIR_IN: printf("REDIR_IN"); break;
        case REDIR_OUT: printf("REDIR_OUT"); break;
        case APPEND: printf("APPEND"); break;
        case HERE_DOC: printf("HERE_DOC"); break;
        case END: printf("END"); break;
        default: printf("UNKNOWN"); break;
    }
}

void print_token_list(t_token_list *head) {
    t_token_list *current = head;

    while(current != NULL) {
        print_token(current->token);
        printf(": %s\n", current->value);
        current = current->next;
    }
}

void	modify_linked_list(t_token_list *head, t_mini *m, char **cmd)
{
	check_error_syntax_command(cmd, m);
	check_error_parsing_list(m, head);
	check_error_quotes(m);
	while (is_sorted_command(head) == false)
	{
		print_token_list(head);
		rearrange_token_list(&head);
	}
	add_pipes_here_doc(&head);
}
