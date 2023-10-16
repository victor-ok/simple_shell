#include "shell.h"

/**
 * exe - func to execute a command.
 *
 * @command: pointer to tokienized command
 * @name: name of the shell.
 * @env: pointer to the enviromental variables.
 * @rounds: counter of the executed rounds.
 *
 * Return: Nothing.
 */
void exe(char **command, char *name, char **env, int rounds)
{
	char **pth = NULL;
	char  *full_pth = NULL;
	struct stat st;
	unsigned int i = 0;

	if (_strcmp(command[0], "env") != 0)
	{
		print_env(env);
	}
	if (stat(command[0], &st) == 0)
	{
		if (execve(command[0], command, env) < 0)
		{
			perror(name);
			mem_free_exit(command);
		}
	}
	else
	{
		pth = _getpth(env);
		while (pth[i])
		{
			full_pth = _strcat(pth[i], command[0]);
			i++;
			if (stat(full_pth, &st) == 0)
			{
				if (execve(full_pth, command, env) < 0)
				{
					perror(name);
					mem_free(pth);
					mem_free_exit(command);
				}
				return;
			}
		}
		msg_error(name, rounds, command);
		mem_free(pth);
	}
}


/**
 * print_env - func to print all enviromental variables.
 *
 * @env: The pointer to enviromental variables.
 *
 * Return: Nothing.
 */
void print_env(char **env)
{
	size_t i = 0, len = 0;

	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}


/**
 * _getpth - func to gets the full value of env var
 *
 * @env: pointer to enviromental variables.
 *
 * Return: available pathways.
 */
char **_getpth(char **env)
{
	char *pth_value = NULL;
	char **pth_way = NULL;
	unsigned int i = 0;

	pth_value = strtok(env[i], "=");
	while (env[i])
	{
		if (_strcmp(pth_value, "PATH"))
		{
			pth_value = strtok(NULL, "\n");
			pth_way = tokenize(pth_value, ":");
			return (pth_way);
		}
		i++;
		pth_value = strtok(env[i], "=");
	}
	return (NULL);
}


/**
 * msg_error - func to print message not found.
 *
 * @name: shell name.
 * @rounds: cycle count.
 * @command: pointer to command.
 *
 * Return: Nothing.
 */
void msg_error(char *name, char **command, int rounds)
{
	char c;

	c = rounds + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, command[0], _strlen(command[0]));
	write(STDOUT_FILENO, ": No such file or directory\n", 28);
}
