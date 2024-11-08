/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:41:31 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/13 16:21:53 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*my_lstnew(char *content)
{
	t_lexer	*ptr;

	ptr = (t_lexer *)ft_calloc(sizeof(t_lexer), 1);
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->type = -1;
	ptr->expanded_value = NULL;
	ptr->parse_expanded = NULL;
	ptr->last_joind = NULL;
	ptr->previous = NULL;
	ptr->next = NULL;
	return (ptr);
}

void	my_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*ptr;

	ptr = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
		new->previous = ptr;
	}
}

void	create_and_add(t_info *data, char *content)
{
	t_lexer	*ptr;

	ptr = my_lstnew(content);
	my_lstadd_back(&data->tokens, ptr);
}
