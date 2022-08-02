/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:58:46 by etisha            #+#    #+#             */
/*   Updated: 2022/07/28 15:04:39 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define OTHER_ERROR 0
# define SYNTAX_ERROR 1
# define COMMAND_NOT_FOUND 2
# define SYNTAX_PIPE_ERROR 3
# define HOME_NOT_SET 4
# define NO_SUCH_FILE_OR_DIR 5
# define OLDPWD_NOT_SET 6
# define FILE_NAME_TOO_LONG 7
# define SYNTAX_REDIR_ERROR 8
# define PERMISSION_DENIED 9
# define IS_A_DIRECTORY 10
# define FILE_IS_BUSY 11
# define ONLY_READ 12
# define NOT_A_DIRECTORY 13
# define SYNTAX_TOKEN_ERROR 14

extern int	g_last_exit;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_lexer
{
	char			*chank;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_shell
{
	t_list			*envp_list;
	char			**envp;
	char			*input;
	char			**comand;
	t_lexer			*lexer;
	struct termios	new_settings;
	struct termios	default_settings;
	int				fd1[2];
	int				fd2[2];
	pid_t			children;
}	t_shell;

/* INIT BLOCK */
void		ft_new_term_settings(t_shell *mini);
void		ft_default_term(t_shell *mini);
void		ft_init(t_shell	*mini, char **env);
void		ft_init_envp_list(t_list **envp_list, char **env);
void		ft_save_envp_on_list(t_list **list, char *env);
void		ft_free_memory_envp_list(t_list **envp_list);
char		**ft_new_envp(t_list **envp_list);
void		ft_free_memory_matrix(char **matrix);

/* PARSER */
void		ft_lexer(t_lexer **lexer, char	*input);
void		ft_free_memory_lexer_list(t_lexer **lexer);
void		ft_create_lexer(t_lexer **lexer, char *input, int start, int stop);
void		ft_lexer_word(t_lexer **lexer, char *input, int *start, int *stop);
void		ft_lexer_spase(t_lexer **lexer, char *input, int *start, int *stop);
void		ft_lexer_delim(t_lexer **lexer, char *input, int *start, int *stop);
void		lex_s_quotes(t_lexer **lexer, char *input, int *start, int *stop);
void		lex_d_quotes(t_lexer **lexer, char *input, int *start, int *stop);
void		lex_run_space(t_lexer **lexer, char *input, int *start, int *stop);
void		lexer_redir(t_lexer **lexer, char *input, int *start, int *stop);
int			ft_parser(t_shell *mini);
int			ft_exam_pipe_first_last_double(t_shell *mini);
int			ft_exam_syntax_quotes(t_shell *mini);
int			ft_exam_double_redirect(t_shell *mini);
void		ft_print_token_error(char *str, int exeption);
int			ft_exam_last_redirect(t_shell *mini);
void		ft_print_parser_error(t_lexer **lexer, int exeption);
void		ft_parser_create(t_lexer **new);
int			ft_save_or_skip(t_lexer *new, t_lexer *old, int i);
int			ft_save_char(t_lexer *new, char c);
int			ft_take_envp(t_lexer *new, t_lexer *old, int i, t_list *envp);
int			pars_save(t_lexer *new_copy, t_lexer *old_copy, t_list *envp_list);

/* EXECUTION */
void		ft_execution(t_shell *mini);
void		ft_close_fd(t_shell *mini, int i);
void		ft_error_fork(t_shell *mini, int i);
int			ft_found_redirect_in_command(t_lexer *lexer);
void		ft_exit_with_redir(t_shell *mini, t_lexer *copy, int count, int i);
int			found_heredoc(t_lexer *lexer);
int			ft_found_command_with_pipe(t_lexer *lexer);
int			ft_echo(t_lexer *lexer);
int			ft_cd(t_lexer *lexer, t_shell *mini);
int			ft_cd_error(int exeption, char *str);
t_list		*ft_found_in_envp(t_list *envp_list, char *key);
int			ft_update_envp_old_pwd(t_list *envp_list, char *old_pwd);
int			ft_free_envp_old_pwd(char *old_pwd);
int			ft_update_envp_pwd(t_list *envp_list);
int			ft_pwd(void);
int			ft_env(t_list *envp_list);
int			ft_export(t_lexer *lexer, t_list *envp_list);
int			ft_export_run(char *str, t_list *envp_list, int len);
int			ft_exam_void(t_lexer *lexer, t_list *envp_list);
int			ft_exam_export_key(char *str, char *key);
int			ft_print_export_error(char *str);
int			ft_unset(t_lexer *lexer, t_list **envp_list);
int			ft_print_unset_error(char *str);
int			ft_exit(t_shell *mini, t_lexer *lexer);
void		ft_children_run(t_shell *mini, t_lexer *lexer, int i, int count);
int			ft_found_in_castom(t_shell *mini, t_lexer *lexer);
void		ft_work_with_fd(t_shell *mini, int i, int count);
void		ft_work_with_fd_last_command(t_shell *mini, int i, int count);
void		ft_redirect(t_shell *mini, t_lexer *lexer, int i, int count);
int			ft_redirect_error(t_lexer **lexer, int exeption);
void		ft_run_redirect(t_shell *mini, t_lexer *lexer, int *fd);
int			ft_redirect_out_file2(t_lexer *lexer, t_lexer *now);
int			ft_open_heredoc(t_lexer *lexer, int flag);
void		ft_run_from_path(t_shell *mini, t_lexer *copy);
char		**ft_create_argv(t_shell *mini, t_lexer *copy);
char		**ft_return_space(char **matrix);
void		ft_error_exec(t_shell *mini, int exeption, char *str, char **argv);
void		ft_error_stat(t_shell *mini, int exeption, char *str, char **argv);

/* OTHER */
void		ft_signal(int sig);
void		ft_exit_signal(t_shell *mini);
void		rl_replace_line(const char *text, int clear_undo);

/* libft */
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
void		ft_free_memory_split(char **matrix, int x);
size_t		ft_strlen_value(const char *s);
size_t		ft_strlen_key(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strcmp_echo(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
int			ft_atoi(const char *str);
long long	ft_atoi_long(const char *str);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_isalpha(int c);
int			ft_isdigit(int c);

#endif
