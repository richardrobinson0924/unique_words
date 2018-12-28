#include "frequency.h"

void insert_word(WordInfo *words, int *size, char *word) {
	int is_unique = true;

	for (int i = 0; i < *size; i++) {
		if (strcmp(word, words[i].word) == 0) {
			words[i].freq++;
			is_unique = false;
		}
	}

	if (is_unique) {
		strcpy(words[*size].word, word);
		words[*size].freq = 1;
		(*size)++;
	}
}

int freq_cmp(const void *a, const void *b) {
	WordInfo *word_a = (WordInfo *) a;
	WordInfo *word_b = (WordInfo *) b;

	return word_a->freq < word_b->freq ?  1 :
	       word_a->freq > word_b->freq ? -1 :
	       strcmp(word_a->word, word_b->word);
}

int file_cmp(const void *a, const void *b) {
	FileInfo *file_a = (FileInfo *) a;
	FileInfo *file_b = (FileInfo *) b;

	return file_a->num < file_b->num ?  1 :
	       file_a->num > file_b->num ? -1 :
	       0;
}

void print_array(FileInfo *file_array, int n) {
	qsort((void *) file_array, (size_t) n, sizeof(FileInfo), file_cmp);

	for (int k = 0; k < n; ++k) {
		printf("\n%s %d %s", file_array[k].filename, file_array[k].num, file_array[k].median_word);
	}
}
