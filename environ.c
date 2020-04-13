#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 *
 *
 *
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
 *
 *
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
 *
 * 
 *
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
