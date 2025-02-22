#pragma once

#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/insertsort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"

constexpr int bucket_size = 5;

int bucketNumber(int val, int min_val)
{
    return (val - min_val) / bucket_size;
}

void makeBucket(const std::vector<int> &arr, std::vector<std::vector<int>> &bucket)
{
    int max_val = 0, min_val = 0;
    findMaxAndMin(arr, max_val, min_val);

    // std::cout << "max=" << max_val << ";min=" << min_val << std::endl;
    int count = (max_val - min_val) / bucket_size;
    bucket.resize(count + 1);

    for (int val : arr)
    {
        int number = bucketNumber(val, min_val);
        if (bucket[number].empty())
        {
            bucket[number] = std::vector<int>{val};
        }
        else
        {
            bucket[number].push_back(val);
        }
    }
}

void bucketSort(std::vector<int> &arr)
{

    if (arr.size() <= 1)
        return;

    std::vector<std::vector<int>> bucket;
    makeBucket(arr, bucket);

    // print(arr);

    arr.resize(0);
    for (int i = 0; i < bucket.size(); i++)
    {
        // std::cout << "bucket[" << i << "]=";
        // print(bucket[i]);
        if (bucket[i].empty())
            continue;

        insertSort(bucket[i]);

        for (int val : bucket[i])
            arr.emplace_back(val);
    }
}