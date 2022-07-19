#include "minishell.h"

t_list	*ft_found_in_envp(t_list *envp_list, char *key)
{
	t_list	*copy_envp;

	copy_envp = envp_list;
	while (copy_envp)
	{
		if (ft_strcmp(copy_envp->key, key) == 0)
			break ;
		copy_envp = copy_envp->next;
	}
	return (copy_envp);
}

int	ft_update_envp_old_pwd(t_list *envp_list, char *old_pwd)
{
	char	*buf;

	buf = ft_strjoin("OLDPWD=", old_pwd);
	if (!buf)
		return (1);
	if (ft_export_run(buf, envp_list, 0) != 0)
	{
		free (buf);
		return (1);
	}
	free (buf);
	return (0);
}

int	ft_free_envp_old_pwd(char *old_pwd)
{
	free (old_pwd);
	return (1);
}

int	ft_update_envp_pwd(t_list *envp_list)
{
	char	*buf;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	buf = ft_strjoin("PWD=", new_pwd);
	if (!buf)
	{
		free (new_pwd);
		return (1);
	}
	if (ft_export_run(buf, envp_list, 0) != 0)
	{
		free (buf);
		free (new_pwd);
		return (1);
	}
	free (buf);
	free (new_pwd);
	return (0);
}
