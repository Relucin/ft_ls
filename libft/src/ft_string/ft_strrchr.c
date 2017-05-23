/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 20:07:15 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:35:00 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	l;
	char			cc;

	i = 0;
	l = 0;
	cc = (char)c;
	while (s[i])
		if (s[i++] == cc)
			l = i - 1;
	if (s[i] == cc)
		return ((char*)(s + i));
	else if (s[l] == cc)
		return ((char*)(s + l));
	return (NULL);
}
