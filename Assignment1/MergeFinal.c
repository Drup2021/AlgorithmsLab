#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r, int *cnt) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0;j = 0;k = l;  
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            (*cnt)++;
        } else {
            arr[k] = R[j];
            j++;
            (*cnt)++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        (*cnt)++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        (*cnt)++;
    }
}

void mergeSort(int arr[], int l, int r, int *cnt) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, cnt);
        mergeSort(arr, m + 1, r, cnt);

        merge(arr, l, m, r, cnt);
    }
}



int checkForCorrectness(int *arr, int n) {
    int correct = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            return 0;
        }
    }
    return 1;
}

void getArray(int *arr, int n) {
    srand(time(0));
    for(int i=0;i<n;i++){
        int s=0;
        for(int j=0;j<12;j++){
            s += rand() % 100 + 1;
        }
        arr[i] = s/12; 
    }
}

int main() {
    int n = 2;
    int power = 16;
    int iterations = 20;


    for (int i = 0; i < power; i++) {
        long total_cnt = 0;
        float total_time = 0;

        for (int j = 0; j < iterations; j++) {
            int *arr = (int *)malloc(n * sizeof(int));
            int cnt = 0;
            getArray(arr, n);

            float start_time = clock();
            mergeSort(arr, 0, n - 1, &cnt);
            float end_time = clock();

            total_cnt += cnt;

            float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
            total_time += time_taken;

            if (checkForCorrectness(arr, n)) {
                printf("\nNum = %d Run %d: %d comparisons, %0.4f ms", n, j +
                1, cnt, time_taken);
            } else {
                printf("\nArray Not Sorted");
                break;
            }
        }
        float avg_time = total_time / iterations;
        long avg_count = total_cnt / iterations;
        printf("\nN: %d, Avg time: %0.4f, Avg count: %ld\n", n, avg_time,
        avg_count);
        n *= 2;
    }
    return 0;
}