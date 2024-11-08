/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:20:44 by blackstar         #+#    #+#             */
/*   Updated: 2024/10/13 17:22:51 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str && str[++i])
			free(str[i]);
		free(str[i]);
		free(str);
	}
}

void	free_cmd(t_cmd *command)
{
	t_cmd	*temp;
	t_file	*tmp;

	temp = command;
	while (temp)
	{
		free_double(temp->arguments);
		tmp = command->file;
		while (tmp)
		{
			command->file = tmp->next;
			free(tmp->filename);
			free(tmp);
			tmp = command->file;
		}
		command = temp->next;
		free(temp);
		temp = command;
	}
}

void	ft_free(t_info *data, t_cmd *command)
{
	t_lexer	*ptr;
	int		i;

	ptr = data->tokens;
	while (ptr)
	{
		i = -1;
		free(ptr->content);
		free_double(ptr->expanded_value);
		free_double(ptr->last_joind);
		if (ptr->parse_expanded)
		{
			while (ptr->parse_expanded[++i])
				free(ptr->parse_expanded[i]);
			free(ptr->parse_expanded[i]);
			free(ptr->parse_expanded);
		}
		data->tokens = ptr->next;
		free(ptr);
		ptr = data->tokens;
	}
	free(data);
	if (command)
		free_cmd(command);
}
