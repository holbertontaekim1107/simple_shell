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
		numb = numb / 10;
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
	int length;
	unsigned int uint;
	
	length = nlen(num);
	buff = malloc(sizeof(char) * (length + 1);

	if(!buff)
	{
		return (NULL);
	}

	buff[length] = "\0";

	if (num < 0)
	{
		uint = num;
	}
	length--;
	return(buff);
}

/**
 *
 *
 *
 */

int make_error(**args, int x);
{







}
