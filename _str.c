#include "shell.h"

/**
 * _strcpy - copies src string to dest
 * @dest: destination string
 * @src: source string
 *
 * Return: void
 */
void _strcpy(char *dest, char *src)
{
	int i = 0;

	for (; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}
/**
 * _strlen - finds the length of an input string
 * @s: input string
 *
 * Return: length of string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		;
	return (i);
}
/**
 * _strcmp - compares two strings
 *@s1: string 1 to be compared
 *@s2: string 2 to be compared
 * Return: a positive, negative, or 0 number based on the first different char
 */
int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}
