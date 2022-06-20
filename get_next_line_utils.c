#include "minishell.h"

void	ft_new_reminder(char *reminder)
{
	long int	i;
	long int	k;

	i = 0;
	while (reminder[i] && reminder[i] != '\n')
		i++;
	if (reminder[i] == '\n')
		i++;
	k = 0;
	while (i < BUFFER_SIZE)
		reminder[k++] = reminder[i++];
	while (k <= BUFFER_SIZE)
		reminder[k++] = '\0';
}

char	*ft_free_reminder(char *reminder)
{
	free (reminder);
	reminder = NULL;
	return (reminder);
}

char	*ft_strchr(const char *s, int c)
{
	long int	i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i] != '\0')
		i++;
	if (s[i] == '\0' && c != '\0')
		return (NULL);
	else
		return ((char *)s + i);
}

char	*ft_strjoin(char *line, char *line_buffer)
{
	size_t	len;
	char	*join;
	size_t	i;
	size_t	k;

	if (!line || !line_buffer)
		return (NULL);
	len = ft_strlen(line) + ft_strlen(line_buffer);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (join == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (line[k])
		join[i++] = line[k++];
	k = 0;
	while (line_buffer[k])
		join[i++] = line_buffer[k++];
	join[i] = '\0';
	free (line);
	free (line_buffer);
	return (join);
}
