/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:13:04 by joerober          #+#    #+#             */
/*   Updated: 2023/03/23 16:07:26 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next(char *tracker)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (tracker[i] != '\0' && tracker[i] != '\n')
		i++;
	if (!tracker[i])
	{
		free(tracker);
		return (NULL);
	}
	line = ft_calloc_gnl((ft_strlen_gnl(tracker) - i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i++;
	while (tracker[i])
		line[j++] = tracker [i++];
	line[j] = '\0';
	free(tracker);
	return (line);
}

char	*ft_get_line(char *tracker)
{
	char	*line;
	int		i;

	i = 0;
	if (!tracker[i])
		return (NULL);
	while (tracker[i] != '\0' && tracker[i] != '\n')
		i++;
	line = ft_calloc_gnl(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (tracker[i] != '\0' && tracker[i] != '\n')
	{
		line[i] = tracker[i];
		i++;
	}
	if (tracker[i] && tracker[i] == '\n')
	{
		line[i] = tracker[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *tracker)
{
	char	*buff;
	int		bytes_read;

	if (!tracker)
		tracker = ft_calloc(1, 1);
	buff = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(tracker, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		tracker = ft_strjoin_gnl(tracker, buff);
	}
	free (buff);
	return (tracker);
}

char	*get_next_line(int fd)
{
	static char	*tracker;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (0);
	tracker = ft_read(fd, tracker);
	if (!tracker)
		return (NULL);
	line = ft_get_line(tracker);
	tracker = ft_next(tracker);
	return (line);
}

/*
#include <fcntl.h>

int main()
{
	int		fd;
	int		i;
	char	*line;

	i = 1;
	fd = open("test.txt", O_RDONLY);
	while (i < 4)
	{
		line = get_next_line(fd);
		printf("line[%i]: %s", i, line);
		free (line);
		i++;
	}
	close(fd);
}
*/
