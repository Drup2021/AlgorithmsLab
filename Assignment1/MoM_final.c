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


int median_of_median(int arr[], int arr_size, int partition_size)
{
    if (arr_size < partition_size)
    {
        int median = give_median(arr, 0, arr_size - 1);
        return median;
    }

    int no_full_group = arr_size / partition_size;
    int elements_in_last = arr_size % partition_size;

    int next_arr_size;

    if (elements_in_last == 0)
        next_arr_size = no_full_group;
    else
        next_arr_size = no_full_group + 1;

    int next_arr[next_arr_size];

    for (int i = 0; i < next_arr_size; i++)
    {
        if (i == next_arr_size - 1)
            next_arr[i] = give_median(arr, partition_size * i, arr_size - 1);
        else
            next_arr[i] = give_median(arr, partition_size * i, partition_size * (i + 1) - 1);
    }

    return median_of_median(next_arr, next_arr_size, partition_size);
}

int main()
{
    srand(time(0));

    int arr_size = 10000;
    int iterations = 10;
    float start_time, end_time, time_taken;
    double avg_time;

    FILE *fout = fopen("MedianOfMedians_obs.txt", "w");

    int partition_size;

    int arr[arr_size];

    for (int obs_counter = 0; obs_counter <= 1000; obs_counter++)
    {
        partition_size = 2 * obs_counter + 3;
        avg_time = 0;
        float acc = 0;
        int correct = 0;

        for (int i = 0; i < iterations; i++)
        {
            for (int j = 0; j < arr_size; j++)
                arr[j] = rand() % 101;

            start_time = clock();
            int mom_median = median_of_median(arr, arr_size, partition_size);
            end_time = clock();
            int direct_median = give_median(arr,0,arr_size-1);
            printf("%d %d\n",mom_median,direct_median);
            if(direct_median == mom_median) correct++;
            time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
            avg_time += time_taken;
        }
        avg_time = avg_time / iterations;

        printf("partition_size: %4d avg_time: %3.4f ms Correct : %d\n", partition_size, avg_time,correct);
        fprintf(fout, "%d, %f\n", partition_size, avg_time);
    }

    fclose(fout);
    return 0;
}