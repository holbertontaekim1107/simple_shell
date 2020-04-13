#include "shell.h"

int nlen(int num)
char *my_itoa(int num);

/**
 *
 *
 */

int nlen(num)
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

char *my_itoa(int num)
{
	char *buff;
	int length;
	unsigned int uint;
	
	length = nlen(num);
	buff = malloc(sizeof(char) * (length + 1);

	if(!buffer)
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
