//
// Created by Richard Robinson on 2018-12-26.
//

#ifndef UNIQUE_WORDS_FREQUENCY_H
#define UNIQUE_WORDS_FREQUENCY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_STRING 101
#define true  1
#define false 0

/**
 * A typedef struct for the WordArray, which includes a word (string) field and a frequency (int) field
 */
typedef struct WordArray {
	char word[MAX_STRING];
	int freq;
} WordArray;

/**
 * A typedef struct for the FileArray, which includes a filename (string) field, a field to store the number of unqiue words (int), and a field for the median word (string)
 */
typedef struct FileArray {
	char filename[MAX_WORDS];
	int num;
	char median_word[MAX_STRING];
} FileArray;

/** A global static variable to count the number of files */
static int file_index = 0;

/** A global array of all FileArray objects from the files */
FileArray file_array[100];

/**
 * Inserts a string {@code word} into an array of WordArrays {@code words}, and stores the total number of unique words in pointer n. If the word already exists, the frequency of the word struct element is incremented. Otherwise, the word is unique and added to the WordArray array, with its frequency initiated to 1.
 *
 * Note, {@code n} must be first initialized (typically to 0) in the caller to store the number.
 *
 * @param words an array of WordArray structs
 * @param n a pointer to the variable which stores the number of unique words thus far, amd acts as a pseudo-global variable
 * @param word a string within the array of strings
 */
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

/**
 * A comparator function for the qsort function for WordArrays. Given two WordArrays, this function sorts an array of WordArrays by decreasing frequency
 */
int freq_cmp(WordArray *a, WordArray *b) {
	return a->freq < b->freq ? 1 :
	       a->freq > b->freq ? -1 :
	       strcmp(a->word, b->word);
}

/**
 * A comparator function for the qsort function for FileArrays. Given two WordArrays, this function sorts an array of WordArrays by decreasing number of unique words
 */
int file_cmp(FileArray *a, FileArray *b) {
	return a->num < b->num ? 1 :
	       a->num > b->num ? -1 :
	       0;
}

/**
 * Sorts {@code arr} struct elements by frequency. Then, for each file, stores the filename, number of unique words, and the median word into a FileArray object
 *
 * @param farr the FileArray struct into which to store the data
 * @param string the filename of the acting file
 * @param n the number of unique words
 * @param arr the WordArray struct array of words, sorted by frequency
 */
void insert_arr(FileArray *farr, char *string, int n, WordArray *arr) {
	qsort(arr, (size_t) n, sizeof(WordArray), (int (*)(const void *, const void *)) freq_cmp);

	strcpy(farr[file_index].filename, string);
	strcpy(farr[file_index].median_word, arr[n / 2].word);
	farr[file_index].num = n;

	file_index++;
}

/**
 * The main threaded function which executes upon each file in the argument list. Scans the associated filename passed to it, and generates a sorted list of WordArray objects from the strings in the file.
 *
 * It then stores the WordArray and associated information into a FileArray object in the array {@code file_array}, and increments the global {@code file+index} counter of files.
 *
 * @param vargp the passed parameter from the {@code pthread_create()} function, the string filename command line argument taken as a pointer (ultimately casted to a regular string)
 * @return NULL
 */
void *getMedianWord(void *vargp) {
	char *filename = *(char **) vargp;
	WordArray word_array[MAX_WORDS];

	FILE *fp = fopen(filename, "r");
	char word[101];

	int n = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s", word);
		insert_word(word_array, &n, word);
	}

	insert_arr(file_array, filename, n, word_array);

	return NULL;
}

#endif //UNIQUE_WORDS_FREQUENCY_H
