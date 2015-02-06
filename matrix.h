#ifndef MATRIX_H
#define MATRIX_H

#ifndef MAX_DIMS
#define MAX_DIMS	(2)	/* Maximum number of matrix demensions */
#endif

struct matrix {
	size_t size[MAX_DIMS];
	char *buffer;
};

void matrix_free(struct matrix *matrix);
inline void set_xdim(struct matrix *matrix, size_t xdim);
inline void set_ydim(struct matrix *matrix, size_t ydim);
inline size_t get_xdim(const struct matrix *matrix);
inline size_t get_ydim(const struct matrix *matrix);
int matrix_init(struct matrix *matrix, size_t xdim, size_t ydim);
char get_element(const struct matrix *matrix, size_t x, size_t y);
void set_element(struct matrix *matrix, size_t x, size_t y, char c);
void print_matrix(const struct matrix *matrix);

#endif /* MATRIX_H */
