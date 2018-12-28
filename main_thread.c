#include "frequency.h"

void *get_median_word(void *vargp) {
	const char *filename = vargp;
	WordInfo word_array[MAX_WORDS];

	FILE *fp = fopen(filename, "r");
	char word[MAX_STRING];

	int n = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s", word);
		insert_word(word_array, &n, word);
	}

	qsort(word_array, (size_t) n, sizeof(WordInfo), freq_cmp);

	strcpy(file_array[count].filename, filename);
	strcpy(file_array[count].median_word, word_array[n / 2].word);
	file_array[count].num = n;

	count++;
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	pthread_t tid[argc];

	for (int i = 0; i < argc-1; ++i) {
		pthread_create(&tid[i], NULL, (void *(*)(void *)) get_median_word, argv[i + 1]);
	}

	for (int j = 0; j < argc - 1; ++j) {
		pthread_join(tid[j], NULL);
	}

	print_array(file_array, argc - 1);
	pthread_exit(NULL);
}
