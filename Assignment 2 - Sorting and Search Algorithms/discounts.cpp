/**
 * Except where otherwise noted, the following code is licensed under the Creative Commons Attribution 4.0 International license (CC BY 4.0):
 * http://creativecommons.org/licenses/by/4.0/
 * Copyright 2021 Gabriel Vieira
 * https://github.com/gqmv
 *
 * Whenever using, citing, or modifying this work, be sure to include a copy of the license and this notice.
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * Merges two parts of the array (which are independently sorted) into one larger part (which does not mean the final array will be necessarily sorted).
 *
 * @param arr The array that contains the two parts to be merged.
 * @param left The left index of the first part.
 * @param middle The middle index that separates the two parts.
 * @param right The right index of the second part.
 */
void merge(int arr[], int left, int middle, int right)
{
    int left_size = middle - left + 1;
    int right_size = right - middle;

    int left_array[left_size], right_array[right_size];

    // Coppies data from the main array into the sub-arrays
    for (int i = 0; i < left_size; i++)
        left_array[i] = arr[left + i];
    for (int j = 0; j < right_size; j++)
        right_array[j] = arr[middle + 1 + j];

    // Iterates through both arrays until one of them is over
    int left_index = 0;
    int right_index = 0;
    int arr_index = left;
    while (left_index < left_size && right_index < right_size)
    {
        if (left_array[left_index] <= right_array[right_index])
        {
            arr[arr_index] = left_array[left_index];
            left_index++;
        }
        else
        {
            arr[arr_index] = right_array[right_index];
            right_index++;
        }
        arr_index++;
    }

    // Appends the rest of the elements of the sub-array
    while (left_index < left_size)
    {
        arr[arr_index] = left_array[left_index];
        left_index++;
        arr_index++;
    }

    while (right_index < right_size)
    {
        arr[arr_index] = right_array[right_index];
        right_index++;
        arr_index++;
    }
}

/**
 * Sorts the array using the well known merge sort algorithm.
 *
 * @param arr The array to be sorted.
 * @param left The left index of the array. (If this is not a recursive call, this should be 0.)
 * @param right The right index of the array. (If this is not a recursive call, this should be the size of the array - 1.)
 */
void mergesort(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        mergesort(arr, left, middle);
        mergesort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

int main()
{
    // This portion of code disables io sync, allowing the streams to buffer independently and consequently increasing performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Acquires the inputs and calculates the sum of the prices of all bars
    int bars_count;
    cin >> bars_count;

    int bars[bars_count];
    long long int sum = 0;
    for (int i = 0; i < bars_count; i++)
    {
        cin >> bars[i];
        sum += bars[i];
    }

    mergesort(bars, 0, bars_count - 1);

    int discounts_count;
    cin >> discounts_count;

    for (int i = 0; i < discounts_count; i++)
    {
        int discount;
        cin >> discount;

        long long int sum_discount = sum - bars[bars_count - (discount)];
        cout << sum_discount << "\n";
    }
}