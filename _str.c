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
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (*s1 == '\0' || *s2 == '\0')
		return (*s1 - *s2);
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
/**
 * _strncmp - compares n bytes of two strings
 * @s1: string 1 to be compared
 * @s2: string 2 to be compared
 * @n: max bytes
 * Return: a positive, negative, or 0 number based on the first different char
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2 && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}
