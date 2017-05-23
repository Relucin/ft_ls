/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:45:53 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:36:53 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int i;
	unsigned int i2;

	i = ft_strlen(s2);
	i2 = (n < i) ? n : i;
	i = ft_strlen(s1);
	(void)ft_strncpy(s1 + i, s2, i2);
	s1[i + i2] = '\0';
	return (s1);
}
