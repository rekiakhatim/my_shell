/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:42:25 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/13 16:19:07 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_parsed_to_expanded(t_lexer *token, int dup_i, int dolar_i, int j)
{
	char	c;
	char	s[2];

	if (token->parse_expanded[dolar_i][j])
	{
		c = (char)token->parse_expanded[dolar_i][j];
		s[0] = c;
		s[1] = '\0';
		token->expanded_value[dup_i]
			= my_strjoin(token->expanded_value[dup_i], s);
	}
}

void	helper(int *i, int dup_i, t_lexer *token)
{
	char	*s;
	int		a;

	a = *i;
	while (token->content[*i] && (token->content[*i] != '$'
			|| is_single_quoted(token->content, *i, 0)
			|| !token->content[*i + 1] || (token->content[*i + 1] != '?'
			&& !char_checker(token->content[*i + 1]))))
		*i += 1;
	if (a < (*i))
	{
		s = my_substr(token->content, a, (*i) - a);
		token->expanded_value[dup_i]
			= my_strjoin(token->expanded_value[dup_i], s);
		free(s);
	}
}

void	helper2(t_lexer *token, int *dolar_i, int *dup_i)
{
	int	j;

	j = -1;
	*dolar_i += 1;
	while (token->parse_expanded[*dolar_i]
		&& token->parse_expanded[*dolar_i][++j])
	{
		while (token->parse_expanded[*dolar_i][j] == END_OF_STR)
			j++;
		if (j > 0 && token->expanded_value[*dup_i]
			&& token->parse_expanded[*dolar_i][j - 1] == END_OF_STR)
			*dup_i += 1;
		join_parsed_to_expanded(token, *dup_i, *dolar_i, j);
	}
}

void	join_the_final(t_lexer *token, int dolar_nb)
{
	int	i;
	int	dolar_i;
	int	dup_i;

	dolar_i = -1;
	dup_i = 0;
	free_double(token->expanded_value);
	i = str_counter(token, dolar_nb) + 1;
	token->expanded_value = ft_calloc(sizeof(char *), i);
	i = 0;
	while (token->content[i])
	{
		helper(&i, dup_i, token);
		if (token->content[i] == '$' && token->content[i + 1]
			&& !is_single_quoted(token->content, i, 0))
			helper2(token, &dolar_i, &dup_i);
		if (token->content[++i] && token->content[i] == '?')
			i++;
		else
			while (token->content[i] && char_checker(token->content[i]))
				i++;
	}
}

int	expander(t_info *data)
{
	t_lexer	*ptr;
	int		temp;

	ptr = data->tokens;
	if (!ptr)
		return (0);
	while (ptr)
	{
		temp = dolar_counter(ptr->content);
		if (ptr->type == WORD && (ptr->previous == NULL
				|| (ptr->previous && ptr->previous->type != HERE_DOC)))
		{
			search_for_expand(ptr);
			convert_to_int(ptr, temp);
			masking_white_spaces(ptr);
			join_the_final(ptr, temp);
		}
		if (ptr->type == WORD)
			skip_quotes(ptr);
		ptr = ptr->next;
	}
	if(!syntax_error(data))
		return (0);
	return (1);
}
