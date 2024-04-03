#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent, rank;
};

int find(Subset subsets[], int i) {
    // finds the ultimate parent
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

void kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), compareEdges);

    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> result;
    int e = 0;
    for (Edge next_edge : edges) {
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            e+= next_edge.weight;
        }
    }
    int components = 0;
    for(int i=0;i<V;i++){
        if(subsets[i].parent == i) components++;
    }

    delete[] subsets;
    long long mstweight = 0; 
    cout << "Edges in the MST are: " << endl;
    for (Edge edge : result) {
        mstweight += edge.weight;
        cout << edge.src << " - " << edge.dest << " (weight: " << edge.weight << ")" << endl;
    }



    cout<<"MST weight : "<<mstweight<<endl;
    cout<<"The number of connected components : "<<components<<endl;
}

int main() {
    vector<Edge> edges;
    int max_node = -1;

    ifstream file("lesmiserables.txt");
    if (file.is_open()) {
        int src, dest,wt,tmp;
        while (file >> src >> dest >> wt) {
            if(wt < 0) wt *= -1;
            edges.push_back({src, dest,wt});
            max_node = max(max_node, max(src, dest));
        }
        file.close();
    } else {
        cerr << "Unable to open the file." << endl;
        return 1;
    }

    int V = max_node + 1;

    float start = clock();
    kruskalMST(edges, V);
    float end = clock();



    float duration = (end - start) * 1000 / CLOCKS_PER_SEC;
    cout << "Time taken by Kruskal's MST algorithm: " << duration << " ms" << endl;


    return 0;
}