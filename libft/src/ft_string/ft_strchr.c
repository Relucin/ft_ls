/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 19:36:42 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:40:08 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char cc;

	cc = (char)c;
	while (*s)
		if (*s++ == cc)
			return ((char*)--s);
	if (*s == cc)
		return ((char*)s);
	else
		return (NULL);
}
