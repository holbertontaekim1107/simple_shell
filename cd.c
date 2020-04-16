#include "shell.h"
#include <dirent.h>

/**
 * cd - builtin to change directories
 * @path: path of directory to switch to
 *
 * Return: Always 0 (ok)
 */
int cd(char *path)
{
	int c;
	DIR *o;

	if (!path)
	{
		return (127);
	}
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
		return (127);
	}
	return (c);
}
