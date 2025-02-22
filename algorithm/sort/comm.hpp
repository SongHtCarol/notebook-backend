#pragma once

#include <iostream>

void mySwap(std::vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void print(const std::vector<int> &arr)
{

    std::cout << "arr:[";
    for (int i = 0; i < arr.size(); i++)
    {
        if (i > 0)
        {
            std::cout << ",";
        }
        std::cout << arr[i];
    }
    std::cout << "]" << std::endl;
}

bool compareArr(const std::vector<int> &arr1, const std::vector<int> &arr2)
{
    if (arr1.size() != arr2.size())
        return false;

    for (int i = 0; i < arr1.size(); i++)
    {
        if (arr1[i] != arr2[i])
            return false;
    }

    return true;
}

void printCompare(const std::vector<int> &result, const std::vector<int> &expected)
{

    std::cout << "result:[";
    for (int i = 0; i < result.size(); i++)
    {
        if (i > 0)
        {
            std::cout << ",";
        }
        std::cout << result[i];
    }

    std::cout << "]\nexpected:[";
    for (int i = 0; i < expected.size(); i++)
    {
        if (i > 0)
        {
            std::cout << ",";
        }
        std::cout << expected[i];
    }
    std::cout << "]" << std::endl;
}

int findMax(const std::vector<int> &arr)
{
    int max_val = -1;
    for (int val : arr)
    {
        if (val > max_val)
            max_val = val;
    }
    return max_val;
}

void findMaxAndMin(const std::vector<int> &arr, int &max, int &min)
{

    if (arr.empty())
        return;

    max = arr[0];
    min = arr[0];
    for (int val : arr)
    {
        if (val > max)
            max = val;
        if (val < min)
            min = val;
    }
}

int countBit(int val)
{
    int count = 0;
    while (val)
    {
        val /= 10;
        count++;
    }
    return count;
}