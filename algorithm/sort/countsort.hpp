#pragma once

#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"


void count(const std::vector<int> &arr, std::vector<int> &counter)
{

    int max_val = findMax(arr);
    std::cout << "max_val=" << max_val << std::endl;
    counter.resize(max_val + 1, 0); //

    for (int val : arr)
    {
        counter[val]++;
    }
}

void countSort(std::vector<int> &arr)
{

    if (arr.size() <= 1)
        return;

    std::vector<int> counter;
    count(arr, counter);
    print(counter);

    int index = 0;
    for (int i = 0; i < counter.size(); i++)
    {
        while (counter[i] > 0)
        {
            arr[index++] = i;
            counter[i]--;
        }
    }
}