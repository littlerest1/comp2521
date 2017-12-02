//Written by Huiyue Zhang 2017 s2

/*OUTLINE:
Write a simple search engine in file searchPagerank.c 
that given search terms (words) as commandline arguments, 
finds pages with one or more search terms 
and outputs (to stdout) top 30 pages in descending order of
number of search terms found and then within each group, 
descending order of Weighted PageRank. 
If number of matches are less than 30, output all of them.
Your program must use data available in two files 
invertedIndex.txt and pagerankList.txt, 
and must derive result from them. 
We will test this program independently to 
your solutions for "A" and "B".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "invertList.h"


#define MAX_PAGE 30

//need?
#define TXT 5
#define URL 4
#define INT_SIZE 14
#define MAX_FILE_NAME 24


int main(int argc, char *argv[]){
	if(argc == 1){
		printf("Usage: %s word1 word2\n", argv[0]);
		return 0;
	}
	


	Structure S = newS();

	int i;
	for(i = 1; i < argc; i++){
		normalise(argv[i]);

		FILE *fp = fopen("invertedIndex.txt", "r");
		if(fp == NULL){
			fprintf(stderr, "invertedIndex.txt couldn't be opened.\n");
			return 0;
		}

		char find[MAX_CHAR];
		char *f;
		//find word in txt
		while(fscanf(fp,"%s", find) == 1){
			if(strcmp(find, argv[i]) == 0){
			//found word
				//insert its urls
				while(fscanf(fp," %s ", find) == 1){
					if((f = strstr(find, "url")))  insertS(S, argv[i], f);	
					else  break;
				}
				break;
			}else{
			//word not found, try next line
				fscanf(fp,"%*[^\n]");
			}

		}

	}
	//for debugging
	printS(stdout, S);



	//search term = argc - 1
	int st = argc - 1;
	printf("Search term = %d\n", st);
    findCommon(S);
	
	
	
	freeS(S);

	return 0;
}


