//part3.h
//written by Ziqing.Yan 17/s2
#include <stdio.h>

typedef struct NodeRep *List;
typedef struct ZeroRep *ZeroList;

//list for store element of Union set of urls and vertex in matrix
List newList();
void ListInsert(List L,char *url);
int Vexist(List L,char *url);
int NumofV(List L);
void printList(List L);
char *findVer(List L,int src);

//list for store '0''s position in matrix
ZeroList newZeroList();
void ZeroInsert(ZeroList L,int row,int column);
int Zeroexist(ZeroList L,int row,int column);
void printZeroList(ZeroList Z,List L,int size);
void printZeros(ZeroList Z);
int finalColumns(ZeroList Z,int src);
int NumofZeros(ZeroList Z);


