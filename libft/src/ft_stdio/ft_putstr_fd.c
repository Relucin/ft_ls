/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 23:49:57 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:45:32 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ftstring.h>

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, &(*s), ft_strlen(s));
}
