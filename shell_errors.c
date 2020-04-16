#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int make_error(char **args, int x);

/**
 * nlen - Counts length of the number
 * @num: Measured number
 * Return: Digit's length
 */

int num_len(num)
{
	int length;
	unsigned int numb;

	length = 1;

	if (numb < 0)
	{
		length++
	}
	else if (numb > 9)
	{
		length++;
		numb = num / 10;
	}
	else
	{
		numb = num; 
	}
	return(length);
}


/**
 * my_itoa - Convert integer to string (words)
 * @num: Int
 * Return: String
 */

char *_itoa(int num)
{
	char *buff;
	int length = num_len(num);
	unsigned int numb;

	buff = malloc(sizeof(char) * (length + 1));
	if (!buff)
		return (NULL);

	buff[len] = '\0';

	if (num < 0)
	{
		numb = num * -1;
		buff[0] = '-';
	}
	else
	{
		numb = num;
	}

	length--;
	do 
	{
		buff[length] = (numb % 10) + '0';
		numb /= 10;
		length--;
	}while (numb > 0);
	return (buff);
}

/**
 * make_error - Creates error message to stderr
 * @args: An array of args
 * @err: Error value
 * Return: Error value
 */

int make_error(**args, int x);
{
	char *error;

	switch (err)
	{
	case -1:
		error = env_error(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));
	if(error)
		free(error);
	return(err);
}






}
