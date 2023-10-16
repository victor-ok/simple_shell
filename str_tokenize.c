#include "shell.h"

/**
 * tokenize - func to split command string.
 *
 * @deli: delimiter for strtok.
 * @buffer: pointer to input string.
 *
 * Return: A string with full command.
 */
char **tokenize(char *buffer, const char *deli)
{
	char *token = NULL, **command = NULL;
	size_t buffsize = 0;
	int i = 0;

	if (buffer == NULL)
	{
		return (NULL);
	}
	buffsize = _strlen(buffer);
	command = malloc((buffsize + 1) * sizeof(char *));
	if (command == NULL)
	{
		perror("allocation failed");
		free(buffer);
		mem_free(command);
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, deli);
	while (token != NULL)
	{
		command[i] = malloc(_strlen(token) + 1);
		if (command[i] == NULL)
		{
			perror("allocation failed");
			mem_free(command);
			return (NULL);
		}
		_strcpy(command[i], token);
		token = strtok(NULL, deli);
		i++;
	}
	command[i] = NULL;
	return (command);
}
