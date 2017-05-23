/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 23:58:08 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:46:36 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ftstring.h>

void	ft_putendl_fd(char const *s, int fd)
{
	char n;

	n = '\n';
	write(fd, &(*s), ft_strlen(s));
	write(fd, &n, 1);
}
