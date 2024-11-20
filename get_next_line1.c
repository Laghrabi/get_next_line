/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:44:25 by claghrab          #+#    #+#             */
/*   Updated: 2024/11/20 17:44:28 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	sub_len = ft_strlen(s + start);
	if (len > sub_len)
		len = sub_len;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	free(s);
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
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
	free(s1);
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
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	tonl(char *s, char c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char    *append_to_buff(char *str, t_buff *buff)
{
    int i;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i] && buff->idx < 1023 && str[i] != '\n')
			buff->buffer[(buff->idx)++] = str[i++];
			//append to line if the buffer is full
	if (i == 1023)
	{
		buff->buffer[buff->idx] = '\0';
		return (buff->buffer);
	}
	if (str[i] == '\n')
	{
		buff->buffer[(buff->idx)++] = str[i++];
    	buff->buffer[buff->idx] = '\0';
		return (buff->buffer);
	}
	return (NULL);
}

char	*get_next_line1(int fd)
{
	static char	*last;
	char		tmp[BUFFER_SIZE + 1];
	char		*line = NULL;
	t_buff		buff;
	ssize_t		i;

	i = 1;
	buff.idx = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (last)
	{
		line = append_to_buff(last, &buff);
		if (tonl(last, '\n') != -1)
		{
			last = ft_substr(last, tonl(last, '\n') + 1, BUFFER_SIZE);
			return (line);
		}
	}
	if (!last)
	{
		while (i > 0)
		{
			i = read(fd, tmp, BUFFER_SIZE);
			tmp[i] = '\0';
			line = ft_strjoin(line, append_to_buff(tmp, &buff));
			if (tonl(tmp, '\n'))
			{
				last = ft_substr(tmp, tonl(tmp, '\n') + 1, BUFFER_SIZE);
				return (line);
			}
			else
				return (line);

		}
		// append_to_buff(tmp, &buff);
	}
	return (NULL);
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
	while ((buffer = get_next_line1(fd)) != 0)
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