#include "minishell.h"

void	ft_print_parser_error(t_lexer **lexer, int exeption)
{
	t_lexer	*copy;

	copy = *lexer;
	if (exeption == SYNTAX_ERROR)
	{
		write(2, "minishell: syntax error\n", 24);
	}
	else if (exeption == COMMAND_NOT_FOUND)
	{
		write(2, "minishell: ", 11);
		write(2, copy->chank, ft_strlen(copy->chank));
		write(2, ": command not found\n", 20);
	}
	else if (exeption == SYNTAX_PIPE_ERROR)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	else if (exeption == NO_SUCH_FILE_OR_DIR)
	{
		write(2, "minishell: ", 11);
		write(2, copy->chank, ft_strlen(copy->chank));
		write(2, ": No such file or directory\n", 29);
	}
	else if (exeption == SYNTAX_REDIR_ERROR)
		write(2, "minishell: syntax error near unexpected token `newline'\n", \
		56);
}

int	ft_print_export_error(char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	ft_print_unset_error(char *str)
{
	write(2, "minishell: unset: `", 19);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	ft_cd_error(int exeption, char *str)
{
	if (exeption == HOME_NOT_SET)
		write(2, "minishell: cd: HOME not set\n", 28);
	else if (exeption == NO_SUCH_FILE_OR_DIR)
	{
		write(2, "minishell: cd: ", 15);
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 29);
	}
	else if (exeption == OLDPWD_NOT_SET)
		write(2, "minishell: cd: OLDPWD not set\n", 30);
	else if (exeption == FILE_NAME_TOO_LONG)
	{
		write(2, "minishell: cd: ", 15);
		write(2, str, ft_strlen(str));
		write(2, ": File name too long\n", 21);
	}
	else if (exeption == PERMISSION_DENIED)
	{
		write(2, "minishell: cd: ", 15);
		write(2, str, ft_strlen(str));
		write(2, ": Permission denied\n", 21);
	}
	g_last_exit = 1;
	return (1);
}

int	ft_redirect_error(t_lexer **lexer, int exeption)
{
	t_lexer	*copy;

	copy = *lexer;
	write(2, "minishell: ", 12);
	write(2, copy->chank, ft_strlen(copy->chank));
	if (exeption == IS_A_DIRECTORY)
		write(2, ": Is a directory\n", 17);
	else if (exeption == PERMISSION_DENIED)
		write(2, ": Permission denied\n", 20);
	else if (exeption == NO_SUCH_FILE_OR_DIR)
		write(2, ": No such file or directory\n", 28);
	else if (exeption == FILE_IS_BUSY)
		write(2, ": File is busy\n", 15);
	else
		write(2, ": error open file!\n", 19);
	return (1);
}
