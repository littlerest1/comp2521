//Written by Huiyue Zhang 2017 s2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "data.h"


//gets number of links in a given file
int urlNum(char *fileName){
    FILE *fp = fopen(fileName, "r");
    assert(fp);

    int count = 0;
    char find[MAX_CHAR];
    while(fscanf(fp, " %s ", find) == 1){
        if(strstr(find, "url")) count ++;
        if(strcmp(find, "#end") == 0) break;
    }
    fclose(fp);
    return count;
}

//gets all the url index in a given file
int *urlArray(char *fileName, int max){
    if (fileName == NULL || max <= 0)  return NULL;

    FILE *fp = fopen(fileName, "r");
    assert(fp);
    int *urlA = calloc(max, sizeof(int));
    assert(urlA);

    int i=0;
    char find[MAX_CHAR];
    char * s;
    while(fscanf(fp, " %s ", find) == 1 && i < max){

        if((s = strstr(find, "url"))){
            //get the url number with offset of 3
            urlA[i] = atoi(s+3); 
            i ++;   
        }
        //shouldnt need this line because of max
        //if(strcmp(find, "#end") == 0)  break;

    }
    fclose(fp);
    return urlA;
}

//free memory of array
void freeArray(int * array){
	free(array);
}



//converts uppercase to lowercase
static void lower(char *word, int length){
    if(word == NULL) return;
    int i;
    for(i = 0; i < length; i ++){
        if(isupper(word[i]))  word[i] = tolower(word[i]);
    }
}

//remove '.' (dot), ',' (comma), ';' (semicolon), ? (question mark)
void normalise(char *word){
    if(word == NULL) return;
    int length = strlen(word);
    //convert uppercase to lowercase
    lower(word, length);

    int i, j = 0;
    for(i = 0; i < length; i ++){
        if(isalnum(word[i])){
            word[j] = word[i];
            j ++;
        }
    }
    word[j] = '\0';
}



