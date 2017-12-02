//written by Ziqing.yan 17/s2
//functions for matrix and algorithm operation
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "part3.h"

//part1: for store union set of urls 
typedef struct Node *node;
typedef struct Node{
	    char *url;
		node next;
}Node;
typedef struct NodeRep{
	int nV;
	node first;
	node last;
}NodeRep;

List newList(){
	 List L = malloc(sizeof(NodeRep));
	 assert(L);
	 L->nV = 0;
	 L->first = L->last = NULL;
	 return L;
}

node newNode(char *url){
	 assert(url);
	 node new = malloc(sizeof(Node));
	 assert(new);
	 new->url = (char*)malloc(sizeof(strlen(url)+1));
	 strcpy(new->url,url);
	 new->next = NULL;
	 return new;
}

void ListInsert(List L,char *url){
	 node n;
	 n = newNode(url);
	 assert(L);
	 assert(n);
	 
	 if(L->first == NULL){
		L->first = L->last = n;
		L->nV++;
	 }
	 else{
		  if(Vexist(L,url)==1)return;
		  L->last->next = n;
		  L->last = n;
		  L->nV++;
	 }
}
//if url are already in list skip this link
int Vexist(List L,char *url){
	assert(L);
	assert(L->first);
	node src = L->first;
	while(src != NULL){
		  if(strcmp(src->url,url) == 0){
			  return 1;
		  }
		  src = src->next;
	}
	return 0;
}

int NumofV(List L){
	return L->nV;
}
//debug func.
void printList(List L){
	 node src = L->first;
	 while(src != NULL){
		 printf("%s\t",src->url);
	     src = src->next;
	 }
	 printf("\n");
	 return;
}
//find the name of the vertex
char *findVer(List L,int src){
	node start = L->first;
	int k = 0;
	while(k < src){
		 start = start->next;
		 k++;
	}
	return start->url;
}
//part 2:store '0''s position in the list
typedef  struct Zero *zeros;
typedef struct Zero{
		int row;
		int column;
		zeros next;
}Zero;
	
struct ZeroRep{
		zeros first;
		zeros last;
		int nZ;
}ZeroRep;

ZeroList newZeroList(){
     ZeroList L = malloc(sizeof(ZeroRep));
	 assert(L);
	 L->first = L->last = NULL;
	 L->nZ = 0;
	 return L;
}

zeros newZeros(int row,int column){
      zeros new = malloc(sizeof(Zero));
	  assert(new);
	  new->row = row;
	  new->column = column;
	  new->next = NULL;
	  return new;
}

void ZeroInsert(ZeroList L,int row,int column){
	 zeros n;
	 n = newZeros(row,column);
	 assert(L);
	 assert(n);
	 
	 if(L->first == NULL){
		L->first = L->last = n;
	 }
	 else{
		  if(Zeroexist(L,row,column)==1)return;
		  L->last->next = n;
		  L->last = n;
	 }
	 L->nZ++;
}
//cuz only one zero's position will store in each row
int Zeroexist(ZeroList L,int row,int column){
	zeros n = L->first;
	while(n != NULL){
		if(n->row == row && n->column == column)return 1;
		n = n->next;
	}
	return 0;
}
//print out the urls by position order
void printZeroList(ZeroList Z,List L,int size){
	 assert(Z->first);
	 int count = size;
	 int row = 1;
	 while(count != 0){
		zeros n = Z->first;
		while(n != NULL){
			if(n->row == row){
				 char *p = findVer(L,n->column-1);
				 printf("%s\n",p);
				 row ++;
				 count --;
			}
			n = n->next;
		}
	 }
}
//debug func.
void printZeros(ZeroList Z){
	 assert(Z->first);
	 zeros n = Z->first;
	 while(n != NULL){
		 printf("zero at [%d][%d]\n",n->row,n->column);
		 n = n->next;
	 }
}
//return the zero's position(use zero's row to find its column)
int finalColumns(ZeroList Z,int src){
	 assert(Z->first);
	 zeros n = Z->first;
	 
	 while(n != NULL){
		 if(n->row == src)return n->column;
	     n = n->next;
	 }
	 return 0;
}
//return num of zeros if num of zeros equal to the numbers of vertex operation finished
int NumofZeros(ZeroList Z){
	return Z->nZ;
}
