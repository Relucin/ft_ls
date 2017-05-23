/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 01:00:15 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:39:08 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	t;
	char			*ns;

	if (!(ns = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	t = 0;
	while (*s1)
		ns[t++] = *s1++;
	while (*s2)
		ns[t++] = *s2++;
	ns[t] = '\0';
	return (ns);
}
