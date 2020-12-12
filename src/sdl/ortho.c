#include "ortho.h"


float similarity(char* str1, char* str2,
        unsigned int len1, unsigned int len2)
{
    float maxi = max(len1, len2);
    int similarity = 0;
    unsigned int i = 0;
    unsigned int j = 0;

    while (i < len1 && j < len2)
    {
        if (str1[i] == str2[j])
        {
            similarity++;
            i++;
            j++;
        }
        else if (len1 < len2)
        {
            len1++;
            j++;
        }
        else if (len1 > len2)
        {
            i++;
            len1--;
        }
        else{
            i++;
            j = j + 2;
        }
    }
    if ((similarity/maxi)*100 < 50)
        return .0f;
    return (similarity/maxi)*100;
}

void copyString(char* str1, char* str2)
{
    for(size_t i = 0; i < strlen(str2); i++)
    {
        str1[i] = str2[i];
    }
}


char* changingWordL(char* word, char* filename)
{
    int maxi = 3;
    char* word_max = (char*)malloc (40);
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror(filename);
        errx(1, "The dictionnary wasn't find !");
    }
    char line[MAX_LINE_LENGTH] = {0};

    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        int val = levenshtein(word, line);
        if (line[strlen(line)-1] == '\n')
            line[strlen(line)-1] = '\0';

        if (strcmp(line, word) == 0)
        {
            strcpy(word_max,line);
            break;
        }
        if (maxi > val)
        {
            maxi = val;
            strcpy(word_max,line);
        }
    }
    if (!(strcmp(word_max,"")))
        return word;
    if (fclose(file))
        perror(filename);
    return word_max;
    free(word_max);
}

char* changingWordS(char* word, char* filename)
{
    int maxi = 0;
    int len1 = strlen(word);
    char* word_max = (char*)malloc (40);
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror(filename);
        errx(1, "The dictionnary wasn't find !");
    }
    char line[MAX_LINE_LENGTH] = {0};

    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        int val = similarity(word, line, len1, strlen(line));

        if (line[strlen(line)-1] == '\n')
            line[strlen(line)-1] = '\0';

        if (strcmp(line,word)== 0)
        {
            strcpy(word_max, line);
            break;
            return word;
        }

        if (maxi < val)
        {
            maxi = val;
            strcpy(word_max,line);
        }
    }

    if(!(strcmp(word_max,"")))
        return word;
    if (fclose(file))
        perror(filename);
    return word_max;
    free(word_max);
}



int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len + 1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y-1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return column[s1len];
}



void testTime(char* str1, char* filename)
{
    gettimeofday(&start, NULL);
    printf("Similarity algorithm computation time :\n");
    printf("The nearest word of %s is %s \n", str1, changingWordS(str1,filename));
    gettimeofday(&stop, NULL);
    printf("The operation took %lu micro s\n\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);


    gettimeofday(&start, NULL);
    printf("Levensthein algorithm computation time : \n");
    printf("The nearest word of %s is %s \n", str1 ,changingWordL(str1,filename));
    gettimeofday(&stop, NULL);
    printf("The operation took %lu micro s\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);


}




int testOrtho()
{
    testTime("victor", "../../../1-3000.txt");
    //char* test = "testa taste ceci est encore un test";
    //char* word = "test";
    //char* word1 = "tets";
    //similarity(test, word, 5, 4Bon );
    //sentenceTest(test, word);
    //printf(" The word is %s ", changingWordS("exploslon","../../../2-3000.txt"));
    //printf(" The word is %s ", changingWordL("exploslon","../../../1-3000.txt"));
    //printf(" The word is %f ", similarity("hello","zone",5,4));
    //printf("Levensthein distance is %i", levenshtein(word,word1));
    return 0;
}

