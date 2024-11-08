/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:00:52 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/04 23:13:00 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	total_removal_quotes(char *str)
{
	int	counter;
	int	i;

	counter = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '"')
			&& !is_quoted(str, i, 0))
			counter++;
	}
	return (counter);
}

int	*save_index(char *str)
{
	int	*returned;
	int	i;
	int	j;

	i = total_removal_quotes(str);
	returned = ft_calloc(i + 1, sizeof(int));
	if (i == 0)
		returned[0] = -1;
	else
	{
		i = -1;
		j = 0;
		while (str[++i])
		{
			if ((str[i] == '\'' || str[i] == '"')
				&& !is_quoted(str, i, 0))
				returned[j++] = i;
		}
	}
	return (returned);
}

int	arr_size(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

void	skip_for_token(t_lexer *token)
{
	int	*arr;
	int	i;
	int	j;
	int	a;

	a = 0;
	j = -1;
	arr = save_index(token->content);
	token->last_joind = ft_calloc(sizeof(char *), 2);
	if (!token->last_joind)
		return ;
	i = ft_strlen(token->content) - total_removal_quotes(token->content);
	token->last_joind[0] = ft_calloc(sizeof(char), i + 1);
	i = 0;
	while (token->content[++j])
	{
		if (j != arr[a])
			token->last_joind[0][i++] = token->content[j];
		else
			a++;
	}
	token->last_joind[0][i] = '\0';
	token->last_joind[1] = NULL;
	free(arr);
}

void	skip_quotes(t_lexer	*token)
{
	int	j;
	int	i;
	int	a;

	i = -1;
	a = 0;
	j = -1;
	if (token->previous == NULL || (token->previous
			&& token->previous->type != HERE_DOC))
		skip_for_expaned(token, j, i, a);
	else
		skip_for_token(token);
}
