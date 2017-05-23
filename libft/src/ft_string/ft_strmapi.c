/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 23:46:25 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:37:13 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ns;

	if (!(ns = (char*)malloc(ft_strlen(s) + 1)))
		return (0);
	i = 0;
	while (*s)
	{
		ns[i] = f(i, *s++);
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
