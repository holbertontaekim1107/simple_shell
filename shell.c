#include "shell.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define NOMEM ("Error: Failed to allocate memory\n")
#define FAILFORK ("Error creating fork\n")

int path_check(int *runs, char **tok, char **envp, char **argv,
	       char **pathTok);
void free_all(char **s);
int fork_exe(char **tok, char **envp);
void sigint_handle(int sig);
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
	size_t n = 1;
	char *buff = malloc(1), **tok, *path = envp[8] + 5, **ptok;
	int runs = 1, i, tmp;
	/*When not mallocing, getline alloced too much space. Rely on realloc*/
	(void)argc;
	/*Set SIGINT to default to be caught by the handler*/
	signal(SIGINT, sigint_handle);

	ptok = _strtok(path, ":");
	while (1)/*Always true unless exit sent to prompt*/
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		if (getline(&buff, &n, stdin) == EOF)
			return (0);
/*If buff is small, getline reallocs*/
		if (!buff)
			dprintf(STDERR_FILENO, NOMEM), exit(97);
		if (!_strcmp(buff, ""))
			continue;
		tok = _strtok(buff, " ");
		if (!_strcmp(tok[0], "exit"))
		{
			free(buff);
			if (_atoi(tok[1]) > 0)
			{
				tmp = _atoi(tok[1]);
				free_all(tok);
				exit(tmp);
			}
			else
			{
				free_all(tok);
				return (0);
			}
		}
		path_check(&runs, tok, envp, argv, ptok);
		runs++;
	}
	free(buff);
	for (i = 0; tok[i]; i++)
		free(tok[i]);
	free(tok);
	return (0);
}
/**
 * sigint_handle - a signal handler for sigint
 * @sig: Caught signal
 *
 * Return: void
 */
void sigint_handle(int sig)
{
	(void)sig;
	signal(SIGINT, sigint_handle);
	printf("\n$ ");
	fflush(stdout);
}
/**
 * fork_exe - performs an action based on fork pid
 * @tok: An array of strings containing the tokens
 * @envp: Program environment
 *
 * Return: 0
 */
int fork_exe(char **tok, char **envp)
{
	int e = 0, status;
	pid_t pid = fork(), w;

	if (pid == 0)
	{
		e = execve(tok[0], tok, envp);
		exit(-1);
	}
	else if (pid == -1)
		dprintf(STDERR_FILENO, FAILFORK), exit(99);
	else
	{
		do {
			w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			if (w == -1)
				perror("Error at waitpid\n"), exit(99);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (WEXITSTATUS(status) == 255)
			return (-1);
	}
	return (0);
}
/**
 * free_all - frees a char **
 * @s: char ** to be freed
 *
 * Return: void
 */
void free_all(char **s)
{
	int i = 0;

	for (; s[i]; i++)
		free(s[i]);
	free(s);
}
/**
 * path_check - determines if program needs to check the path, then checks
 * @runs: Number of runs for the program
 * @tok: tokenized input
 * @envp: program environment
 * @argv: argument vector
 * @pathTok: Tokenized path
 *
 * Return: Always 0
 */
int path_check(int *runs, char **tok, char **envp, char **argv, char **pathTok)
{
	char *path, *fname = malloc(_strlen(tok[0]));
	int i, sflag = 0, e;

	_strcpy(fname, tok[0]);
	for (i = 0; tok[0][i]; i++)
		if (tok[0][i] == '/')
		{
			sflag = 1;
			break;
		}
	if (sflag == 1)
		e = fork_exe(tok, envp);
	else
	{
		for (i = 0; pathTok[i]; i++)
		{
			path = malloc((_strlen(pathTok[i]) + _strlen(tok[0])
				       + 1) * sizeof(char));
			if (path == NULL)
				perror(NOMEM);
			_strcpy(path, pathTok[i]);
			path[_strlen(path)] = '/';
			_strcpy(path + _strlen(pathTok[i]) + 1, fname);
			free(tok[0]);
			tok[0] = path;
			e = fork_exe(tok, envp);
			if (e == 0)
				break;
			if (e == -1)
				continue;
		}
		if (!pathTok[i])
			dprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
				argv[0], *runs++, fname);
	}
	return (0);
}
