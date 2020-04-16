#include "shell.h"
#include <dirent.h>

/**
 * cd - builtin to change directories
 * @path: path of directory to switch to
 * @envp: program environment, to be used to find home
 *
 * Return: Always 0 (ok)
 */
int cd(char *path, char **envp)
{
	int c, i;
	DIR *o;
	char *home, *old;

	for (i = 0; envp[i]; i++)
	{
		if (!_strncmp(envp[i], "HOME=", 4))
		{
			home = malloc(_strlen(envp[i] + 5) + 1);
			_strcpy(home, envp[i] + 5);
		}
		if (!_strncmp(envp[i], "OLDPWD=", 6))
		{
			old = malloc(_strlen(envp[i] + 7) + 1);
			_strcpy(old, envp[i] + 7);
		}
	}
	if (!path || !_strcmp(path, "~") || !_strcmp(path, "$HOME"))
		path = home;
	if (!_strcmp(path, "-"))
		path = old;
	if ((o = opendir(path)) != NULL)
	{
		c = chdir(path);
		closedir(o);
	}
	else
	{
		write(2, "hsh: 1: cd: Can't cd to", 24);
		write(2, path, _strlen(path));
		write(2, "\n", 1);
		free(home);
		free(old);
		return (127);
	}
	free(home);
	free(old);
	return (c);
}
