#include "frequency.h"

/**
 * The heart of the program. Iterates through all elements in the array `words`. If `word` is already in the WordInfo array `words`, the frequency associated with the word is incremented. Otherwise, the word is added to the array, the frequency is initialized to 1, and the size of the array is incremented.
 *
 * @param words the array of WordInfo objects in which to put the desired word.
 * @param size the number of elements in the array. Incremented upon each addition.
 * @param word the word to search for in the array, and add it to the array if it is not already there
 */
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

/**
 * A comparator for `WordInfo` object pointers. Used to sort an array of words from WordInfo objects ascending by frequency, and then alphabetically.
 *
 * @param a the first WordInfo object
 * @param b the second WordInfo object
 * @return `1` if a's frequency is greater than b's, or if they are of equal frequency and the former appears first alphabetically; `-1` otherwise
 */
int freq_cmp(const void *a, const void *b) {
	WordInfo *word_a = (WordInfo *) a;
	WordInfo *word_b = (WordInfo *) b;

	return word_a->freq < word_b->freq ? 1 :
	       word_a->freq > word_b->freq ? -1 :
	       strcmp(word_a->word, word_b->word);
}

/**
 * A comparator for `FileInfo` object pointers. Used to sort an array of FileInfo objects descending by number of unique words
 *
 * @param a the first FileInfo object
 * @param b the second FileInfo object
 * @return `1` if a has more unique words than b, `-1` if the reverse, and `0` if the numbers are equal
 */
int file_cmp(const void *a, const void *b) {
	FileInfo *file_a = (FileInfo *) a;
	FileInfo *file_b = (FileInfo *) b;

	return file_a->num < file_b->num ? 1 :
	       file_a->num > file_b->num ? -1 :
	       0;
}

/**
 * Given an array of FileInfo objects and the size of the array, the function first sorts the array. It then iterates through all the elements in the array and prints they're respective fields.
 *
 * @param file_array the array of FileInfo objects to be printed
 * @param n the size of the array
 */
void print_array(FileInfo *file_array, int n) {
	qsort((void *) file_array, (size_t) n, sizeof(FileInfo), file_cmp);

	for (int k = 0; k < n; ++k) {
		printf("\n%s %d %s", file_array[k].filename, file_array[k].num, file_array[k].median_word);
	}
}
