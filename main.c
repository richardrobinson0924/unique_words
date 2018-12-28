#include "frequency.h"

FileInfo get_median_word(void *vargp) {
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

	FileInfo f;
	strcpy(f.filename, filename);
	strcpy(f.median_word, word_array[n/2].word);
	f.num = n;

	return f;
}

int main(int argc, char *argv[]) {
	file_array_ptr = mmap(0, MAX_WORDS * sizeof(FileInfo), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	for (int i = 0; i < argc - 1; i++) {
		if (fork() == 0) {
			file_array_ptr[i] = get_median_word(argv[i + 1]);
			exit(0);
		} else {
			usleep(30000);
		}
	}

	print_array(file_array_ptr, argc - 1);
	return 0;
}
