/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:54:36 by rkhatim           #+#    #+#             */
/*   Updated: 2024/10/31 16:59:04 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valide_keyname(char *str)
{
	int i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return(-2);
	i++;
	while (str[i] && str[i] != '=')
	{
		if(str[i] != '_' && !ft_isalnum(str[i]))
			return(-3);
		i++;
	}
	if (!str[i])
		return (-1);
	return (i);
}

char	*key_name(char *str, int len)
{
	char *var;
	int i;

	if(len == -1)
		len = ft_strlen(str);
	else
		len++;
	var = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while(i < len)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*export_value(char *str)
{
	char *returned;
	int start;
	int len;

	start = valide_keyname(str);
	if (start <= -1)
		return (NULL);
	start++;
	if(!str[start])
		return(my_strdup(""));
	len = ft_strlen(str);
	returned = ft_substr(str, start, len - start);
	return(returned);
}

void	my_env(void)
{
	int i;

	i = 0;
	while (g_main.env && g_main.env[i])
	{
		if(valide_keyname(g_main.env[i]) > -1)
			printf("%s\n", g_main.env[i]);
		i++;
	}
}
