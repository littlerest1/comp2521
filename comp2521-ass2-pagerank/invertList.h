//Written by Huiyue Zhang 2017 s2

typedef struct StructureRep *Structure;

//creates a new empty linked list
Structure newS();
//frees entire linked list
void freeS(Structure S);
//insert word and url into the list
void insertS(Structure S, char *word, char *url);
//prints the linked list S into the file fp
void printS(FILE *fp, Structure S);
void findCommon(Structure S);
