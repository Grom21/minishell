#include "minishell.h"

int	ft_echo(t_lexer *lexer, t_list *envp_list)
{
	t_lexer	*copy;
	int		flag_n;

	flag_n = 0;
	copy = lexer->next;
	if (copy && ft_strcmp(copy->chank, "-n") == 0)
	{
		flag_n = 1;
		copy = copy->next;
	}
	if (copy)
		ft_putstr_fd(copy->chank, 1);
	if (flag_n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
