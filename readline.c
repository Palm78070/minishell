#include "minishell.h"

char	*rl_get()
{
	static char	*line;

	line = NULL;
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	line = readline("Enter command: ");
	if (line != NULL && *line)
		add_history(line);
	return (line);
}
