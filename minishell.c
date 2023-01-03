#include "minishell.h"

int	is_exit(char *s)
{
	return (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't');
}

int	main(void)
{
	char	*line;

	line = "";
	while (line != NULL && !is_exit(line))
	{
		line = rl_get();
		printf("%s\n", line);
	}
	free(line);
	return (0);
}
