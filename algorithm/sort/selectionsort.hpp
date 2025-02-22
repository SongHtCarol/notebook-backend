#pragma once

#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"

void selectionSort(std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int min = arr[i];
        int min_index = i;

        for (int j = i + 1; j < arr.size(); j++)
        {
            if (min > arr[j])
            {
                min = arr[j];
                min_index = j;
            }
        }

        mySwap(arr, i, min_index);
    }
}
// 调整当前子树
// 左节点 root*2 +1 小于 根节点
// 右节点 root*2 +2 小于 根节点
void adjustHeap(std::vector<int> &arr, int root, int len)
{

    int left = root * 2 + 1;
    int right = root * 2 + 2;

    if (left >= len)
        return;

    int max = arr[root];
    int max_index = root;
    if (left < len && arr[left] > max)
    {
        max = arr[left];
        max_index = left;
    }

    if (right < len && arr[right] > max)
    {

        max = arr[right];
        max_index = right;
    }

    if (root != max_index)
    {
        mySwap(arr, root, max_index);
        adjustHeap(arr, max_index, len);
    }
}

//  堆排序
void buildMaxHeap(std::vector<int> &arr)
{
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
    {
        adjustHeap(arr, i, arr.size());
    }
}

void heapSort(std::vector<int> &arr)
{
    buildMaxHeap(arr);

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        mySwap(arr, 0, i); // 把大根和最小的儿子交换

        // 缩小
        adjustHeap(arr, 0, i);

        std::cout << "swap:";
        print(arr);
    }
}
