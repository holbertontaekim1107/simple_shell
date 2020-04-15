#include "shell.h"

/**
 * _strcpy - copies src string to dest
 * @dest: destination string
 * @src: source string
 *
 * Return: void
 */

char *_strcpy(char *dest, char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
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
 * _strcat - Concantenates two strings
 * @dest: poiner to dest string
 * @src: pointer to source string
 * Return: pointer to dest string
 */

char *_strcat(char *dest, const char *src)
{
	char *temp_dest;
	const char *temp_src;

	temp_dest = dest;
	temp_src =  src;

	while (*temp_dest != '\0')
		temp_dest++;

	while (*temp_src != '\0')
		*temp_dest++ = *temp_src++;
	*temp_dest = '\0';
	return (dest);
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
