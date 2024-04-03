#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Graph{
    int **adjMatrix;
    int numVertices;
}Graph;
Graph* createGraph(int);
void addEdge(Graph*,int,int,int);
void displayAdjMatrix(Graph*);

void findMST(Graph*);
int selectMinVertex(int*,bool*,int);

int main(){
    int src,dest,wt,tmp;
    Graph *g=createGraph(3784);
    FILE *fp=fopen("bitcoin.txt","r");
    if(!fp){
        printf("CANNOT OPEN FILE");
        return 1;
    }
    // for(int i=0;i<10;i++){
    //     fscanf(fp,"%d %d %d\n",&src,&dest,&wt);
    //     addEdge(g,src-1,dest-1,wt);
    // }
    while(fscanf(fp,"%d %d %d %d\n",&src,&dest,&wt,&tmp)==4){
        if(wt < 0)wt *= -1;
        addEdge(g,src-1,dest-1,wt);
    }
    // displayAdjMatrix(g);
    float start_time = clock();
    findMST(g);
    float end_time = clock();

    float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
    
    printf("Total time taken using Prim's Algorithm : %f ms \n",time_taken);
    fclose(fp);
    // getch();
    return 0;
}
void findMST(Graph* g){
    int *parent=(int*)malloc(sizeof(int)*g->numVertices);
    int *value=(int*)malloc(sizeof(int)*g->numVertices);
    bool *setMST=(bool*)malloc(sizeof(bool)*g->numVertices);
    for(int i=0;i<g->numVertices;i++){
        value[i]=INT_MAX;
        setMST[i]=false;
    }
    parent[0]=-1;
    value[0]=0;
    for(int i=0;i<g->numVertices-1;i++){
        int u=selectMinVertex(value,setMST,g->numVertices);
        setMST[u]=true;
        for(int j=0;j<g->numVertices;j++){
            if(g->adjMatrix[u][j]!=0 && setMST[j]==false && g->adjMatrix[u][j]<value[j]){
                value[j]=g->adjMatrix[u][j];
                parent[j]=u;
            }
        }
    }
    for(int i=1;i<g->numVertices;i++){
        printf("\nEdge %3d : %3d %3d %3d",i,parent[i],i,g->adjMatrix[parent[i]][i]);
    }
    int cost=0;
    for(int i=1;i<g->numVertices;i++){
        cost+=g->adjMatrix[parent[i]][i];
    }
    printf("\nMinimum Spanning Tree Cost = %d\n",cost);

    free(parent);
    free(value);
    free(setMST);
}
int selectMinVertex(int* value,bool* setMST,int numVertices){
    int minimum=INT_MAX;
    int vertex;
    for(int i=0;i<numVertices;i++){
        if(setMST[i]==false && value[i]<minimum){
            vertex=i;
            minimum=value[i];
        }
    }
    return vertex;
}

Graph* createGraph(int v){
    Graph* g=(Graph*)malloc(sizeof(Graph));
    g->adjMatrix=(int**)malloc(sizeof(int*)*v);
    for(int i=0;i<v;i++){
        g->adjMatrix[i]=(int*)malloc(sizeof(int)*v);
        for(int j=0;j<v;j++){
            g->adjMatrix[i][j]=0;
        }
    }
    g->numVertices=v;
    return g;
}
void addEdge(Graph* g,int src,int dest,int weight){
    g->adjMatrix[src][dest]=weight;
    g->adjMatrix[dest][src]=weight;
}
void displayAdjMatrix(Graph* g){
    for(int i=0;i<g->numVertices;i++){
        for(int j=0;j<g->numVertices;j++){
            printf("%5d ",g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}