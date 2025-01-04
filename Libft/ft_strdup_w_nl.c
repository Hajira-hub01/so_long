#include "libft.h"

char	*ft_strdup_w_nl(char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	free(s);
	str[i] = '\0';
	return (str);
}
