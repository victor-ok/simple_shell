#include "shell.h"

/**
 * main - A function that runs our shell.
 * @ac: The number of inputed arguments.
 * @av: The pointer to array of inputed arguments.
 * @env: The pointer to array of enviromental variables.
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL, **command = NULL;
	size_t buff_size = 0;
	ssize_t char_read = 0;
	int rounds = 0;
	(void)ac;

	while (1)
	{
		rounds++;
		prompt();
		signal(SIGINT, handle);
		char_read = getline(&buffer, &buff_size, stdin);
		if (char_read == EOF)
		{
			_EOF(buffer);
		}
		else if (*buffer == '\n')
		{
			free(buffer);
		}
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			command = tokenize(buffer, " \0");
			free(buffer);
			if (_strcmp(command[0], "exit") != 0)
				shell_exit(command);
			else if (_strcmp(command[0], "cd") != 0)
				change_dir(command[1]);
			else
				create_child_process(command, av[0], env, rounds);
		}
		fflush(stdin);
		buffer = NULL;
		buff_size = 0;
	}
	if (char_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * prompt - prints the prompt
 *
 * Return: Nothing.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
	}
}

/**
 * handle - func to handle the Ctr + C signal.
 *
 * @signals: signal to be handled.
 *
 * Return: Nothing.
 */
void handle(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\ncisfun$ ", 10);
}

/**
 * _EOF -  checks for EOF in a buff
 *
 * @buffer: input string.
 *
 * Return: Nothing
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}

/**
 * shell_exit - func to exits the shell.]
 *
 * @command: tokenized command.
 *
 * Return: Nothing.
 */
void shell_exit(char **command)
{
	int stats = 0;

	if (command[1] == NULL)
	{
		mem_free(command);
		exit(EXIT_SUCCESS);
	}

	stats = _atoi(command[1]);
	mem_free(command);
	exit(stats);
}
