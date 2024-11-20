/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:31:20 by claghrab          #+#    #+#             */
/*   Updated: 2024/11/18 16:31:24 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char *buffer;
	static char *dup;
	char *line;
	size_t nl;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (dup)
	{
		nl = tonl(dup, '\n');
		if (nl)
			return (ft_substr(dup, 0, len(dup, '\n')));
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	int count = 0;
	nl = 0;
	while (!nl)
	{
		count = count + 1;
		printf("%d\n", count);
		ssize_t i = read(fd, buffer, BUFFER_SIZE);
		if (i == 0)
			return (NULL);
		nl = tonl(buffer, '\n');
		if (nl)
		{
			if (buffer + nl + 1 != '\0')
			{
				line = ft_strjoin(dup, ft_substr(buffer, 0, len(buffer, '\n')));
				dup = ft_substr(buffer, nl + 1, BUFFER_SIZE - (nl + 1));
				return (line);
			}
			else
				return (ft_strjoin(dup, buffer));
		}
		dup = ft_strjoin(dup, buffer);
	}
	return (NULL);
}



size_t	tonl(char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

size_t	nl_func(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub_len = ft_strlen(s + start);
	if (len > sub_len)
		len = sub_len;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = 0;
	return (new);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*new;

	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

size_t	len(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(void)
{
	int		fd;
	char	*buffer;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("open failed\n");
		return (0);
	}
	while ((buffer = get_next_line(fd)) != 0)
	{
		printf("%s\n", buffer);
		free(buffer);
	}
	// if (!buffer)
	// {
	//     printf("allocation failed\n");
	//     return (0);
	// }
	// ssize_t read_value = read(fd, buffer, BUFFER_SIZE);
	// if (read_value > 0)
	//     printf("%s\n", buffer);
	// else if (read_value == 0)
	// {
	//     printf("EOF\n");
	//     printf("%d\n", EOF);
	// }
	// else
	//     printf("error reading file");
	// free(buffer);
	close(fd);
}
