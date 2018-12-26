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
void insert_word(WordArray *words, int *size, char *word);

/**
 * A comparator function for the qsort function for WordArrays. Given two WordArrays, this function sorts an array of WordArrays by decreasing frequency
 */
int freq_cmp(WordArray *a, WordArray *b);

/**
 * A comparator function for the qsort function for FileArrays. Given two WordArrays, this function sorts an array of WordArrays by decreasing number of unique words
 */
int file_cmp(FileArray *a, FileArray *b);

/**
 * Sorts {@code arr} struct elements by frequency. Then, for each file, stores the filename, number of unique words, and the median word into a FileArray object
 *
 * @param farr the FileArray struct into which to store the data
 * @param string the filename of the acting file
 * @param n the number of unique words
 * @param arr the WordArray struct array of words, sorted by frequency
 */
void insert_arr(FileArray *farr, char *string, int n, WordArray *arr);

/**
 * The main threaded function which executes upon each file in the argument list. Scans the associated filename passed to it, and generates a sorted list of WordArray objects from the strings in the file.
 *
 * It then stores the WordArray and associated information into a FileArray object in the array {@code file_array}, and increments the global {@code file+index} counter of files.
 *
 * @param vargp the passed parameter from the {@code pthread_create()} function, the string filename command line argument taken as a pointer (ultimately casted to a regular string)
 * @return NULL
 */
void *getMedianWord(void *vargp);

#endif //UNIQUE_WORDS_FREQUENCY_H
