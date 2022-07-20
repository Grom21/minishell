#include "minishell.h"

int	ft_echo(t_lexer *lexer, t_list *envp_list)
{
	t_lexer	*copy;
	int		flag_n;
	int		i;

	flag_n = 0;
	copy = lexer->next;
	i = 0;
	if (copy && copy->chank[0] == '-' && copy->chank[1] == 'n' \
	&& (copy->chank[2] == ' ' || copy->chank[2] == '\0'))
	{
		flag_n = 1;
		if (copy->chank[2] == ' ')
			i = 3;
		else
			i = 2;
	}
	while (copy && copy->chank[i] && copy->chank[0] != '<' \
	&& copy->chank[0] != '>')
		ft_putchar_fd(copy->chank[i++], 1);
	if (flag_n == 0)
		ft_putchar_fd('\n', 1);
	g_last_exit = 0;
	return (0);
}
