/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 23:58:08 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:46:22 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ftstring.h>

void	ft_putendl(char const *s)
{
	char n;

	n = '\n';
	write(1, &(*s), ft_strlen(s));
	write(1, &n, 1);
}
