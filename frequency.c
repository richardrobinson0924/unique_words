/**
 * The primary source file for the implementations of its associated header file.
 */
#include "frequency.h"

void insert_word(WordArray *words, int *size, char *word) {
	int is_unique = true;

	for (int i = 0; i < *size; i++)
		if (!strcmp(word, words[i].word)) {
			words[i].freq++;
			is_unique = false;
		}

	if (is_unique) {
		strcpy(words[*size].word, word);
		words[(*size)++].freq = 1;
	}
}

int freq_cmp(WordArray *a, WordArray *b) {
	return a->freq < b->freq ? 1 :
	       a->freq > b->freq ? -1 :
	       strcmp(a->word, b->word);
}

int file_cmp(FileArray *a, FileArray *b) {
	return a->num < b->num ? 1 :
	       a->num > b->num ? -1 :
	       0;
}

void insert_arr(FileArray *farr, char *string, int n, WordArray *arr) {
	qsort(arr,
	      (size_t) n,
	      sizeof(WordArray),
	      (int (*)(const void *, const void *)) freq_cmp
	);

	strcpy(farr[file_index].filename, string);
	strcpy(farr[file_index].median_word, arr[n / 2].word);
	farr[file_index].num = n;

	file_index++;
}

void *getMedianWord(void *vargp) {
	const char *filename = vargp;
	WordArray word_array[MAX_WORDS];

	FILE *fp = fopen(filename, "r");
	char word[101];

	int n = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s", word);
		insert_word(word_array, &n, word);
	}

	insert_arr(file_array, filename, n, word_array);

	pthread_exit(NULL);
}