/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 01:42:23 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:34:16 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>
#include <stdlib.h>

char	**ft_strsplit(char const *s, char c)
{
	unsigned int	end;
	unsigned int	word;
	char			**words;

	if (!(words = (char**)malloc(sizeof(*words) * ((ft_strlen(s) / 2) + 2))))
		return (NULL);
	word = 0;
	while (*s)
	{
		end = 0;
		while (*s == c)
			s++;
		while (s[end] != c && s[end])
			end++;
		if (end)
			words[word++] = ft_strsub(s, 0, end);
		s += end;
	}
	words[word] = 0;
	return (words);
}
