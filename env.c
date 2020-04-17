int shell_env(char **args, char __attribute__((__unused__)) **head);
int shell_setenv(char **args, char __attribute__((__unused__)) **head);
int shell_unset_env(char **args, char __attribute__((__unused__)) **head);

/**
 * shell_env - Prints current env
 * @args: Array of args passed to shell
 * @head: Double pointer to head of args
 * Return: 0 Success, -1 otherwise
 */

int shell_env(char **args, char __attribute__((__unused__)) **head)
{
	int i;
	char nc = '\n';

	if (!environ) /* calling from our environ.c file */
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		/* First arg passed to write() is the file descriptor to write to */		
		/* Second is the butter to write from */
		/* Third is the size of the text in the buffer */
		write(STDOUT_FILENO, &nc, 1);
		/* 1 stands for STDOUT_FILENO */
	}

	(void)args;
	return (0);
}

/**
 * shell_setenv - Change or adds env variables to the PATH
 * @args: Array of args passed to shell
 * @head: Double pointer to the head of args
 * Return: 0 Success, -1 otherwise
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **head)
{
	char **env_var = NULL, **nenv, *nval; /* nenv=  new env, nval= new value */
	size_t s; /* size */
	int i; /* index */

	nval = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);

	_strcpy(nval, args[0]);
	_strcat(nval, "=");
	_strcat(nval, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = nval;
		return (0);
	}
	for (s = 0; environ[s]; s++)
		;

	nenv = malloc(sizeof(char *) * (size + 2));

	for (i = 0; environ[i]; i++)
		nenv[i] = environ[i];

	free(environ);
	environ = nenv;
	environ[i] = nval;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * shell_unset_env - Deleting env var from PATH
 * @args: Array of args passed to shell
 * @head: Doublt pointer to head of args
 * Return: 0 Success, -1 Error
 */

int shell_unset_env(char **args, char __attribute__((__unused__)) **head)
{
	char **env_var, **nenv;
	size_t s;
	int i, si;

	env_var = _getenv(args[0]);

	if (!env_var)
		return (0);

	for (s = 0; environ[s]; s++)

	nenv = malloc(sizeof(char *) * s);

	for (i = 0, si = 0; environ[i]; i++)
	{
		if (*env_var == environ[i])
		{
			free(env_var);
			continue;
		}
		nenv[si] = environ[i];
		si++;
	}
	free(environ);
	environ = nenv;
	return (0);
}
