/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:12:28 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/13 17:22:15 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char **content)
{
	t_cmd	*ptr;

	ptr = ft_calloc(sizeof(t_cmd), 1);
	if (!ptr)
		return (NULL);
	ptr->arguments = content;
	ptr->file = NULL;
	ptr->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

void	add_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

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
		new->prev = ptr;
	}
}

t_file	*new_file(char *content, t_token type)
{
	t_file	*ptr;

	ptr = ft_calloc(1, sizeof(t_file));
	if (!ptr)
		return (NULL);
	if (content)
		ptr->filename = my_strdup(content);
	ptr->type = type;
	ptr->next = NULL;
	return (ptr);
}

void	add_file(t_file **lst, t_file *new)
{
	t_file	*ptr;

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
	}
}
