#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>



int main()
{
 

    FILE *fout = fopen("normalized_normal_distribution222.txt", "w");
    int n = 10000;
    float arr[n];
   
    srand(time(0));

    float t[n];
    float maxi = 0;
    float mini = 101;  
    for(int i = 0;i < n;i++){
        int s = 0;
        for(int j = 0; j < 12;j++)
        s += rand() % 100 + 1;
        t[i] = s/12;
        if(t[i] > maxi) maxi = t[i];
        if(t[i] < mini) mini = t[i];
    }

    for(int i=0;i<n;i++){
        arr[i] = ((float)t[i] - mini)/(maxi - mini);
        fprintf(fout,"%f\n",arr[i]);
    }
    fclose(fout);
    return 0;
}