#include "frequency.h"

/**
 * The main function. Runs {@code getMedianWord()} in parallel threads for each file, then outputs the sorted elements in FileArray array.
 */
int main(int argc, char **argv) {
	pthread_t tid[argc];

	for (int i = 0; i < argc - 1; ++i) {
		pthread_create(&(tid[i]), NULL, getMedianWord, (void *) &argv[i + 1]);
		pthread_join(tid[i], NULL);
	}

	qsort(file_array, (size_t) (argc - 1), sizeof(FileArray), (int (*)(const void *, const void *)) file_cmp);

	for (int k = 0; k < argc - 1; ++k) {
		printf("\n%s %d %s", file_array[k].filename, file_array[k].num, file_array[k].median_word);
	}

	return 0;
}
