#include "../include/shell.h"

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp_s;

	tmp_s = (unsigned char *)s;
	while (n--)
		*(tmp_s++) = 0;
}

long long int	ft_atoi(const char *str)
{
	char			*tmp_str;
	size_t			i;
	long long int	res;
	long long int	minus;

	minus = 1;
	res = 0;
	tmp_str = (char *)str;
	i = 0;
	while (tmp_str[i] == ' ' || tmp_str[i] == '\t' || tmp_str[i] == '\n'
		|| tmp_str[i] == '\v' || tmp_str[i] == '\f' || tmp_str[i] == '\r')
		i++;
	if (tmp_str[i] == '-' || tmp_str[i] == '+')
		if (tmp_str[i++] == '-')
			minus = -1;
	while (tmp_str[i] >= '0' && tmp_str[i] <= '9')
	{
		res = res * 10 + (tmp_str[i] - '0');
		i++;
	}
	return (minus * res);
}

int	ft_isprint(unsigned char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

int	arr_size(char **strs)
{
	int	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}
