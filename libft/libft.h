/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 09:42:52 by egeant            #+#    #+#             */
/*   Updated: 2020/06/02 11:06:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int value, size_t len);
void	ft_bzero(void *str, size_t len);
void	*ft_memcpy(void *dst, void const *src, size_t size);
void	*ft_memccpy(void *dst, void const *src, int c, size_t len);
void	*ft_memmove(void *dst, void const *src, size_t size);
void	*ft_memchr(void const *str, int c, size_t size);
int		ft_memcmp(void const *str1, void const *str2, size_t size);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(char const *str, int c);
char	*ft_strrchr(char const *str, int c);
int		ft_strncmp(char const *str1, char const *str2, size_t n);
size_t	ft_strlcpy(char *dst, char const *src, size_t size);
size_t	ft_strlcat(char *dst, char const *src, size_t size);
char	*ft_strnstr(char const *haystack, char const *needle, size_t len);
int		ft_atoi(char const *str);
void	*ft_calloc(size_t len, size_t size);
char	*ft_strdup(char const *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char const *str);
char	*ft_strchr(char const *str, int c);
char	*ft_strjoinfree(char *s1, char const *s2);

#endif
