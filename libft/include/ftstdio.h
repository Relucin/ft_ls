/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftstdio.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:25:40 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 23:09:50 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSTDIO_H
# define FTSTDIO_H
# include <stdarg.h>

void	ft_putchar(char c);
int		ft_printf(const char *format, ...);
int		ft_vprintf(const char *format, va_list ap);
int		ft_asprintf(char **ret, const char *format, ...);
int		ft_vasprintf(char **ret, const char *format, va_list ap);
int		ft_dprintf(int fd, const char *format, ...);
/*
** extra
** Things in libft that are not in stdio.h
*/
void	ft_putstr(char const *c);
void	ft_putendl(char const *c);
void	ft_putnbr(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *c, int fd);
void	ft_putendl_fd(char const *c, int fd);
void	ft_putnbr_fd(int c, int fd);
#endif
