#pragma once

#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"

void quickSortDfs(std::vector<int> &arr, int left, int right)
{

    if (left >= right)
        return; // 空数组或者只有一个

    std::cout << "start:left=" << left << ";right=" << right << std::endl;
    print(arr);

    int i = left, j = right;
    int base = arr[left];
    while (i != j)
    {

        while (arr[i] <= base && i < j)
            i++;
        while (arr[j] > base && i < j)
            j--;

        //  swap
        mySwap(arr, i, j);
    }

    int index = arr[i] > base ? i - 1 : i;
    mySwap(arr, left, index);

    std::cout << "swap:";
    print(arr);

    quickSortDfs(arr, left, index - 1);
    quickSortDfs(arr, index + 1, right);
}

void quickSort(std::vector<int> &arr)
{
    return quickSortDfs(arr, 0, arr.size() - 1);
}
