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

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to old memory
 * @old_size: size of old memory
 * @new_size: size of new memory
 *
 * Return: pointer to new memory, or NULL on failure
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char *old_ptr;
	char *new_ptr;
	size_t i = 0;
	size_t copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	old_ptr = ptr;
	copy_size = old_size;
	if (new_size < old_size)
		copy_size = new_size;

	while (i < copy_size)
	{
		new_ptr[i] = old_ptr[i];
		i++;
	}

	free(ptr);
	return (new_ptr);
}
