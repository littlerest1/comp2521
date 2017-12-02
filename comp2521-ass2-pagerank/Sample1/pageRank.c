#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include <math.h>
#include "graph.h"
#include "data.h"

#define MAXLINE 1000

static void pagerank(double, double, int, int, Graph);

int main(int argc, char *argv[]){
    if(argc != 4){
        printf("please insert damping factor,diffPR and maxiteration as argument\n");
        return 0;
    }

    int count = urlNum("collection.txt");
    Graph graph = newGraph(count);
    initVertex(graph, "collection.txt");
    
    FILE *URL;
    if((URL=fopen("collection.txt","r")) == NULL){
       printf("Can not open file\n");
       exit(1);
    }
    char URLS[MAXLINE];
    char newUR[MAXLINE];
    char gets[MAXLINE];
    char t[5] = ".txt";
    FILE *fp;
    while((fscanf(URL,"%s",URLS))==1){
        strcpy(gets,URLS);
        strcat(URLS,t);
        //URLS=urlxx.txt gets=urlxx;
        if((fp=fopen(URLS,"r"))==NULL){
            printf("Can not open urls.txt\n");
            exit(1);
        }else{
            //gets urls
            while((fscanf(fp,"%s",newUR)) == 1){
                if(strcmp(newUR,"#start") == 0 || strcmp(newUR,"Section-1") == 0)  continue;
                else if(strcmp(newUR,"#end") == 0)  break;
                else if(strcmp(newUR,gets) == 0)  continue;
                else  addEdge(graph,gets,newUR);          
            }
        }
    }
    //showGraph(graph,0);
    fclose(fp);
    fclose(URL);

    //calls pagerank 
    double df = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxiteration = atoi(argv[3]);  
    pagerank(df, diffPR, maxiteration, count, graph);

    disposeGraph(graph);
    return 0;
}



/*
calculates pagerank given by algorithm and 
outputs a list of urls in descending order of Weighted PageRank values (8sf)
to a file named pagerankList.txt
*/
static void pagerank(double df, double diffPR, int maxiteration, int maxV, Graph g){
    showGraph(g,0);
    double dv = (double) (1 - df)/ maxV;
    //calculate pr
    double pr[maxV], prOld[maxV];
    int i;
    for(i = 0; i <maxV; i++){
        pr[i] = 1.0 / maxV;
        prOld[i] = 1.0 / maxV;
    }
   
    int iteration = 0;
    double diff = diffPR;
    while(iteration < maxiteration && diff >= diffPR){
        diff=0.0;
        for(i = 0;i < maxV;i++){
            int m;
            double w = 0.0;
            for(m = 0;m < maxV;m++){
                if(isConnected(g, m, i)){
                   double win = Win(g, m, i);
                   double wout = Wout(g, m, i);
                   w += prOld[m] * win * wout;
                printf("w=%.7lf\tp[%d]=%.7lf win[%d][%d]=%.7lf\twout[%d][%d]=%.7lf\n",w,m,pr[m],m,i,win,m,i,wout);
                }  
            }

            pr[i] = dv + df * w;
        }
        int x;
        for(x = 0;x < maxV; x++){
            diff += fabs(prOld[x] - pr[x]);
            prOld[x] = pr[x];
        }
        printf("**********iteration %d**********\n",iteration);
        iteration++;
    }
   
    //sort and print pr in descending order (name of url/outlink of url/PR of url)
    double cmp = pr[0];
    int position = 0;
    FILE *PR = fopen("pagerankList.txt","w");;
    int y = 0;
    while(y < maxV){
        int x;
        for(x = 0;x < maxV; x++){
            if(pr[x] > cmp){
               cmp = pr[x];
               position = x;
            }
        }
        pr[position] = -1;
        fprintf(PR, "%s, %d, %.7lf\n", name(g, position), nOutlink(g, position), cmp);
        y++;
        cmp = 0;
        position = 0;
    }
    fclose(PR);
}
