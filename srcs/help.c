/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:13:49 by blackstar         #+#    #+#             */
/*   Updated: 2024/10/09 19:48:37 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_single_quoted(char *str, int index, bool flag)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] && i <= index)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = 1;
			j = i;
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
	if (str[j] != '\'')
		flag = 0;
	return (flag);
}

bool	char_checker(char c)
{
	if ((c >= 'a' && c <= 'z') || c == '_'
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	size_ofdouble(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (str && str[0] && str[0][0] == '\0')
		return (0);
	return (i);
}

int	not_white_space(char *str, int i)
{
	if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		return (0);
	return (1);
}

int	white_space_checker(char *str, int start, int end)
{
	while (str[start] && start < end)
	{
		if (str[start] != 32 && (str[start] < 9 || str[start] > 13))
			return (0);
		start++;
	}
	return (1);
}
