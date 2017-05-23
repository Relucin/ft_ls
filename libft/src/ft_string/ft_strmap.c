/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 23:46:25 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:37:39 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *ns;
	char *hold;

	if (!(ns = (char*)malloc(ft_strlen(s) + 1)))
		return (0);
	hold = ns;
	while (*s)
		*ns++ = f(*s++);
	*ns = '\0';
	return (hold);
}
