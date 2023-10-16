#include "shell.h"

/**
 * mem_free -function that frees all the memory allocated
 *
 * @command: pointer to allocated memory to free.
 *
 * Return: Nothing.
 */

void mem_free(char **command)
{
	size_t i = 0;

	if (command == NULL)
	{
		return;
	}
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	if (command[i] == NULL)
	{
		free(command[i]);
	}
	free(command);
}

/**
 * mem_free_exit - func to free all the memory allocated and exit.
 *
 * @command: The pointer to allocated command memory to free.
 *
 * Return: Nothing.
 */
void mem_free_exit(char **command)
{
	size_t i = 0;

	if (command == NULL)
	{
		return;
	}
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	if (command[i] == NULL)
	{
		free(command[i]);
	}
	free(command);
	exit(EXIT_FAILURE);
}
