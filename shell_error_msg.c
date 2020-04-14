#include "shell.h"

char *env_error(char **args);
char *break_error(char **args);
char *exit_error(char **args);

/**
 * env_error - Our Shell.c's env error msgs
 * @args: Array of args passed
 * Return: String
 */

char *env_error(char **args)
{
	int length;
	char *error, *pstring;

	pstring = _itoa(hist);
	if (!pstring)
	{
		return(NULL);
	}
	args--;
	
	length = _strlen(name) + _strlen(pstring) + _strlen(args[0] + 45;
	eror = malloc(sizeof(char) * (length +1);

	if(!error)
	{
		free(pstring);
		return (NULL);
	}
	
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, pstring);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Cannot add or remove from environment");
}	
