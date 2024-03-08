#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void mySwap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high, int *cnt)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int curr = low; curr <= high; curr++)
    {
        if (arr[curr] < pivot)
        {
            i++;
            mySwap(&arr[i], &arr[curr]);
            (*cnt)++;
        }
    }
    mySwap(&arr[i + 1], &arr[high]);
    (*cnt)++;
    return (i + 1);
}

int randomized_partition(int *arr, int initial, int final, int *count)
{
    int i = rand() % (final - initial) + initial;
    mySwap(&arr[final], &arr[i]);
    return partition(arr, initial, final, count);
}

void quickSort(int *arr, int initial, int final, int *count)
{
    if (initial < final)
    {
        int pos_of_pivot = randomized_partition(arr, initial, final, count);
        quickSort(arr, initial, pos_of_pivot, count);
        quickSort(arr, pos_of_pivot + 1, final, count);
    }
}

int checkForCorrectness(int *arr, int n)
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

void getArray(int *arr, int n)
{
    // for(int i=0;i<n;i++){
    //     arr[i] = rand() % 100 + 1;
    // }

    for(int i=0;i<n;i++){
        int s=0;
        for(int j=0;j<12;j++){
            s += rand() % 100 + 1;
        }
        arr[i] = s/12; 
    }
}
int main()
{
    FILE *fptr = fopen("rqs_normal.txt", "w");
    int n = 2;
    int power = 16;
    int runs = 20;
    for (int i = 0; i < power; i++)
    {

        long total_cnt = 0;
        float total_time = 0;

        for (int j = 0; j < runs; j++)
        {
            int *arr;
            if(j == 0)
            arr = (int *)malloc(n * sizeof(int));
            int cnt = 0;
            getArray(arr, n);

            float start_time = clock();
            quickSort(arr, 0, n - 1, &cnt);
            float end_time = clock();

            total_cnt += cnt;

            float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
            total_time += time_taken;

            if (checkForCorrectness(arr, n))
            {
                printf("\nNum = %d Run %d: %d comparisons, %0.4f ms", n, j + 1, cnt, time_taken);
            }
            else
            {
                printf("\nArray Not Sorted");
                break;
            }
        }
        float avg_time = total_time / runs;
        long avg_count = total_cnt / runs;
        printf("\nN: %d, Avg time: %0.4f, Avg comparisons: %ld\n", n, avg_time, avg_count);
        fprintf(fptr,"%d, %0.4f, %ld\n",n,avg_time,avg_count);
        n *= 2;
    }
    return 0;
}