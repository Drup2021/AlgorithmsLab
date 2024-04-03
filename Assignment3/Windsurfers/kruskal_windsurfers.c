#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
typedef struct Node{
    int parent;
    int rank;
}Node;
typedef struct DisjointSets{
    struct Node **elements;
    int size;
}DisjointSets;
DisjointSets* createDisjointSet(int);
Node* makeSet();
int findSet(DisjointSets*,int);
void unionSet(DisjointSets*,int,int);

/// Graph related
typedef struct Edge{
    int src;
    int dest;
    int weight;
}Edge;
typedef struct Graph{
    struct Edge **edges;
    int numVertices;
    int numEdges;
}Graph;
Graph* creategraph(int,int);
void addEdge(Graph*,int,int,int);
void displayGraph(Graph*);

bool isCyclic(Graph*);
Graph* kruskal(Graph*);
int compare(const void*,const void*);

int main(){
    int src,dest,wt;
    Graph *g=creategraph(43,336);
    FILE *fp=fopen("moreno_beach.txt","r");
    if(!fp){
        printf("CANNOT OPEN FILE");
        return 1;
    }
    // for(int i=0;i<10;i++){
    //     fscanf(fp,"%d %d %d\n",&src,&dest,&wt);
    //     addEdge(g,src-1,dest-1,wt);
    // }
    while(fscanf(fp,"%d %d %d\n",&src,&dest,&wt)==3){
        addEdge(g,src-1,dest-1,wt);
    }
    
    displayGraph(g);
    // qsort(g->edges,g->numEdges,sizeof(Edge*),compare);
    // displayGraph(g);

    float start_time = clock();
    Graph* mst=kruskal(g);
    float end_time = clock();


    float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
    displayGraph(mst);

    int cost=0;
    for(int i=0;i<mst->numEdges;i++){
        cost+=mst->edges[i]->weight;
    }
    printf("\nCost = %d\n",cost);
    // if(isCyclic(g)){
    //     printf("\nCYCLE DETECTED");
    // }else{
    //     printf("\nNO CYCLE PRESENT");
    // }
    fclose(fp);
    printf("Total time taken using Kruskal's Algorithm : %f ms \n",time_taken);
    puts("\n\n===PROGRAM RUN SUCCESSFUL===");
    return 0;
}
Graph* kruskal(Graph* g){
    qsort(g->edges,g->numEdges,sizeof(Edge*),compare);
    // displayGraph(g);
    DisjointSets *ds=createDisjointSet(g->numVertices);
    Graph *mst=creategraph(g->numVertices,g->numVertices-1);
    int i=0,j=0;
    while(i<g->numVertices-1 && j<g->numEdges){
        int x=findSet(ds,g->edges[j]->src);
        int y=findSet(ds,g->edges[j]->dest);
        if(x==y){
            j++;
            continue;
        }
        unionSet(ds,x,y);
        addEdge(mst,g->edges[j]->src,g->edges[j]->dest,g->edges[j]->weight);
        i++; 
    }
    return mst;
}
int compare(const void* E1,const void* E2){
    Edge* e1=*(Edge**)E1;
    Edge* e2=*(Edge**)E2;
    // printf("\n%d ",e1->weight);
    // printf("%d",e2->weight);
    return e1->weight-e2->weight;
}
bool isCyclic(Graph* g){
    DisjointSets *ds=createDisjointSet(g->numVertices);
    for(int i=0;i<g->numEdges;i++){
        int x=findSet(ds,g->edges[i]->src);
        int y=findSet(ds,g->edges[i]->dest);
        if(x==y){
            return true;
        }
        unionSet(ds,x,y);
    }
    return false;
}
Graph* creategraph(int V,int E){
    Graph *g=(Graph*)malloc(sizeof(Graph));
    g->edges=(Edge**)malloc(sizeof(Edge)*E);
    g->numEdges=0;
    g->numVertices=V;
    return g;
}
void addEdge(Graph* g,int src,int dest,int wt){
    Edge *e=(Edge*)malloc(sizeof(Edge));
    e->src=src;
    e->dest=dest;
    e->weight=wt;
    g->edges[g->numEdges]=e;
    g->numEdges++;
}
void displayGraph(Graph* g){
    printf("\nS  D  Wt");
    for(int i=0;i<g->numEdges;i++){
        printf("\nEdge %3d : %3d  %3d  %3d",i+1,g->edges[i]->src,g->edges[i]->dest,g->edges[i]->weight);
    }
}
////////////////////
DisjointSets* createDisjointSet(int n){
    DisjointSets *ds=(DisjointSets*)malloc(sizeof(DisjointSets));
    ds->elements=(Node**)malloc(sizeof(Node*)*n);
    for(int i=0;i<n;i++){
        ds->elements[i]=makeSet();
    }
    ds->size=n;
    return ds;
}
Node* makeSet(){
    Node* s=(Node*)malloc(sizeof(Node));
    s->parent=-1;
    s->rank=0;
    return s;
}
int findSet(DisjointSets* ds,int x){
    if(ds->elements[x]->parent==-1){
        return x;
    }
    return ds->elements[x]->parent=findSet(ds,ds->elements[x]->parent);
}
void unionSet(DisjointSets* ds,int x,int y){
    if(ds->elements[x]->rank > ds->elements[y]->rank){
        ds->elements[y]->parent=x;
    }else if(ds->elements[x]->rank < ds->elements[y]->rank){
        ds->elements[x]->parent=y;
    }else{//equal rank
        ds->elements[x]->parent=y;
        ds->elements[y]->rank++;
    }
}




// 
    // printf("\n%p",g->edges);
    // printf("\n%p",g->edges[0]);