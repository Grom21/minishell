#include "minishell.h"

void	ft_new_term_settings(t_shell *mini)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &mini->default_settings);
	tcgetattr(STDIN_FILENO, &mini->new_settings);
	mini->new_settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &mini->new_settings))
	{
		write (2, "error: unable to change terminal settings\n", 42);
		exit (1);
	}
}

void	ft_default_term(t_shell *mini)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &mini->default_settings);
}
