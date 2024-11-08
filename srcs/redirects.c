/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:13:58 by yuki              #+#    #+#             */
/*   Updated: 2024/11/07 22:17:27 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return ;
    write(fd, s, ft_strlen(s));
}
void    print_error2(char *filename, int error_type)
{
    ft_putstr_fd("bash : ", 2);
    ft_putstr_fd(filename, 2);
    if (error_type == 1)
        ft_putstr_fd(": No such file or directory\n", 2);
    else if (error_type == 2)
        ft_putstr_fd(": Permission denied\n", 2);
    else if (error_type == 3)
        ft_putstr_fd(": Is a directory\n", 2);
}

 // Returns: 0 = success, 1 = no file, 2 = permission denied, 3 = is directory
int check_input_access(char *filename)
{
    struct stat file_stat;

    if (access(filename, F_OK) == -1)
        return (1);
    if (stat(filename, &file_stat) == 0
        && S_ISDIR(file_stat.st_mode))
        return (3);
    if (access(filename, R_OK) == -1)
        return (2);
    return (0);
}

int check_output_access(char *filename)
{
    struct stat file_stat;

    if (access(filename, F_OK) == 0)
    {
        if (stat(filename, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
            return (3);
        if (access(filename, W_OK) == -1)
            return (2);
    }
    return (0);
}

int handle_fd_redirect(int fd, int target_fd, char *filename)
{
    if (fd == -1)
    {
        print_error2(filename, 2);
        return (1);
    }
    if (dup2(fd, target_fd) == -1)
    {
        close(fd);
        print_error2(filename, 2);
        return (1);
    }
    close(fd);
    return (0);
}

int handle_input_redirection(t_file *file)
{
    int error;
    int fd;

    error = check_input_access(file->filename);
    if (error)
    {
        print_error2(file->filename, error);
        return (1);
    }
    fd = open(file->filename, O_RDONLY);
    return (handle_fd_redirect(fd, STDIN_FILENO, file->filename));
}

int handle_output_redirection(t_file *file, int append_mode)
{
    int error;
    int fd;
    int flags;

    error = check_output_access(file->filename);
    if (error)
    {
        print_error2(file->filename, error);
        return (1);
    }
    flags = O_WRONLY | O_CREAT | (append_mode ? O_APPEND : O_TRUNC);
    fd = open(file->filename, flags, 0644);
    return (handle_fd_redirect(fd, STDOUT_FILENO, file->filename));
}

int handle_heredoc_redirection(t_file *file)
{
    int fd;

    if (!file->filename)
    {
        print_error2("heredoc", 1);
        return (1);
    }
    fd = open(file->filename, O_RDONLY);
    //printf("my fd issssss %d \n",fd);
    if (handle_fd_redirect(fd, STDIN_FILENO, file->filename))
        return (1);
    unlink(file->filename);
    return (0);
}

int handle_redirections(t_file *files)
{
    t_file *current;
    int status;

    current = files;
    while (current)
    {
        if (current->type == RIP)
            status = handle_input_redirection(current);
        else if (current->type == ROP)
            status = handle_output_redirection(current, 0);
        else if (current->type == RO_APPEND)
            status = handle_output_redirection(current, 1);
        else if (current->type == HERE_DOC)
            status = handle_heredoc_redirection(current);
        else
            return ((ft_putstr_fd("minishell: Invalid redirection type\n", 2)), 1);
        if (status)
            return (status);
        current = current->next;
    }
    return (0);
}

int execute_command(t_cmd *cmd)
{
    // pid_t pid;
    // int status;
    char *executable_path = NULL;

    if(!cmd->arguments[0])
        return g_main.exit_status;
    executable_path = get_command_path(cmd->arguments[0]);
    if (executable_path == NULL)
    {
        if((access(cmd->arguments[0],F_OK) == 0) && (access(cmd->arguments[0],X_OK) == 0))
        {
            execve(cmd->arguments[0], cmd->arguments, g_main.env);
            perror(cmd->arguments[0]);
            exit(1);
        }
        ft_putstr_fd(cmd->arguments[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        g_main.exit_status = 127;
        return g_main.exit_status;
    }
    // pid = fork();
    // if (pid == -1)
    // {
    //     perror("fork failed");
    //     free(executable_path);
    //     return 1;
    // }
    // if (pid == 0)  // Child process
    // {
        // if (handle_redirections(cmd->file))
        // {
        //     free(executable_path);
        //     exit(1);
        // }
        execve(executable_path, cmd->arguments, g_main.env);
        perror("execve failed");
        free(executable_path);
        // exit(1);
    // }
    // free(executable_path);//free exect path in parent p
    // waitpid(pid, &status, 0); //wait for child to finish
    // if (WIFEXITED(status))
    //     g_main.exit_status = WEXITSTATUS(status);
    // else if (WIFSIGNALED(status))
    //     g_main.exit_status = 128 + WTERMSIG(status);

    return g_main.exit_status;
}


