#ifndef ORTHO_H_
#define ORTHO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <err.h>
#include <sys/time.h>
#define min(a,b) (a<=b?a:b)
#define max(a,b) (a<=b?b:a)
//#define _GNU_SOURCE
#define MAX_LINE_LENGTH 14
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))


struct timeval stop, start;

float similarity(char* str1, char* str2,
        unsigned int len1, unsigned int len2);
// Eye-T Algo that compute the % of similarity between two words
void copyString(char* str1, char* str2);
// Equivalent to strcpy
char* changingWordL(char* word, char* filename);
// Returns the correct word using the Levensthein method
char* changingWordS(char* word, char* filename);
// Returns the correct word using the Similarity method
int levenshtein(char *s1, char *s2);
// Returns the levenshtein distance between two giver words
void testTime(char* str1, char* filename);
// Test the two methods and gives the time of computation for each one
int testOrtho(char* str1);
// Testing function
void ToSentence(char* sentence, FILE* fptr);
#endif
