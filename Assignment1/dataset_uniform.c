#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    FILE* fptr;
    char file_name[50] = "UniformDistribution.txt";
    srand(time(NULL));
    fptr = fopen(file_name, "w");
    int n = 10000;
    int *arr = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        arr[i] = rand() % 100 + 1;
        fprintf(fptr,"%d\n",arr[i]);
    }
    free(arr);
    fclose(fptr);
}




