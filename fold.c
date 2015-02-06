#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "matrix.h"

int fold_once(const struct matrix *data, char direction, struct matrix *result)
{
	int rc = 0;
	int x, y;
	int result_last_row, result_last_col;
	int data_last_row, data_last_col;
	struct matrix temp;

	set_xdim(&temp, get_xdim(data)*2);
	set_ydim(&temp, get_ydim(data)/2);

	result_last_row = get_xdim(&temp)-1;
	result_last_col = get_ydim(&temp)-1;
	data_last_row = get_xdim(data)-1;
	data_last_col = get_ydim(data)-1;

	switch (direction) {
	case '0':
		/* fold down */
		for (x = 0; x < get_xdim(data); x++) {
			for (y = 0; y < get_ydim(&temp); y++) {
				set_element(&temp, x, y, get_element(data, x, y));
				set_element(&temp, result_last_row-x, y, get_element(data, x, data_last_col-y));
			}
		}
		break;
	case '1':
		/* fold up */
		for (x = 0; x < get_xdim(data) ; x++) {
			for (y = 0; y < get_ydim(&temp); y++) {
				set_element(&temp, x, y, get_element(data, data_last_row-x, data_last_col-y));
				set_element(&temp, result_last_row-x, y, get_element(data, data_last_row-x, y));
			}
		}
		break;
	default:
		rc = EINVAL;
	}
	set_xdim(result, get_xdim(&temp));
	set_ydim(result, get_ydim(&temp));
	memcpy(result->buffer, temp.buffer, get_xdim(&temp)*get_ydim(&temp));

	return rc;
}

int fold(const char *data, const char *folds, size_t nr_folds, char *result)
{
	int rc = 0;
	int i = 0;
	struct matrix data_matrix = { {1, 1UL << nr_folds}, data };
	struct matrix result_matrix = { {1, 1UL << nr_folds}, result };
	struct matrix *input = &data_matrix;

	print_matrix(&data_matrix);
	printf("---\n");

	for (i = 0; i < nr_folds; i++) {
		rc = fold_once(input, folds[i], &result_matrix);
		if (rc  != 0) {
			errno = rc;
			perror("fold_once");
			goto out;
		}
		print_matrix(&result_matrix);
		printf("---\n");
		input = &result_matrix;
	}

	print_matrix(&result_matrix);
	printf("---\n");
out:
	return rc;
}

int main(int argc, char *argv[])
{
	int status = EXIT_SUCCESS;
	char data[] =  "1234";
	char folds[] = "1";
	char result[sizeof(data)] = {'\0'};

	status = fold(data, folds, sizeof(folds)-1, result);

	exit(status);
}
