/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:43:14 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:39:36 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		loc;

	loc = 0;
	if (!(dup = (char*)malloc(sizeof(*dup) * (ft_strlen(s1) + 1))))
		return (NULL);
	while (*s1)
		dup[loc++] = *s1++;
	dup[loc] = '\0';
	return (dup);
}
