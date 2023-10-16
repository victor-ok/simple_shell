#include "shell.h"

/**
 * create_child_process - A function that creates a sub process from parent
 * @command: pointer to command
 * @name: shell name
 * @env: pointer to env variables.
 * @rounds: num of time executed
 *
 * Return: Nothing.
 */
void create_child_process(char **command, char *name, char **env, int rounds)
{
	int pid = 0;
	int status = 0;
	int wait_error = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		mem_free_exit(command);
	}
	else if (pid == 0)
	{
		exe(command, name, env, rounds);
		mem_free(command);
	}
	else
	{
		wait_error = waitpid(pid, &status, 0);
		if (wait_error < 0)
		{
			mem_free_exit(command);
		}
		mem_free(command);
	}
}


/**
  * change_dir - Afunction that changes the working directory.
  *
  * @path: The new current working directory.
  *
  * Return: 0 on success, -1 on failure.
  */
int change_dir(const char *path)
{
	char *buff = NULL;
	size_t size = 1024;

	if (path == NULL)
	{
		path = getcwd(buff, size);
	}
	if (chdir(path) == -1)
	{
		perror(path);
		return (98);
	}
	return (1);
}
