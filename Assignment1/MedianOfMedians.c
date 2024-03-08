#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int arr[], int initial, int final)
{
    for (int i = initial; i <= final; i++)
    {
        int value = arr[i];
        int pos = i - 1;
        while (pos >= initial && arr[pos] > value)
        {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = value;
    }
}

int give_median(int arr[], int initial, int final)
{
    insertion_sort(arr, initial, final);
    int mid = (initial + final) / 2;
    return arr[mid];
}

int median_of_median(int arr[], int arr_size, int divide_size)
{
    if (arr_size < divide_size)
    {
        int median = give_median(arr, 0, arr_size - 1);
        return median;
    }

    int no_full_group = arr_size / divide_size;
    int elements_in_last = arr_size % divide_size;

    int next_arr_size;

    if (elements_in_last == 0)
        next_arr_size = no_full_group;
    else
        next_arr_size = no_full_group + 1;

    int next_arr[next_arr_size];

    for (int i = 0; i < next_arr_size; i++)
    {
        if (i == arr_size)
            next_arr[i] = give_median(arr, divide_size * i, arr_size - 1);
        else
            next_arr[i] = give_median(arr, divide_size * i, divide_size * (i + 1) - 1);
    }

    return median_of_median(next_arr, next_arr_size, divide_size);
}
void getArray(int *arr,int n){
    for(int i = 0 ; i < n;i++){
        arr[i] = rand() % 100 + 1;
    }
}
int main()
{
    srand(time(0));

    int arr_size = 10;

    int arr[arr_size];

    
    getArray(arr,arr_size);
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int copy[arr_size];

    for (int i = 0; i < arr_size; i++)
        copy[i] = arr[i];

    printf("Median of Medians: %d\n", median_of_median(arr, arr_size, 5));
    printf("Direct: %d\n", give_median(copy, 0, arr_size - 1));

    return 0;
}