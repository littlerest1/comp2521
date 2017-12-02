#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

typedef struct Node {
      void *data;
      struct Node *next;
      struct Node *prev;
} Node;
//struct a node which includes data,pointer to next and prev
typedef struct IteratorGRep {
	Node  *first;
	Node  *last;
  Node  *elems1;
  Node  *elems2;
  Node  *elems3;
	ElmNewFp    newFp;
	ElmCompareFp cmpFp;
	ElmFreeFp    freeFp; 
} IteratorGRep;
//struct a rep point to first last element and other function as well as
//the ^(1 is ^next,2 is ^prev,3 is p/n return element)
int isValid(IteratorG it){
	  if(it==NULL){
	 	    return 0;
	  }
	 	return 1;
}
//checkout the list is it valid
IteratorG IteratorGNew(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp)
{
	IteratorG new;
	
	if ((new = malloc(sizeof(struct IteratorGRep))) == NULL) {
	  fprintf(stderr, "Error!!  .... \n"); 
	}
  assert(new!=NULL);
    
	new->first=NULL;
	new->last=NULL;
	new->elems1=NULL;
	new->elems2=NULL;
	new->elems3=NULL;
	new->cmpFp = cmpFp;
	new->newFp = newFp;
	new->freeFp = freeFp;

	return new;
}
//create a new list with initiallized
int  add(IteratorG it, void *vp)
{
	assert(isValid(it));
// check the state of list
  struct Node *curr;
  struct Node *next;
  Node *new;
	
	if((new=malloc(sizeof(Node)))==NULL){
		return 0;
	}
//create a new node
	new->data=it->newFp(vp);
//add the data by using given function
	new->next=NULL;
	new->prev=NULL;
	
  if(it->first==NULL){
	   it->first=new;
	   it->last=it->first;
	   it->elems1=it->last;
	   return 1;
	}	//NUll case
	else{ 
       if(it->elems1==it->last){
		    new->prev=it->last;
		    it->last->next=new;
		    it->last=new;
		    it->elems1=it->last;
		    return 1;
		  }//last case need to change the last pointer
		  else{
		        curr=it->elems1;
		        next=it->elems2;
   		      new->next=next;
   		      new->prev=curr;
   		      curr->next=new;
   		      next->prev=new;
            it->elems1=new;
		      return 1;
		  }//else case which in the middle,change the ^ pointer
  }
	
  return 0;
		  
}
int  hasNext(IteratorG it)
{
	int f=1;
	int b=1;
	struct Node *first=it->elems2;
	struct Node *sec=it->elems1;
//first=^next, sec=^prev
	while(first!=NULL){
		  first=first->next;
		  f++;
  }
	//go!
	while(sec!=NULL){
		  sec=sec->prev;
		  b++;
  }
	//go!
	if(f>b){
		return 1;
  }
  //compare and return
  return 0;
}
int  hasPrevious(IteratorG it)
{
  int f=1;
	int b=1;
	struct Node *first=it->elems2;
	struct Node *sec=it->elems1;
	
	while(first!=NULL){
		  first=first->next;
		  f++;
  }
	
	while(sec!=NULL){
		  sec=sec->prev;
		  b++;
  }
	
	if(b>f){
		return 1;
  }
		 
  return 0;
}//same as hasnext
void *next(IteratorG it)
{
  void *data;	
   
  if(it->elems2==NULL){
     return NULL;
  }
//no next value, ^ next is null  
  data=it->elems2->data;
	it->elems1=it->elems2;
	it->elems3=it->elems2;
	it->elems2=it->elems2->next;
//has next value which point by elems2,store the value and change position	further change elem3 which might be use in delete stage
  return data;

}
void *previous(IteratorG it)
{
   void *data;

   if(it->elems1==NULL){
      return NULL;
   }
	 
	 data = it->elems1->data;
	 it->elems3=it->elems1;
	 it->elems2=it->elems1;	
   it->elems1=it->elems1->prev;		   

	 return data;

}//same as next
int  delete(IteratorG it)
{
	assert(isValid(it));
	if(it->elems3==NULL){
	   return 0;
	}
	
	struct Node *curr=NULL;
	struct Node *next=NULL;
	struct Node *de=it->elems3;
//must delete the element return by p/n fp/fn which pt by elems3

	if(it->first==it->last){
		  curr=it->first;
		  it->first=NULL;
		  it->last=NULL;
		  it->elems1=NULL;
		  it->elems2=NULL;
		  it->elems3=NULL;
	    it->freeFp(curr->data);
	    free(curr);
		  return 1;
  }//delete the only elem
	else if(it->last==de){
	      curr=de->prev;
	      curr->next=NULL;
		    it->last=curr;
			  it->elems1=it->last;
			  it->elems2=NULL;
			  it->elems3=NULL;
			  it->freeFp(de->data);
			  free(de);
			  return 1;
	}//last case
	else if(it->first==de){
		   it->first=de->next;
		   it->elems1=NULL;
		   it->elems3=NULL;
		   it->elems2=it->first;
		   it->freeFp(de->data);
		   free(de);
		   return 1;
	}//first case
	else if(de==it->elems1){
	     curr=it->elems1->prev;
	     next=it->elems1->next;
	     next->prev=curr;
	     curr->next=next;
	     it->elems1=curr;
	     it->elems3=NULL;
	     it->freeFp(de->data);
	     free(de);
	     return 1;
	}//elem return by p/fp prev pt need to be change
	else if(de==it->elems2){
	     curr=it->elems2->prev;
	     next=it->elems2->next;
	     next->prev=curr;
	     curr->next=next;
	     it->elems2=curr;
	     it->elems3=NULL;
	     it->freeFp(de->data);
	     free(de);
	     return 1;
	}//elem return by n/fn next pt need to be change
	return 0;
}
int  set(IteratorG it, void *vp)
{
	assert(isValid(it));
	Node *curr=it->elems3; 
//check pt return by fp/p,fn/n
  if(curr!=NULL){
	     it->freeFp(curr->data);
	     curr->data=it->newFp(vp);
	     it->elems3=NULL;
	     return 1;
	}
	//change data
	return 0;
  
}
void *findNext(IteratorG it, void *vp)
{
	assert(isValid(it));
  Node *curr=it->elems2;
	
	while(curr!=NULL){
		  if(it->cmpFp(curr->data,vp)==0){
			  it->elems1=curr;
			  it->elems3=curr->next;
			  it->elems2=curr->next;
			  return it->elems2->data;
	    }
      curr=curr->next;
   }
//use function strcmp to find out the pt,then change position and return pt
	return NULL;
}
void *findPrevious(IteratorG it, void *vp)
{
  assert(isValid(it));
  Node *curr=it->elems1;
	
	while(curr!=NULL){
		  if(it->cmpFp(curr->data,vp)==0){
			  it->elems2=curr;
			  it->elems3=curr->prev;
			  it->elems1=curr->prev;
			  return it->elems1->data;
	    }
      curr=curr->prev;
  }
  //same as fn
	return NULL;
}
void reset(IteratorG it)
{
	assert(isValid(it));
	it->elems1=NULL;
	it->elems2=it->first;
//reset the position
}

void freeIt(IteratorG it){
    assert(it!=NULL);
    assert(it->first!=NULL);
    struct Node *curr=NULL;
    struct Node *temp=it->first;
//free all the Node from the beginning    
  while(temp!=NULL){ 
    if(it->first==it->last){
		    curr=it->first;
		    it->first=NULL;
		    it->last=NULL;
		    it->elems1=NULL;
		    it->elems2=NULL;
		    it->elems3=NULL;
		    temp=NULL;
		    it->freeFp(curr->data);
	      free(curr);
    }//only node case
    else{
       curr=it->first;
		   it->first=curr->next;
		   it->elems1=NULL;
		   it->elems3=NULL;
		   it->elems2=it->first;
		   temp=it->first;
		   it->freeFp(curr->data);
		   free(curr);
    }//other case
  }
}
/*void SetTraverse(IteratorG it){

	assert(isValid(it));

  struct Node *curr=it->first;
	if(it->first==NULL){
	  return;
	}
	else{	
	  while(curr!=NULL){
	        printf("%d, ",*((int*)curr->data));
	        curr=curr->next;
	  }
    
    
	}
	return;
}


*/

