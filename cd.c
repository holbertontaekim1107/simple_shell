#include "shell.h"

/**
 * cd - builtin to change directories
 *
 * Return: Always 0 (ok)
 */
int cd(char *path)
{
	int c;

	c = chdir(path);
	return (c);
}
