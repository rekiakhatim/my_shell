/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:29:10 by blackstar         #+#    #+#             */
/*   Updated: 2024/10/31 21:31:28 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_masking(int *arr, int i)
{
	if (arr[i] == 32 || (arr[i] >= 9 && arr[i] <= 13))
		return (0);
	return (1);
}

void	skip_for_expaned(t_lexer *token, int j, int i, int a)
{
	int	*arr;
	int	k;

	token->last_joind = ft_calloc(sizeof(char *),
			arr_size(token->expanded_value) + 1);
	while (token->expanded_value[++j])
	{
		arr = save_index(token->expanded_value[j]);
		i = ft_strlen(token->expanded_value[j])
			- total_removal_quotes(token->expanded_value[j]);
		token->last_joind[j] = ft_calloc(sizeof(char), i + 1);
		i = -1;
		a = 0;
		k = 0;
		while (token->expanded_value[j][++i])
		{
			if (i != arr[a])
				token->last_joind[j][k++] = token->expanded_value[j][i];
			else
				a++;
		}
		token->last_joind[j][k] = '\0';
		free(arr);
	}
	token->last_joind[j] = NULL;
}

void	search_for_expand2(t_lexer *ptr, int *i, int *j, int *a)
{
	char	*s;

	while (ptr->content[*i] && char_checker(ptr->content[*i]))
		*i += 1;
	s = my_substr(ptr->content, *j, *i - (*j));
	if (s)
	{
		ptr->expanded_value[*a] = my_strdup(get_env(s));
		free(s);
	}
	if (!ptr->expanded_value[*a])
		ptr->expanded_value[*a] = my_strdup("");
	*a += 1;
	if (ptr->content[*i])
		*i -= 1;
}
