#include "shell.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define NOMEM ("Error: Failed to allocate memory\n")
#define FAILFORK ("Error creating fork\n")

int path_check(int *runs, char **tok, char **envp, char **argv,
	       char **pathTok);
void free_all(char **s);
int fork_exe(char **tok, char **envp, char *fname);
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
	char *buff = malloc(1), **tok, *path,
		**ptok;
	int runs = 1, tmp, p = 0, j;
	/*When not mallocing, getline alloced too much space. Rely on realloc*/
	(void)argc;
	/*Set SIGINT to default to be caught by the handler*/
	signal(SIGINT, sigint_handle);

	buff[0] = '\0';
	for (j = 0; _strncmp(envp[j], "PATH=", 4); j++)
		;
	path = malloc(_strlen(envp[j] + 5));
	_strcpy(path, envp[j] + 5);
	ptok = _strtok(path, ":");
	while (1)/*Always true unless exit sent to prompt*/
	{
		j = 0;
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		if (getline(&buff, &n, stdin) == EOF)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			free(path);
			free_all(ptok);
			if (buff)
				free(buff);
			return (0);
		}
/*If buff is small, getline reallocs*/
		if (!buff)
			write(2, NOMEM, _strlen(NOMEM)), exit(97);
		while (*(buff + j) == ' ')
			j++;
		if (!_strcmp(buff + j, "\n"))
			continue;
		tok = _strtok(buff, " ");
		if (!_strcmp(tok[0], "exit"))/*exit builtin with(out) args*/
		{
			free(buff);
			free(path);
			free_all(ptok);
			if (tok[1] != NULL && _atoi(tok[1]) > 0)
			{
				tmp = _atoi(tok[1]);
				free_all(tok);
				exit(tmp);
			}
			else
			{
				free_all(tok);
				return (p);
			}
		}
		else if (!_strcmp(tok[0], "cd"))
		{
			cd(tok[1]);
			runs++;
			continue;
		}
		p = path_check(&runs, tok, envp, argv, ptok);
		runs++;
		free_all(tok);
	}
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
	write(1, "\n$ ", 3);
	fflush(stdout);
}
/**
 * fork_exe - performs an action based on fork pid
 * @tok: An array of strings containing the tokens
 * @envp: Program environment
 *
 * Return: 0
 */
int fork_exe(char **tok, char **envp, char *fname)
{
	int e = 0, status;
	pid_t pid = fork();

	if (pid == 0)
	{
		e = execve(tok[0], tok, envp);
		perror(fname);
		exit(e);
	}
	else if (pid == -1)
		write(2, FAILFORK, _strlen(FAILFORK)), exit(99);
	else
	{
		do {
			if (waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1)
				perror("waitpid"), exit(99);
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

	if (s == NULL)
		return;
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
	char *path, *fname = malloc(_strlen(argv[0] + 2));
	struct stat *buf = malloc(sizeof(struct stat *));
	int i, sflag = 0, e = -1;

	if (fname == NULL || buf == NULL)
		write(2, NOMEM, _strlen(NOMEM)), exit(99);
	_strcpy(fname, argv[0] + 2);
	for (i = 0; tok[0][i]; i++)
		if (tok[0][i] == '/')
		{
			sflag = 1;
			break;
		}
	if (sflag == 1)
		e = fork_exe(tok, envp, fname);
	else
	{
		for (i = 0; pathTok[i]; i++)
		{
			path = malloc((_strlen(pathTok[i]) + _strlen(tok[0])
				       + 1) * sizeof(char));
			if (path == NULL)
				write(2, NOMEM, _strlen(NOMEM)), exit(99);
			_strcpy(path, pathTok[i]);
			path[_strlen(path)] = '/';
			_strcpy(path + _strlen(pathTok[i]) + 1, fname);
			free(tok[0]);
			tok[0] = path;
			if (!stat(tok[0], buf))
				e = fork_exe(tok, envp, fname);
			if (e == 0)
				break;
			if (e == -1)
				continue;
		}
		if (!pathTok[i])
		{
			stat(tok[0], buf);
			perror(fname);
			free(fname);
			free(buf);
			return (127);
		}
	}
	runs++;
	free(buf);
	free(fname);
	return (0);
}
