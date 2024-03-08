#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

using namespace std;

void insertionSort(vector<float> &arr, int n)
{
    float i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(float arr[],int n,vector<int> &bucketSize){
    
    vector<vector<float>> bucket(n,vector<float>());

    for(int i = 0;i < n;i++){
        int index = arr[i] * n;
        if(index >= n){
            bucket[n-1].push_back(arr[i]);
        }
        else{
            bucket[index].push_back(arr[i]);
        }
    }
    
    for(int i = 0; i < n ;i++){
        if(!bucket[i].empty())
        insertionSort(bucket[i],bucket[i].size());
    }
    int k = 0;
    for(int i = 0 ; i < n;i++){
        for(int j = 0; j < bucket[i].size(); j++){
            arr[k++] = bucket[i][j];
        }
    }
    for(int i = 0 ; i < n;i++){
        bucketSize[i] = bucket[i].size();
    }
    
}

void getArray(float* arr, int n){
    srand(time(0));
    float t[n];
    float maxi = 0;
    float mini = 100;  
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
    }
}

int checkForCorrectness(float *arr, int n)
{
    int correct = 1;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            correct = 0;
            break;
        }
    }
    return correct;
}
void printArray(float* arr,int n){
    for(int i=0;i<n;i++){
        printf("%0.4f ",arr[i]);
    }
    printf("\n");
}
int main(){

    int n = 2;
    int iterations = 20;
    int power = 16;
    FILE *fptr = fopen("test_normal.txt", "w");
    for(int i=0;i < power;i++){
        float total_time = 0;
        for(int j =0 ; j < iterations;j++){
            float arr[n];
            vector<int> bucketSize(n,0);
            getArray(arr,n);
            float start_time = clock();
            bucketSort(arr,n,bucketSize);
            float end_time = clock();

            //for average bucket size
            int s = 0,s2 = 0;
            for(int k=0;k<bucketSize.size();k++){
                s += bucketSize[k];
                s2 += bucketSize[k] * bucketSize[k];
            }

            float avg_bucket_size = (float)s / n;
            float e_n2 = (float)s2 / n;
            float var = sqrt(abs(e_n2 - avg_bucket_size*avg_bucket_size));
            float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
            if(checkForCorrectness(arr,n)){
                printf("n = %d Iteration %d: , %0.4f ms Avg_Bucket_size : %f E(n2) : %f Var : %f\n", n, j +
                1,time_taken,avg_bucket_size,e_n2,var);
                // printArray(arr,n);
            }else{
                printf("The array is not sorted\n");
            }
            total_time += time_taken;
        }
        float average_time = total_time / iterations;
        printf("n = %d Average time taken : %0.4f\n\n",n,average_time);
        fprintf(fptr, "%d, %0.4f\n", n,average_time);
        n *= 2;
    }
}
