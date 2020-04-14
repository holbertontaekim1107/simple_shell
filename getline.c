#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _getline - Reads input from stream
 * @inptr: Buffer to store input
 * @in: Size of inptr
 * @stream: Stream to read
 * Return: Amount of bytes to read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int r;
	char c, *buff;
	static ssize_t input; /* ssize_t same as size_t, but represents num -1 which indicates error */
	ssize_t ret;

	if (input == 0)
		fflush(stream); /* fflush function writes any unwrriten data in stream's buffer */
				/* If stream is a null ptr, fflush func flush all streams with unwritten data in buffer */
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * 80);
	if (!buff)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 80)
			buff = _realloc(buff, input, input + 1);

		buff[input] = c;
		input++;
	}
	buff[input] = '\0';
	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
