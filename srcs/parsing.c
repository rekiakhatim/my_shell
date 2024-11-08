/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:36:56 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/24 12:55:34 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted(char *str, int index, bool flag)
{
	int	i;
	int	j;

	i = -1;
	if (index == -1)
		index = ft_strlen(str) + 1;
	while (str[++i] && i <= index)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = 1;
			j = i;
			if (i == index)
				flag = 0;
			while (str[++i] && i <= index)
			{
				if (str[i] == str[j])
				{
					flag = 0;
					break ;
				}
			}
		}
	}
	return (flag);
}

bool	type_content(char *content, char *str, size_t size)
{
	if (!ft_strncmp(content, str, size)
		&& ft_strlen(content) == size)
		return (0);
	return (1);
}

void	classify_tokens(t_info *data)
{
	t_lexer	*ptr;

	ptr = data->tokens;
	while (ptr)
	{
		if (!type_content(ptr->content, "|", 1))
			ptr->type = PIPE;
		else if (!type_content(ptr->content, "<", 1))
			ptr->type = RIP;
		else if (!type_content(ptr->content, ">", 1))
			ptr->type = ROP;
		else if (!type_content(ptr->content, ">>", 2))
			ptr->type = RO_APPEND;
		else if (!type_content(ptr->content, "<<", 2))
			ptr->type = HERE_DOC;
		else
			ptr->type = WORD;
		ptr = ptr->next;
	}
}

int	duplicate_2d(char **str, char **dup, int i)
{
	int	j;

	j = -1;
	while (str[++j])
	{
		dup[i] = my_strdup(str[j]);
		i++;
	}
	return (i);
}

void    print_list(t_cmd *command)
{
	t_cmd   *temp;
	t_file  *ptr;

	temp = command;
	while (temp)
	{
		printf("\n---------------------------------\n");
		int i =-1;
		while (temp && temp->arguments[++i])
			printf("arg[%i] = [%s]\n", i, temp->arguments[i]);
		if (temp && temp->file)
		{
			ptr = temp->file;
			while (ptr)
			{
				printf("file name is [%s]\n", ptr->filename);
				printf("type : %d\n", ptr->type);
				ptr = ptr->next;
			}
		}
		printf("\n---------------------------------\n");
		temp = temp->next;
	}
}

t_cmd	*parse_input(t_info *data, char *str)
{
	t_cmd	*command;

	command = NULL;
	if (is_quoted(str, -1, 0))
	{
		free(data);
		ft_khrej("unclosed quotes", 1);
		return (NULL);
	}
	tokenizing(data, str);
	classify_tokens(data);
	if (!expander(data))
		return (NULL);
	reform_list(data, &command);
	find_heredoc(command);
	return (command);
}
