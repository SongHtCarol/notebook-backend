#pragma once

#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"

void radixSort(std::vector<int> &arr, std::vector<std::vector<int>> &bucket, int radix)
{

    int i = radix;
    int base = 1;
    while (i)
    {
        base *= 10;
        i--;
    }

    for (int val : arr)
    {

        int tmp = val / base;
        std::cout << "val=" << val << "radix=" << radix << "tmp=" << tmp << std::endl;
        int index = tmp % 10;
        if (bucket[index].empty())
            bucket[index] = std::vector<int>{val};
        else
            bucket[index].emplace_back(val);
    }

    arr.resize(0);
    for (int i = 0; i < bucket.size(); i++)
    {

        if (bucket[i].empty())
            continue;

        std::cout << "bucket[" << i << "]=";
        print(bucket[i]);
        for (int val : bucket[i])
            arr.emplace_back(val);

        bucket[i].resize(0);
    }
    print(arr);
}

void radixSort(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    std::vector<std::vector<int>> bucket(10);

    int count = countBit(findMax(arr));
    for (int i = 0; i < count; i++)
    {
        radixSort(arr, bucket, i);
    }
}