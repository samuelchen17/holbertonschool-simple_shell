#include "shell.h"

int resize_buffer(char **lineptr, size_t *n, size_t needed)
{
	char *new_buf;
	size_t new_size = *n;

	while (new_size <= needed)
		new_size *= 2;

	new_buf = malloc(new_size);
	if (!new_buf)
		return (-1);

	memcpy(new_buf, *lineptr, *n);

	free(*lineptr);
	*lineptr = new_buf;
	*n = new_size;

	return (0);
}