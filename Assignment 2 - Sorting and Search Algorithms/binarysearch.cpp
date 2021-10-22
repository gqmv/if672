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
 * Finds the index of the first appearance of the target in the array.
 *
 * @param array The array to be searched.
 * @param size The size of the array.
 * @param target The target to be searched for.
 *
 * @returns The index of the first appearance of the target.
 */
int binarySearch(long long int arr[], int size, long long int target)
{
    int left = 0;
    int right = size - 1;
    int middle;
    int target_index = -1;

    while (left <= right)
    {
        middle = (left + right) / 2;
        if (arr[middle] == target)
        {
            target_index = middle;
            right = middle - 1;
        }
        else if (arr[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return target_index;
}

int main()
{

    // This portion of code disables io sync, allowing the streams to buffer independently and consequently increasing performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Input aquisition
    int elements_count, queries_count;
    cin >> elements_count >> queries_count;

    long long int elements[elements_count];

    for (int i = 0; i < elements_count; i++)
    {
        cin >> elements[i];
    }

    for (int i = 0; i < queries_count; i++)
    {
        long long int query;
        cin >> query;
        int index = binarySearch(elements, elements_count, query);
        cout << index << "\n";
    }
}
