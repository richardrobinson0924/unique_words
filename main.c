#include "frequency.h"

/**
 * The main function. Runs {@code getMedianWord()} in parallel threads for each file, then outputs the sorted elements in FileArray array.
 */
int main(int argc, char **argv) {
	int actual_args = argc - 1;
	pthread_t tid[argc];

	for (int i = 0; i < actual_args; ++i)
		pthread_create(&tid[i], NULL, getMedianWord, (void *) &argv[i + 1]);

	for (int j = 0; j < actual_args; ++j)
		pthread_join(tid[j], NULL);

	qsort(file_array,
	      (size_t) actual_args,
	      sizeof(FileArray),
	      (int (*)(const void *, const void *)) file_cmp
	);

	for (int k = 0; k < actual_args; ++k)
		printf("\n%s %d %s",
		       file_array[k].filename,
		       file_array[k].num,
		       file_array[k].median_word
		);

	return 0;
}
