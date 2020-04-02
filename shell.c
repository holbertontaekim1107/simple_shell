#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define NOMEM ("Error: Failed to allocate memory")
void sigint_handle(int sig);
int _strcmp(char *s1, char *s2);
/**
 * main - A simple shell program
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Program environment
 *
 * Return: Always 0 (ok)
 */
int main(int argc, char *argv[], char *envp[])
{
	size_t n = 1, i = 0;
	char *buff = NULL;
	int rflag = 0, tmp;
	/*When not mallocing, getline alloced too much space. Rely on realloc*/

	/*Set SIGINT to default to be caught by the handler*/
	signal(SIGINT, sigint_handle);

	while (rflag == 0)/*Always true unless exit sent to prompt*/
	{
		i = 0;
		printf("$ ");/*Prints the $ prompt*/
		getline(&buff, &n, stdin);/*If buff is small, getline reallocs*/
		if (!buff)
			dprintf(STDERR_FILENO, NOMEM), exit(97);
		while (buff[i])
			i++;
		buff[i - 1] = 0;/*getline automatically appends a newline*/
		if (!_strcmp(buff, "exit"))
			rflag = 1;
		tmp = n;
		printf("%d, %s\n", tmp, buff);
	}
	return (0);
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
/**
 * sigint_handle - a signal handler for sigint
 * @sig: Caught signal
 *
 * Return: void
 */
void sigint_handle(int sig)
{
	signal(SIGINT, sigint_handle);
	printf("\n$ ");
	fflush(stdout);
}
