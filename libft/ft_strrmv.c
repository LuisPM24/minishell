/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrmv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:16:00 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/28 09:18:33 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrmv(const char *src, const char *rmv)
{
	char	*pos;
	char	*new_str;
	size_t	len;

	if (!src || !rmv)
		return (NULL);
	pos = ft_strnstr(src, rmv, ft_strlen(src));
	if (!pos)
		return (ft_strdup(src));
	len = pos - src;
	new_str = malloc(len + ft_strlen(pos + ft_strlen(rmv)) + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, src, len + 1);
	ft_strlcat(new_str, pos + ft_strlen(rmv),
		len + ft_strlen(pos + ft_strlen(rmv)) + 1);
	return (new_str);
}
