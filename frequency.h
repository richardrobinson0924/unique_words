#ifndef UNIQUE_WORDS_FREQUENCY_H
#define UNIQUE_WORDS_FREQUENCY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_WORDS 1000
#define MAX_STRING 101
#define true  1
#define false 0

/**
 * A structure which contains a field for a document filename, the number of unique words in the document, and the median word of the document
 */
typedef struct {
	char filename[MAX_WORDS];
	int num;
	char median_word[MAX_STRING];
} FileInfo;

typedef struct {
	char word[MAX_STRING];
	int freq;
} WordInfo;

static FileInfo *file_array_ptr;
static FileInfo file_array[MAX_WORDS];
static int count = 0;

void insert_word(WordInfo *words, int *size, char *word);

int freq_cmp(const void *a, const void *b);
int file_cmp(const void *a, const void *b);

void print_array(FileInfo *file_array, int n);

#endif //UNIQUE_WORDS_FREQUENCY_H
