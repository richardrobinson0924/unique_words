/**
 * The primary source file for the implementations of its associated header file.
 */
#include "frequency.h"

void insert_word(WordInfo *words, int *size, char *word) {
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

int freq_cmp(const void *a, const void *b) {
	WordInfo *word_a = (WordInfo *) a;
	WordInfo *word_b = (WordInfo *) b;

	return word_a->freq < word_b->freq ? 1 :
	       word_a->freq > word_b->freq ? -1 :
	       strcmp(word_a->word, word_b->word);
}

int file_cmp(const void *a, const void *b) {
	FileInfo *file_a = (FileInfo *) a;
	FileInfo *file_b = (FileInfo *) b;

	return file_a->num < file_b->num ? 1 :
	       file_a->num > file_b->num ? -1 :
	       0;
}

void insert_arr(FileInfo *farr, const char *string, int n, WordInfo *arr) {
	qsort(arr, (size_t) n, sizeof(WordInfo), freq_cmp);

	strcpy(farr[file_index].filename, string);
	strcpy(farr[file_index].median_word, arr[n / 2].word);
	farr[file_index].num = n;

	file_index++;
}

void *get_median_word(void *vargp) {
	const char *filename = vargp;
	WordInfo word_array[MAX_WORDS];

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