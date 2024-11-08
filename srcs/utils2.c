/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:59:53 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/13 17:21:00 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_file(t_lexer *token)
{
	t_lexer	*ptr;

	ptr = token;
	while (ptr)
	{
		if (ptr->previous && (ptr->previous->type == RO_APPEND
				|| ptr->previous->type == ROP || ptr->previous->type == RIP))
			ptr->type = FILENAME;
		else if (ptr->previous && ptr->previous->type == HERE_DOC)
			ptr->type = DELIMITER;
		ptr = ptr->next;
	}
}

int	args_nbr(t_lexer *token)
{
	t_lexer	*ptr;
	int		j;
	int		counter;

	ptr = token;
	counter = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == WORD)
		{
			j = -1;
			while (ptr->last_joind[++j])
				counter++;
		}
		ptr = ptr->next;
	}
	return (counter);
}

void	fillin_args(t_lexer *token, t_cmd *command)
{
	t_lexer	*ptr;
	int		i;

	ptr = token;
	i = 0;
	command->arguments = ft_calloc(args_nbr(ptr) + 2, sizeof(char *));
	if (!command->arguments)
		return ;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == WORD && (ptr->previous == NULL
				|| (ptr->previous && ptr->previous->type != HERE_DOC)))
			i = duplicate_2d(ptr->last_joind, command->arguments, i);
		else if (ptr->type == WORD)
		{
			command->arguments[i] = my_strdup(ptr->content);
			i++;
		}
		ptr = ptr->next;
	}
	command->arguments[i] = NULL;
}

t_lexer	*handle_files(t_lexer *token, t_file **file)
{
	t_file	*tmp;

	while (token && token->type != PIPE)
	{
		tmp = NULL;
		if (token->type == FILENAME)
		{
			tmp = new_file(token->last_joind[0], token->previous->type);
			add_file(file, tmp);
		}
		else if (token->type == DELIMITER)
		{
			tmp = new_file(token->content, token->previous->type);
			add_file(file, tmp);
		}
		token = token->next;
	}
	return (token);
}

void	reform_list(t_info *data, t_cmd **command)
{
	t_lexer	*token;
	t_cmd	*temp;

	token = data->tokens;
	while (token)
	{
		if (token->type != PIPE)
		{
			temp = new_cmd(NULL);
			fillin_args(token, temp);
			token = handle_files(token, &temp->file);
			add_cmd(command, temp);
		}
		if (token)
			token = token->next;
	}
}
