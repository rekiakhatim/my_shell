/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:13:07 by blackstar         #+#    #+#             */
/*   Updated: 2024/10/12 11:31:21 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dolar_counter(char *str)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (str[++i])
	{
		if (str[i] == '$' && !is_single_quoted(str, i, 0) && str[i + 1]
			&& (char_checker(str[i + 1]) || str[i + 1] == '?'))
			counter++;
	}
	return (counter);
}

void	search_for_expand(t_lexer *ptr)
{
	int	i;
	int	j;
	int	a;

	a = dolar_counter(ptr->content) + 1;
	i = -1;
	ptr->expanded_value = ft_calloc(sizeof(char *), a);
	a = 0;
	while (ptr->content[++i])
	{
		if (ptr->content[i] == '$' && (char_checker(ptr->content[i + 1])
				|| ptr->content[i + 1] == '?')
			&& !is_single_quoted(ptr->content, i, 0))
		{
			j = ++i;
			if (ptr->content[i] == '?')
			{
				ptr->expanded_value[a] = ft_itoa(g_main.exit_status);
				a++;
			}
			else if (char_checker(ptr->content[i]))
				search_for_expand2(ptr, &i, &j, &a);
		}
	}
}

void	masking_white_spaces(t_lexer *token)
{
	int	i;
	int	j;
	int	a;

	i = -1;
	j = -1;
	while (token->content[++i])
	{
		if (token->content[i] == '$' && !is_single_quoted(token->content, i, 0)
			&& token->content[i + 1] && (char_checker(token->content[i + 1])
				|| token->content[i + 1] == '?'))
		{
			j++;
			if (is_quoted(token->content, i, 0) == 0)
			{
				a = -1;
				while (token->parse_expanded[j][++a])
				{
					if (!check_for_masking(token->parse_expanded[j], a))
						token->parse_expanded[j][a] = END_OF_STR;
				}
			}
		}
	}
}

void	convert_to_int(t_lexer *token, int size)
{
	int	len;
	int	i;
	int	j;

	j = -1;
	token->parse_expanded = ft_calloc(sizeof(int *), size + 1);
	if (!token->parse_expanded)
		return ;
	while (token->expanded_value[++j])
	{
		i = -1;
		len = ft_strlen(token->expanded_value[j]);
		token->parse_expanded[j] = ft_calloc(sizeof(int), len + 2);
		if (!token->parse_expanded[j])
			return ;
		while (token->expanded_value[j][++i])
			token->parse_expanded[j][i] = (int )token->expanded_value[j][i];
		token->parse_expanded[j][i] = 0;
	}
}

int	str_counter(t_lexer *token, int size)
{
	int	counter;
	int	i;
	int	j;

	counter = 1;
	j = -1;
	while (++j < size)
	{
		i = -1;
		while (token->parse_expanded[j][++i] != 0)
		{
			if (token->parse_expanded[j][i] == END_OF_STR
				&& !(token->parse_expanded[j][i + 1] == 0
				|| token->parse_expanded[j][i + 1] == END_OF_STR))
				counter++;
		}
	}
	return (counter);
}
