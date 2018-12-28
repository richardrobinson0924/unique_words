# Unique Words Program

Given a list of text file paths as command line arguments, calculates and returns the median word of each file.  Run the forked version via

```console
$ gcc -Wall -o unique_words frequency.h main.c -lpthread
$ ./unique_words args1 arg2 ...
```

and the thread version via

```console
$ gcc -Wall -o unique_words frequency.h main_thread.c -lpthread
$ ./unique_words args1 arg2 ...
```