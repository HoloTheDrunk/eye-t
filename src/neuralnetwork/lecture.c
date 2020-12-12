#include "lecture.h"

Matrix* ReadFileMatrix(char* filename)
{
    Matrix* result = NewMatrix(28,28);
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror(filename);
        errx(1, "The training file wasn't find !");
    }
    char line[MAX_LINE_LENGTH+2] = {0};
    int j = 0;
    while (fgets(line, MAX_LINE_LENGTH+2, file) && j < MAX_LINE_LENGTH-1)
    {
        int i = 0;
        int index = 0;
        while (line[index] != '\0' && i < MAX_LINE_LENGTH)
        {
            SetElement(result, i, j, line[i]-'0');
            i++;
            index++;

        }
        j++;
    }
    if (fclose(file))
        perror(filename);

    return result;
}



