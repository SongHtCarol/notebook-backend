#include <iostream>

#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/bubble.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/quicksort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/insertsort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/selectionsort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/mergesort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/countsort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/bucketsort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/radixsort.hpp"
#include "/Users/ivysong/beibei/github/SongHtCarol/notebook-backend/algorithm/sort/comm.hpp"

static std::vector<std::vector<int>> inputs = {
    {},        // 空数据集
    {1},       // 只含有一个元素
    {1, 1, 1}, // 全是相同元素
    {1, 2, 3}, // 已经是有序
    {3, 5, 1, 7},
    {3, 5, 0, 1, 7, 1}, // 含有重复元素
    {5, 3, 1},          // 逆序
    {53, 31, 61, 0, 112, 3, 45, 232, 5, 22, 11113}};

static std::vector<std::vector<int>> expected = {
    {},        // 空数据集
    {1},       // 只含有一个元素
    {1, 1, 1}, // 全是相同元素
    {1, 2, 3}, // 已经是有序
    {1, 3, 5, 7},
    {0, 1, 1, 3, 5, 7}, // 含有重复元素
    {1, 3, 5},          // 逆序
    {0, 3, 5, 22, 31, 45, 53, 61, 112, 232, 11113}};

int main()
{

    for (int i = 0; i < inputs.size(); i++)
    {
        auto input = inputs[i];

        // bubbleSort(input);
        // quickSort(input);
        // insertSort(input);
        // selectionSort(input);
        // heapSort(input);
        // mergeSort(input);
        // countSort(input);
        // bucketSort(input);
        radixSort(input);
        if (compareArr(input, expected[i]))
        {
            std::cout << "ok: index = " << i << std::endl;
            //     printCompare(input, expected[i]);
        }
        else
        {
            std::cout << "error: index = " << i << std::endl;
            printCompare(input, expected[i]);
        }
    }

    return 0;
}