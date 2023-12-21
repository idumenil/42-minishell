/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatdiall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:46:38 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/20 16:46:41 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <fcntl.h>
# include <errno.h>

// # ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

# define NC			"\e[0m"
# define YELLOW		"\e[1;33m"
# define BLUE		"\e[1;34m"
# define RED		"\e[1;91m"

typedef struct s_data
{
	int		err;
	int		exit;
	char	**orig_env;
	char	*cmd_line;
	char	**cmd_parsed;
	char	*prompt;
	char	**copy_env;
	char	***args_arr;
	int		cmd_ret;
	int		exit_status;
	char	**redirection_file;
	char	*type_redir;
	int		saved_fd_in;
	int		saved_fd_out;
	int		file_redir_in;
	int		file_redir_out;
	int		here_doc_exists;
	char	*pwd;
}				t_data;

typedef struct s_parse
{
	int	start;
	int	end;
	int	i;
	int	j;
}				t_parse;

// redirect.c
int			redirection(char *type_red, char *file_name, t_data *datas, int fd);

// my_execve.c
void		do_redir_parent(int fd[2], int haspipe);
void		do_redir_child(int fd[2], int haspipe, int file_redir);
int			my_execve(char **args, t_data *datas, int haspipe);

// my_export
void		my_export(char **args, t_data *datas);
int			name_is_valid(char **args, int i);
void		export_helper(t_data *datas, char *str);

// my_unset
void		my_unset(char **args, t_data *datas);

// init.c
void		init_vars(char **env, t_data *datas);
void		make_prompt(t_data *datas);

//builtin_launcher.c
void		prt_env(char **args, int declarex);
int			look_for_builtin(char **args, t_data *datas, int haspipe);
char		*search_path(char **args, t_data *datas);
// builtin_echo.c
void		builtin_echo(char **args);
// builtin_cd.c
void		builtin_cd(char **args, t_data *datas);
// builtin_pwd.c
int			builtin_pwd(t_data *datas);

// env_utils.c
char		*get_env_var(char *var_name, char **env);
int			get_env_var_line(char *var_name, char **env);
char		**copy_env_var(char **env);
int			nb_lines_arr(char **array);

// libft_utils_1.c
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// libft_utils_2.c
char		**ft_split(const char *s, char c);

// libft_utils_3.c
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strjoin_with_slash(char const *s1, char const *s2);

// libft_utils_4.c
char		*ft_strcpy(char *dest, char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_strldup(const char *s, size_t len);

// libft_utils_5.c
char		*ft_itoa(int n);
int			ft_atoi(const char *str);

// free_utils.c
void		free_2d_char(char **arr);

// exit
void		exit_minishell(t_data *datas);
void		handlerctrlc(int num);

// **** PARSING ****
// parsing_main.c
int			parse(char *cmd_line, t_data *datas);
void		clear_data_args_arr(t_data *datas);
// parsing_quotes.c
char		**analyse_quotes(char **args, char *str);
int			check_quotes_closing(char *str);
void		remove_quotes(t_data *datas);
// parsing_env_vars.c
char		**replace_vars(char **args, t_data *datas);
// parsing_is_char.c
int			is_alpha_num(char c);
int			is_split_char(char c);
int			is_spaces(char c);
int			is_only_spaces(char *str);
int			is_only_quotes(char *str);
// parsing_arrays_utils.c
char		**add_str_part_to_arr(char **args, char *str, int start, int end);
char		**add_str_arr_pos(char **arr, int pos, char *str);
char		**rm_arr_line(char **args, int pos);
// parsing_str_utils.c
char		**trim_all_str(char **args);
char		*ft_reduce_multiple_spaces(char *str);
// parsing_join_quotes.c
char		**check_elements_to_join(char **args);
char		**rm_empty_elements(char **args);
// parsing_splits.c
char		**split_cmds(char **args);
char		**split_spaces(char **args);
// parsing_output.c
void		create_output(char **args, t_data *datas);

// get next line
char		*get_next_line(int fd);

int			is_alpha(char c);

int			is_redirect(t_data *datas);

// main_tools.c
void		prt_args(t_data *datas);
int			check_redir(char **cmd_line, t_data *datas);
void		reset_redirs(t_data *datas);

#endif
