#include <stdlib.h>

int compare_strings(char *s1, char *s2)
{
    size_t i = 0;

    while(s1[i] != '\0')
    {
        if(s2[i] != '\0')
        {
            if(s1[i] == s2[i])
                i++;
            else
                return 0;
        }
        else
            return 0;
    }
    if(s2[i] != '\0')
        return 0;

    return 1;
}
