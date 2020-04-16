#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Makes a copy of the env
 * Return: Error = NULL, otherwise a double pointer to new copy
 */

char **_copyenv(void)
{
	char **nenv;
	size_t s;
	int i;

	for (s = 0; environ[s]; s++)

	nenv = malloc(sizeof(char *) * (s + 1));

	if (!nenv)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		nenv[i] = malloc(_strlen(environ[i]) + 1);

		if (!nenv[i])
		{
			for (i--; i >= 0; i--)
				free(nenv[i]);
			free(nenv);
			return (NULL);
		}
		_strcpy(nenv[i], environ[i]);
	}
	nenv[i] = NULL;

	return (nenv);
}

/**
 * free_env - Frees environment copy
 */

void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		free(environ[i]);
	}
	free(environ);
}

/**
 * _getenv - Gets env var from PATH
 * @var: Name of env var it gets
 * Return: If env var doesnt exist = NULL, otherwise a pointer to env var
 */

char **_getenv(const char *var)
{
	int i, len;

	len = _strlen(var);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], len) == 0)
			{
			return (&environ[i]);
			}
	}
	return (NULL);
}
