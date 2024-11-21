#include "get_next_line.h"

char *leftover(char *str, int nl)
{
    int i;
    char *new;

    if (!str)
        return (NULL);
    i = 0;
    while (str[nl + i])
        i++;
    new = malloc(sizeof(char) * (i + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (str[nl + i])
    {
        new[i] = str[nl + i];
        i++;
    }
    return (new);
}
char *append_to_nl(char *str, char **line)
{
    int i;
    char *new;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    new = malloc(sizeof(char) * (i + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        new[i] = str[i];
        i++;
    }
    return (new);
}


char *dup(char *str)
{
    size_t i;
    char *new;

    if (!str)
        return (NULL);
    new = malloc(sizeof(char) * (ft_strlen(str) + 1));
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

char	*join(char *s1, char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1)
		return (dup(s2));
	if (!s2)
		return (dup(s1));
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
    {
        free(s1);
        return (NULL);
    }
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i] && i < len)
		new[j++] = s2[i++];
	new[j] = 0;
    free(s1);
	return (new);
}

int tonl(char *s, char c)
{
    int i;

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

char	*get_next_line(int fd)
{
    static char	*last;
    char *buffer;
    char *line;
    ssize_t i;
    int nl;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    if (last)
    {
        line = dup(last);
        free(last);
    }
    nl = -1;
    while (nl == -1)
    {
        i = read(fd, buffer, BUFFER_SIZE);
        if (i == -1 || i == 0)
        {
            free(buffer);
            return (NULL);
        }
        buffer[i] = '\0';
        nl = tonl(buffer, '\n');
        if (nl != -1)
        {
            line = malloc(sizeof(char) * (nl + 1));
            if (!line)
            {
                free(buffer);
                return (NULL);
            }
            last = malloc(sizeof(char) * (i - nl));
            if (!last)
            {
                free(buffer);
                free(line);
                return (NULL);
            }
            if(buffer[nl + 1] != '\0')
            {
                if (last)
                    last = join(last, buffer + nl + 1, ft_strlen(buffer + nl + 1));
                else
                    last = dup(buffer + nl + 1);
                line = join(line, buffer, nl + 1);
                free(buffer);
                return (line);
            }
            if (buffer[nl + 1] == '\0')
            {
                line = join(line, buffer, ft_strlen(buffer));
                free(buffer);
                return (line);
            }
        }
        if (nl == -1)
        {
            line = dup(buffer);
            free(buffer);
        }
    }
}
