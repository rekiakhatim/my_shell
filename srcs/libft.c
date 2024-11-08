/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:45:50 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/31 21:30:36 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = ft_strlen(s1) * sizeof(char);
	s2 = (char *)ft_calloc(i + 2, 1);
	if (!s2)
		return (NULL);
	s2[0] = '\0';
	if (!s1)
		return (s2);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*my_strjoin(char *s1, char *s2)
{
	char			*strjoin;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = 0;
	if (!s2)
		s2 = my_strdup("");
	if (!s1)
		s1 = my_strdup("");
	strjoin = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, 1);
	if (!strjoin)
		return (NULL);
	while (s1[++i])
		strjoin[i] = s1[i];
	while (s2[j])
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	free(s1);
	return (strjoin);
}

char	*my_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (my_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = ft_calloc(len + 2, sizeof(char));
	if (!substr)
		return (NULL);
	while (s[start] && i < len && start < ft_strlen(s))
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
