/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:26:14 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/13 16:17:51 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_quotes(char *str, int i)
{
	if (str[++i])
	{
		while (str[i] && str[i] != ' ' && str[i] != '|'
			&& str[i] != '<' && str[i] != '>'
			&& str[i] != '\'' && str[i] != '"')
			i++;
	}
	return (i - 1);
}

char	*quotes_parser2(char *str, char *s, int *i, int *a)
{
	char	*temp;

	*i = after_quotes(str, *i);
	temp = my_substr(str, *a, (*i - (*a)) + 1);
	s = my_strjoin(s, temp);
	*a = *i + 1;
	free(temp);
	return (s);
}

char	*quotes_parser(char *str, int i, int *a)
{
	char	*s;
	int		j;

	s = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = i;
			while (str[++i])
			{
				if (str[i] == str[j])
				{
					s = quotes_parser2(str, s, &i, a);
					break ;
				}
			}
		}
		i++;
		if (!is_quoted(str, i, 0)
			&& !(str[i] == '\'' || str[i] == '"'))
			break ;
	}
	return (s);
}

int	separator_checker(t_info *data, char *str, int i, int j)
{
	if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ' '
		|| str[i] == '\n' || str[i] == '\t' || str[i] == '\v')
	{
		if (j <= i && !white_space_checker(str, j, i))
			create_and_add(data, my_substr(str, j, i - j));
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		{
			create_and_add(data, my_substr(str, i, 2));
			j = i + 2;
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			create_and_add(data, my_substr(str, i, 1));
			j = i + 1;
		}
		else
			j = i + 1;
	}
	else if (str[i] == '\'' || str[i] == '"')
		create_and_add(data, quotes_parser(str, i, &j));
	return (j);
}

void	tokenizing(t_info *data, char *str)
{
	int	j;
	int	i;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (i >= j && str[i + 1] == '\0' && not_white_space(str, i))
		{
			if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
				i--;
			create_and_add(data, my_substr(str, j, (i - j) + 1));
			j = i;
		}
		j = separator_checker(data, str, i ,j);
		if (j > i)
			i = j - 1;
	}
}
