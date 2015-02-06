#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#include "matrix.h"

#ifndef X_DIM
#define X_DIM	(0)
#endif

#ifndef Y_DIM
#define Y_DIM	(1)
#endif

void matrix_free(struct matrix *matrix)
{
	if (matrix) {
		if (matrix->buffer) {
			free(matrix->buffer);
		}
		memset(matrix, 0, sizeof(*matrix));
	}
}

inline void set_xdim(struct matrix *matrix, size_t xdim)
{
	if (matrix) {
		matrix->size[X_DIM] = xdim;
	}
}

inline void set_ydim(struct matrix *matrix, size_t ydim)
{
	if (matrix) {
		matrix->size[Y_DIM] = ydim;
	}
}

inline size_t get_xdim(const struct matrix *matrix)
{
	return matrix ? matrix->size[X_DIM] : 0;
}

inline size_t get_ydim(const struct matrix *matrix)
{
	return matrix ? matrix->size[Y_DIM] : 0;
}

int matrix_init(struct matrix *matrix, size_t xdim, size_t ydim)
{
	int rc = 0;

	if (!matrix) {
		rc = EINVAL;
		goto out;
	}
	matrix->buffer = (char *) calloc(xdim, ydim);
	if (!matrix->buffer) {
		rc = ENOMEM;
		goto out;
	}
	set_xdim(matrix, xdim);
	set_ydim(matrix, ydim);
out:
	return rc;
}

char get_element(const struct matrix *matrix, size_t x, size_t y)
{
	int ydim = get_ydim(matrix);
	return matrix ? matrix->buffer[x*ydim + y] : '?';
}

void set_element(struct matrix *matrix, size_t x, size_t y, char c)
{
	if (matrix) {
		int ydim = get_ydim(matrix);
		matrix->buffer[x*ydim + y] = c;
	}
}

void print_matrix(const struct matrix *matrix)
{
	int x, y, xdim, ydim;

	if (!matrix) {
		return;
	}

	xdim = get_xdim(matrix);
	ydim = get_ydim(matrix);

	for (x = 0; x < xdim; x++) {
		for (y = 0; y < ydim; y++) {
			printf("%c ", get_element(matrix, x, y));
		}
		putchar('\n');
	}
}

