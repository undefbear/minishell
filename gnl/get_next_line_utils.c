/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:21:27 by kstout            #+#    #+#             */
/*   Updated: 2020/11/06 20:21:36 by kstout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

//static int	ft_strlen(char *str)
//{
//	int n;
//
//	n = 0;
//	while (*str != '\0')
//	{
//		n++;
//		str++;
//	}
//	return (n);
//}

//char		*ft_strdup(const char *s1)
//{
//	int		slen;
//	char	*d;
//	int		i;
//
//	i = 0;
//	slen = ft_strlen((char *)s1);
//	if (!(d = (char *)malloc(slen + 1)))
//		return (NULL);
//	else
//		while (slen)
//		{
//			d[i] = s1[i];
//			i++;
//			slen--;
//		}
//	d[i] = '\0';
//	return (&d[0]);
//}

//char		*ft_strjoin(char const *s1, char const *s2)
//{
//	char	*new;
//	int		s1len;
//	int		s2len;
//	int		i;
//
//	i = 0;
//	if ((!s1) || (!s2))
//		return (0);
//	s1len = ft_strlen((char *)s1);
//	s2len = ft_strlen((char *)s2);
//	if (!(new = (char *)malloc(s1len + s2len + 1)))
//		return (NULL);
//	while (s1len--)
//		new[i++] = *s1++;
//	while (s2len--)
//		new[i++] = *s2++;
//	new[i] = '\0';
//	return (new);
//}

char		*ft_strchr(const char *s, int c)
{
	char sb;

	sb = (char)c;
	while (*s)
	{
		if (*s == sb)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}
