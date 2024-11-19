/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:53:20 by ybenchel          #+#    #+#             */
/*   Updated: 2024/11/18 09:16:44 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*store[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	store[fd] = ft_read_file(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	line = ft_get_line(store[fd]);
	store[fd] = ft_update_store(store[fd]);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
//         int fd1 = open("test1.txt", O_RDONLY);
//         int fd2 = open("test2.txt", O_RDONLY);
//         char *line;

//         while ((line = get_next_line_bonus(fd1)))
//         {
//                 printf("%s", line);
//                 free(line);
//         }
//         close(fd1);
// 	printf("\n");
//         while ((line = get_next_line_bonus(fd2)))
//         {
//                 printf("%s", line);
//                 free(line);
//         }
//         close(fd2);
//         return (0);
// }