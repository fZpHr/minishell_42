/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:52:28 by hbelle            #+#    #+#             */
/*   Updated: 2023/09/27 13:58:28 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	boucle(int *i, int *j, char *str, char *to_find)
{
	int	l;
	int	m;

	l = *i;
	m = *j;
	while (str[l] == to_find[m] && to_find[m] != '\0')
	{
		l++;
		m++;
	}
	*i = l;
	*j = m;
}

char	*finito(char *str, int i, int j)
{
	j--;
	i--;
	while (j != 0)
	{
		i--;
		j--;
	}
	return (str + i);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;
	int	t;

	t = 0;
	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		t = i;
		if (str[i] == to_find[j] && to_find[j] != '\0')
		{
			boucle(&i, &j, str, to_find);
			if (to_find[j] == '\0')
				return (finito(str, i, j));
			i = t;
		}
		i++;
	}
	return (0);
}
