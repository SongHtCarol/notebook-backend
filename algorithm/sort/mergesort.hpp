#pragma once

#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"

void merge(std::vector<int> &arr, int left, int right)
{

    std::cout << "left=" << left << "right=" << right << std::endl;

    if (left >= right)
        return;

    std::cout << "before:";
    print(arr);

    int mid = (left + right) / 2;
    merge(arr, left, mid);
    merge(arr, mid + 1, right);

    // 对已经排序好的两个区间合并
    int j = left;
    for (int i = mid + 1; i <= right; i++)
    {

        while (arr[i] > arr[j] && j <= right)
            j++;

        if (j >= i)
            break;

        int tmp = arr[i];
        int x = i;
        while (x > j)
        {
            arr[x] = arr[x - 1];
            x--;
        }

        arr[j] = tmp;
    }
    std::cout << "after:";
    print(arr);
}

void mergeSort(std::vector<int> &arr)
{
    merge(arr, 0, arr.size() - 1);
}
