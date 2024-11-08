
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if(!s || !s[i])
		return(0);
	while (s[i])
		i++;
	return (i);
}
