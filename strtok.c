#include "shell.h"
#include <string.h>

#define NOMEM ("Error allocating memory")
/**
 * _strtok - calls strtok on a string
 * @line: string to call on
 * @delm: delimiter to use to break string
 *
 * Return: double pointer of tokenized string
 */

char **_strtok(char *line, char *delm)
{
	char *tok, **ptr, *tmpline = NULL;
	int i;
	size_t words = 0;

	if (line == NULL || delm == NULL)
		return (NULL);
	if (line[0] == ':' || !_strcmp(line, ""))
	{
		tmpline = malloc(_strlen(line) + 2);
		tmpline[0] = '.';
		_strcpy(tmpline + 1, line);
		line = tmpline;
	}
	for (i = 0; line[i]; i++)
	{
		if (line[i] != *delm && (line[i + 1] == *delm ||
					 line[i + 1] == '\0'))
			words++;
	}
	if (line[i - 1] == '\n')
		line[i - 1] = '\0';
	ptr = malloc(sizeof(char *) * (words + 1));
	if (!ptr)
	{
		write(2, NOMEM, _strlen(NOMEM));
		return (0);
	}

	tok = strtok(line, delm);

	for (i = 0; tok != NULL; i++)
	{
		ptr[i] = malloc(_strlen(tok) + 1);
		if (!ptr[i])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			exit(99);
		}
		_strcpy(ptr[i], tok);
		tok = strtok(NULL, delm);
	}
	ptr[i] = NULL;
	if (tmpline)
		free(tmpline);
	return (ptr);
}
