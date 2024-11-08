/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:15:55 by hboustaj          #+#    #+#             */
/*   Updated: 2024/11/06 16:35:55 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *prepare_dlmt(char *str)
{
	int *arr;
	int i;
	int j;
	int a;
	char *s;

	arr = save_index(str);
	i = ft_strlen(str) - total_removal_quotes(str);
	s = ft_calloc(i + 2, sizeof(char));
	i = -1;
	j = 0;
	a = 0;
	while (str[++i])
	{
		if (arr && i != arr[a])
			s[j++] = str[i];
		else
			a++;
	}
	free(arr);
	return (s);
}

int    if_quots(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '"')
			return (1);
	return (0);
}

char    *take_value(char *line, int *i)
{
	char    *s;
	char    *returned;
	int     j;

	*i += 1;
	if (line[*i] == '?')
		return (ft_itoa(g_main.exit_status));
	j = *i;
	while (line[*i] && char_checker(line[*i]))
		*i += 1;
	s = my_substr(line, j, (*i) - j);
	*i -= 1;
	returned = my_strdup(get_env(s));
	free(s);
	return (returned);
}

char    *check_and_join(char *last, char *line, int a, int i)
{
	char *temp;

	if (a < i)
	{
		temp = my_substr(line, a, i - a);
		last = my_strjoin(last, temp);
		free(temp);
	}
	return (last);
}

char    *heredoc_expanding(char *line, int flag, char *last, int a)
{
	char    *temp;
	int     i;

	i = -1;
	if (!flag && line)
	{
		while (line[++i])
		{
			if (line[i] == '$' && (char_checker(line[i + 1])
				|| line[i + 1] == '?'))
			{
				last = check_and_join(last, line, a, i);
				temp = take_value(line, &i);
				last = my_strjoin(last, temp);
				a = i + 1;
				free(temp);
			}
		}
		last = check_and_join(last, line, a, i);
		return (last);
	}
	return (line);
}
char    *generate_filename(int i)
{
	char    *str;
	char    *temp;

	str = my_strdup("temp");
	temp = ft_itoa(i);
	str = my_strjoin(str, temp);
	free(temp);
	return (str);
}
int	rename_and_open(char **filename, int i)
{
	int 	fd;
	
	free(*filename);
	*filename = generate_filename(i);
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

void	child_for_heredoc(char	*eof, int flag, int fd)
{
	char    *last;
	char    *input;
	
	while (1)
	{
		input = readline(">");
		if (!input)
			break ;
		if((!ft_strncmp(input, eof, ft_strlen(input))
			&& ft_strlen(input) == ft_strlen(eof)))
			break ;
		last = heredoc_expanding(input, flag, NULL, 0);
		ft_putstr_fd(last, fd);
		ft_putstr_fd("\n",fd);
		free(last);
	}
	if (!input)
		write(1, "warning herdoc exited with EOF\n", 31);
	close(fd);
	exit(0);
}

void    handle_heredoc(t_file *file, int i)
{
	char    *eof;
	int     fd;
	int		flag;
	pid_t	pid;
	int 	status;
	
	eof = prepare_dlmt(file->filename);
	flag = if_quots(file->filename);
	fd = rename_and_open(&file->filename, i);
	pid = fork();
	if (!pid)
		child_for_heredoc(eof, flag, fd);
	else
		waitpid(pid, &status, 0);
	close(fd);
	free(eof);
}

void find_heredoc(t_cmd *command)
{
	t_cmd   *ptr;
	t_file  *temp;
	int     i;

	ptr = command;
	while (ptr)
	{
		if (ptr->file)
		{
			temp = ptr->file;
			i = 0;
			while (temp)
			{
				if (temp->type == HERE_DOC)
				{
					i++;
					handle_heredoc(temp, i);
				}
				temp = temp->next;
			}
		}
		ptr = ptr->next;
	}
}
