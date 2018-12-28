#include "frequency.h"
#include <stdlib.h>

/**
 * The main function. Runs {@code getMedianWord()} in parallel threads for each file, then outputs the sorted elements in FileArray array.
 */
int main(int argc, char **argv) {
	pthread_t tid[argc];

	for (int i = 1; i < argc; ++i) {
		pthread_create(&tid[i], NULL, get_median_word, argv[i]);
	}

	for (int j = 1; j < argc; ++j) {
		pthread_join(tid[j], NULL);
	}

	qsort(file_array, (size_t) (argc - 1), sizeof(FileInfo), file_cmp);

	for (int k = 0; k < argc - 1; ++k)
		printf("\n%s %d %s", file_array[k].filename, file_array[k].num, file_array[k].median_word);

	pthread_exit(NULL);
}


