//Written by Huiyue Zhang 2017 s2

#define MAX_CHAR 1000
//gets number of links in a given file
int urlNum(char *fileName);
//gets all the url index in a given file
int *urlArray(char *fileName, int max);
//free memory of array
void freeArray(int * array);

//normalize a string
void normalise(char *word);