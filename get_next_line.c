/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:53:20 by ybenchel          #+#    #+#             */
/*   Updated: 2024/11/19 13:54:08 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *store)
{
	char	*line;
	int		i;

	i = 0;
	if (!store[i])
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	line = ft_substr(store, 0, i);
	return (line);
}

static char	*ft_update_store(char *store)
{
	char	*new_store;
	int		i;
	int		j;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
	{
		free(store);
		return (NULL);
	}
	i++;
	new_store = malloc(ft_strlen(store) - i + 1);
	if (!new_store)
		return (NULL);
	j = 0;
	while (store[i])
		new_store[j++] = store[i++];
	new_store[j] = '\0';
	free(store);
	return (new_store);
}

static char	*ft_read_file(int fd, char *store)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(store, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(store);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		store = ft_strjoin(store, buffer);
	}
	free(buffer);
	return (store);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = ft_read_file(fd, store);
	if (!store)
		return (NULL);
	line = ft_get_line(store);
	store = ft_update_store(store);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line;
// 	while((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	// while((line = get_next_line(STDIN_FILENO)))
// 	// {
// 	// 	printf("this is the result of what you typed mu guy : %s", line);
// 	// 	free(line);
// 	// }
// }