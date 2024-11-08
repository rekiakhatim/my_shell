/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:27:30 by yuki              #+#    #+#             */
/*   Updated: 2024/11/07 22:01:23 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_split_result(char **split_result)
{
    int i = 0;
    if (!split_result)
        return;
    
    while (split_result[i])
    {
        free(split_result[i]);
        i++;
    }
    free(split_result);
}

char *check_direct_path(char *cmd)
{
    if (ft_strchr(cmd, '/') != NULL)
    {
        if (access(cmd, X_OK) == 0)
            return (cmd);
        else
        {
            perror(cmd);
            exit(g_main.exit_status);
        }
    }
    return (NULL);
}

char *get_path_env(void)
{
    int i;
    char *path_env;

    i = 0;
    while (g_main.env[i] != NULL)
    {
        if (ft_strncmp(g_main.env[i], "PATH=", 5) == 0)
        {
            path_env = g_main.env[i] + 5;
            return (path_env);
        }
        i++;
    }
    return (NULL);
}

char *create_full_path(char *dir, char *cmd)
{
    char *temp;
    char *full_path;

    temp = ft_strjoin(dir, "/");
    if (!temp)
        return (NULL);
    full_path = ft_strjoin(temp, cmd);
    free(temp);
    return (full_path);
}

char *get_command_path(char *cmd)
{
    char *path_env;
    char **path_dirs;
    char *full_path;
    int i;

    path_env = get_path_env();
    if (check_direct_path(cmd))
        return (cmd);
    if (!path_env || path_env[0] == '\0')
        return (NULL);
    path_dirs = ft_split(path_env, ':');
    if (!path_dirs)
        return (NULL);
    i = 0;
    while (path_dirs[i])
    {
        full_path = create_full_path(path_dirs[i], cmd);
        if (!full_path || (access(full_path, F_OK) == 0
         && access(full_path, X_OK) == 0))
        {
            free_split_result(path_dirs);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_split_result(path_dirs);
    return (NULL);
}
