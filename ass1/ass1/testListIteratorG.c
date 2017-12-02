#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

#define MAXARRAY 5
#define MAX  100

int getCommand(char *s);
int main(int argc,char *argv[]){
	char cmd[MAX];
    int  done=0;
    int k1=0,k2=0,k3=0,k4=0;
	int result;
  int *v1=NULL,*v2=NULL,*v3=NULL,*v4=NULL;

	IteratorG it1=IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);


	
	while (!done && getCommand(cmd)){
		switch(cmd[0]){
		case 'a':	    
			printf("Enter an integer to add: ");
			 scanf("%d",&k1);
			 result=add(it1,&k1);
		   printf("Inserting %d:%s \n",k1,(result==1 ? "Success":"Failed"));
		   break;
		case 'N':
		      result=hasNext(it1);
			  printf("%s\n",(result==1 ? "has next":"has no next"));
			  break;
		case 'P' :
		      result=hasPrevious(it1);
			  printf("%s\n",(result==1 ? "has prev":"has no prev"));
			  break;
		case 'n':
		    v1=(int *)next(it1);
			  printf("next value is:%d\n",*v1);
			  break;
		case 'p':
		    v2=(int *)previous(it1);
			  printf("prev value is:%d\n",*v2);
			  break;
		case 'd':
		     result=delete(it1);
			 printf("%s\n",(result==1 ? "Success":"Failed"));
			 break;
		case 's':			 
		    printf("Enter an integer to set: ");
			scanf("%d\n",&k2);
			result=set(it1,&k2);
			printf("Setting %d:%s \n",k2,(result==1 ? "Success":"Failed"));
			break;
		case 'F':
			printf("Enter an integer to find next: ");
			scanf("%d\n",&k3);
		  v3=(int *)findNext(it1,&k3);
			printf("Next value of %d is %d\n",k3,*v3);
			break;
		case 'f':
      printf("Enter an integer to find prev: ");
			scanf("%d\n",&k4);
		  v4=(int *)findPrevious(it1,&k4);
		  printf("%d\n",*v4);
			//printf("Previous value of %d is %d\n",k4,*v4);
			break;
		case 'r':
		     reset(it1);
		     break;
		case 'i':
		     freeIt(it1);
		     break;
    case 'q':
        done=1;
        break;
		case 'w':
			printf("\n%%%%%%------ positiveInt Set (1)  ------\n");
		  printf("\n\nAFTER Set values:  \n");
      SetTraverse(it1);
      printf("\n------------ -------------- ---------- \n\n");
      break;
    }
	}
	  return EXIT_SUCCESS;
}
int getCommand(char *buf)
{
	printf("> ");
	return (fgets(buf, MAX, stdin) != NULL);
}

