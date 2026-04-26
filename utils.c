#include "shell.h"

/**
 * file_exists - checks if a file exists at a given path
 * @path: file path to check
 *
 * Return: 1 if file exists, 0 otherwise
 */
int file_exists(char *path)
{
	struct stat st;

	return (stat(path, &st) == 0);
}
