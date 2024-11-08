/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:37:06 by hboustaj          #+#    #+#             */
/*   Updated: 2024/11/06 14:07:46 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib_ft/libft.h"

# define END_OF_STR 1945

struct s_main
{
	int		exit_status;
	char	**env;
	int		env_size;
};

extern struct s_main	g_main;

typedef enum s_token
{
	WORD,
	FILENAME,
	DELIMITER,
	PIPE,
	RIP,
	ROP,
	RO_APPEND,
	HERE_DOC
}	t_token;

typedef struct s_file
{
	char			*filename;
	int				type;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**arguments;
	int				pipefd[3];
	t_file			*file;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_lexer
{
	char			*content;
	char			**expanded_value;
	char			**last_joind;
	int				**parse_expanded;
	t_token			type;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_info
{
	t_lexer	*tokens;
}	t_info;

// parsing
char	*my_strdup(const char *s1);
char	*my_substr(char const *s, unsigned int start, size_t len);
char	*my_strjoin(char *s1, char *s2);
t_lexer	*my_lstnew(char *content);
void	my_lstadd_back(t_lexer **lst, t_lexer *new);
void	create_and_add(t_info *data, char *content);
bool	is_quoted(char *str, int index, bool flag);
bool	type_content(char *content, char *str, size_t size);
void	classify_tokens(t_info *data);
t_cmd	*parse_input(t_info *data, char *str);
int		after_quotes(char *str, int i);
int		white_space_checker(char *str, int start, int end);
char	*quotes_parser(char *str, int i, int *a);
int		separator_checker(t_info *data, char *str, int i, int j);
void	tokenizing(t_info *data, char *str);
void	ft_khrej(char *str, int nb);
void	free_double(char **str);
void	ft_free(t_info *data, t_cmd *command);
bool	char_checker(char c);
bool	is_single_quoted(char *str, int index, bool flag);
int		dolar_counter(char *str);
void	search_for_expand(t_lexer *ptr);
bool	char_checker(char c);
int		expander(t_info *data);
int		total_removal_quotes(char *str);
void	search_for_expand2(t_lexer *ptr, int *i, int *j, int *a);
void	skip_for_expaned(t_lexer *token, int j, int i, int a);
int		white_space_checker(char *str, int start, int end);
int		*save_index(char *str);
void	join_parsed_to_expanded(t_lexer *token, int dup_i, int dolar_i, int j);
void	skip_quotes(t_lexer *token);
void	search_for_expand2(t_lexer *ptr, int *i, int *j, int *a);
void	add_file(t_file **lst, t_file *new);
t_file	*new_file(char *content, t_token type);
void	add_cmd(t_cmd **lst, t_cmd *new);
t_cmd	*new_cmd(char **content);
void	find_file(t_lexer *token);
int		duplicate_2d(char **str, char **dup, int i);
int		syntax_error(t_info *data);
void	reform_list(t_info *data, t_cmd **command);
void	print_list(t_cmd *command);
int		ft_return(t_info *data, char *str, int nb);
int		size_ofdouble(char **str);
int		not_white_space(char *str, int i);
void	join_the_final(t_lexer *token, int dolar_nb);
void	helper2(t_lexer *token, int *dolar_i, int *dup_i);
void	helper(int *i, int dup_i, t_lexer *token);
int		dolar_counter(char *str);
void	search_for_expand(t_lexer *ptr);
void	masking_white_spaces(t_lexer *token);
void	convert_to_int(t_lexer *token, int size);
int		str_counter(t_lexer *token, int size);
int		arr_size(char **str);
int		check_for_masking(int *arr, int i);
void	find_heredoc(t_cmd *command);
char 	*get_env(char *key);
void    env_dup(void);

// builtins
void	excute_builtin(t_cmd *cmd_list);
int		arr2d_size(char **str);
void    update_env(char *pwd, char *newpwd);
void	my_env(void);
void	ft_echo(t_cmd *cmd);
bool    cd(t_cmd *cmd);
void    unset(t_cmd *cmd);
void    find_to_remove(char *str);
void    remove_and_switch(int i);
int		valide_keyname(char *str);
char	*key_name(char *str, int len);
char	*export_value(char *str);
void	export(t_cmd *cmd);
void    ft_print();
void	ft_exit(t_cmd *cmd);
void	ft_pwd(void);
void    env_dup(void);

// execution

int		execute_command(t_cmd *cmd);
char	*get_command_path(char *cmd);
bool	is_builtin(t_cmd *cmd_list);
void	exec(t_cmd *cmd);
int 	handle_pipes(t_cmd *cmd);
int 	handle_redirections(t_file *files);
void	excute_builtin(t_cmd *cmd_list);
void 	waiting(void);



#endif