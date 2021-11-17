/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraffin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 01:39:18 by lraffin           #+#    #+#             */
/*   Updated: 2021/11/17 02:39:10 by lraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE	32
# define INT_MAX		2147483647
# define INT_MIN		-214783648

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_abs(int n);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_atoi_base(char *str, const char *base);
long long	ft_atol(const char *str);
int			ft_atoi(const char *str);
int			ft_bzero(void *s);
void		*ft_calloc(int count, int size);
void		clean_free(char **str);
void		free_double_str(char **str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isflag(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
char		*ft_itoa(int n);
void		*ft_memccpy(void *dst, const void *src, int c, int n);
void		*ft_memchr(const void *s, int c, int n);
int			ft_memcmp(const void *s1, const void *s2, int n);
void		*ft_memcpy(void *dst, const void *src, int n);
void		*ft_memmove(void *dst, const void *src, int len);
void		*ft_memset(void *b, int c, int len);
int			ft_nbrlen_u(unsigned int n, int base_size);
int			ft_nbrlen_ul(unsigned long n, int base_size);
int			ft_nbrlen(long n, int base_size);
int			ft_put0xhexa_ret(unsigned long n, const char *base);
void		ft_putchar_fd(char c, int fd);
int			ft_putchar_ret(int c);
void		ft_putchar(char c);
void		ft_putendl_fd(char *s, int fd);
int			ft_puthexa_ret(unsigned int n, const char *base);
void		ft_putnbr_fd(int n, int fd);
int			ft_putnbr_u_ret(unsigned int n);
void		ft_putnbr_u(unsigned int n);
int			ft_putnbr_ret(int n);
void		ft_putnbr(int n);
void		ft_putstr_fd(char *s, int fd);
int			ft_putstr_n_ret(char *s, int n);
int			ft_putstr_ret(char *s);
void		ft_putstr(const char *s);
void		*ft_realloc(void *ptr, size_t size);
char		**ft_split_on_first(const char *s, char c);
char		**ft_split(const char *s, char c);
int			str_is_alnum(char *s);
int			str_is_digit(char *s);
int			str_is_equal(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_and_free(char *s1, char *s2);
int			ft_strlcat(char *dst, const char *src, int dstsize);
int			ft_strlcpy(char *dst, const char *src, int dstsize);
int			ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strnstr(const char *haystack, const char *needle, int len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(const char *s, int start, int len);
void		ft_swap(int *a, int *b);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			get_next_line(int fd, char **line);

#endif
