#include "minishell.h"

char	*ft_copy_in_line(char *line, char *reminder)
{
	long int	i;
	long int	k;

	i = 0;
	k = 0;
	while (reminder[i] && reminder[i] != '\n')
	{
		if (reminder[i] == '\r')
			i++;
		else
			line[k++] = reminder[i++];
	}
	if (reminder[i] == '\n')
		line[k++] = '\n';
	line[k] = '\0';
	return (line);
}

char	*ft_find_line(char *reminder)
{
	char		*line;
	long int	i;
	long int	k;

	i = 0;
	k = 0;
	while (reminder[i] && reminder[i] != '\n')
	{
		if (reminder[i] == '\r')
			k++;
		i++;
	}
	if (reminder[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i - k + 1));
	if (!line)
		return (NULL);
	line = ft_copy_in_line(line, reminder);
	ft_new_reminder(reminder);
	return (line);
}

char	*ft_copy_from_read(char *line, char *reminder)
{
	char	*line_buffer;

	line_buffer = ft_find_line(reminder);
	if (!line_buffer)
	{
		free (line);
		return (NULL);
	}
	line = ft_strjoin(line, line_buffer);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_read_file(char *line, char *reminder, int fd)
{
	long int	r;

	if (!line)
	{
		line = (char *)malloc(sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	r = 1;
	while (r > 0 && !ft_strchr(line, '\n'))
	{
		r = read(fd, reminder, BUFFER_SIZE);
		if (r <= 0 && !ft_strlen(line))
		{
			free (line);
			return (NULL);
		}
		reminder[r] = '\0';
		line = ft_copy_from_read(line, reminder);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	line = NULL;
	if (reminder)
		line = ft_find_line(reminder);
	if (!reminder)
	{
		reminder = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!reminder)
			return (NULL);
	}
	line = ft_read_file(line, reminder, fd);
	if (!line)
	{
		reminder = ft_free_reminder(reminder);
		return (NULL);
	}
	if (!ft_strlen(reminder))
		reminder = ft_free_reminder(reminder);
	return (line);
}
