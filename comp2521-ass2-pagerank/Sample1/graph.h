// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015
//from lab08 exercise

#ifndef GRAPH_H
#define GRAPH_H  

typedef struct GraphRep *Graph;

// Function signatures

Graph newGraph(int);
int   urlNum(char *);
void initVertex(Graph g,char *);
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
int   isConnected(Graph, int, int);
void  showGraph(Graph,int);
double Win(Graph,int,int);
double Wout(Graph,int,int);
int   nInlink(Graph,int);
int   nOutlink(Graph,int);
char  *name(Graph,int);

#endif

