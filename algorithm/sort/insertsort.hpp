#pragma once

#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"

void insertSort(std::vector<int> &arr)
{
    for (int i = 1; i < arr.size(); i++)
    {

        std::cout << "start: arr[" << i << "]=" << arr[i] << std::endl;
        print(arr);

        int j = 0;
        while (arr[j] <= arr[i] && j < i)
            j++;

        while (j != i)
        {
            mySwap(arr, j, i);
            j++;
        }

        std::cout << "swap:";
        print(arr);
    }
}