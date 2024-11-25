/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:34:10 by claghrab          #+#    #+#             */
/*   Updated: 2024/11/25 13:34:25 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# ifndef FD_SETSIZE
#  define FD_SETSIZE 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*append_line(char *last);
char	*append_last(char *last);
char	*mini_read(int fd, char *last);
char	*handle_read(char *buffer, char *last, ssize_t read_bytes);
char	*join(char *s1, char *s2);
char	*dupl(char *str);
int		ft_strlen(char *str);
int		tonl(char *s, char c);

#endif
