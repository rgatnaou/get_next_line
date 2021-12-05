/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:58:11 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/12/05 13:14:56 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line_read(int fd, char *rest)
{
	char	*tmp;
	int		r_read;

	r_read = -1;
	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (!ft_strchr(rest, '\n') && r_read)
	{
		r_read = read(fd, tmp, BUFFER_SIZE);
		if (r_read == -1)
		{
			free (tmp);
			tmp = NULL;
			return (NULL);
		}
		tmp[r_read] = '\0';
		rest = ft_strjoin(rest, tmp);
	}
	free (tmp);
	tmp = NULL;
	return (rest);
}

char	*get_line(char *rest)
{
	char	*rtn;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	rtn = malloc (i + 1);
	if (!rtn)
		return (NULL);
	while (i)
	{
		rtn[j] = rest[j];
		j++;
		i--;
	}
	rtn[j] = '\0';
	return (rtn);
}

char	*update_rest(char *rest)
{
	char	*rtn;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\0')
	{
		free(rest);
		return (NULL);
	}
	i++;
	rtn = malloc (ft_strlen(rest) - i + 1);
	while (rest[i])
	{
		rtn[j] = rest[i];
		i++;
		j++;
	}
	rtn[j] = '\0';
	free(rest);
	return (rtn);
}

char	*get_next_line(int fd)
{
	static char	*rest[256];
	char		*r_read;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	rest[fd] = get_next_line_read(fd, rest[fd]);
	if (!rest[fd])
		return (NULL);
	r_read = get_line(rest[fd]);
	rest[fd] = update_rest(rest[fd]);
	return (r_read);
}
