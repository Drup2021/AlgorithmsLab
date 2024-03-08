#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    FILE* fptr;
    char file_name[50] = "NormalDistribution.txt";
    srand(time(NULL));
    fptr = fopen(file_name, "w");
    int n = 10000;
    int *arr = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        int s = 0;
        for(int j=0;j<12;j++){
            s += rand() % 100 + 1 ;
        }
        arr[i] = s / 12;
        fprintf(fptr,"%d\n",arr[i]);
    }
    free(arr);
    fclose(fptr);
    
}