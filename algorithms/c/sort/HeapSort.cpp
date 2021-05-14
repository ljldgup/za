#include <stdio.h>
#include <stdlib.h>
#include"test.h"

void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
 
void maxHeapify(int *nums, int start, int end) 
{
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end)  //若子节点指标在范围内才做比较
        {
            if (son + 1 <= end && *(nums + son) < *(nums +son + 1)) 
            //先比较两个子节点大小，选择最大的
            son++;
        if (*(nums + dad) > *(nums +son)) 
            //由于是从低到高建堆，所以下方节点已经排好序，如果父节点大於子节点代表调整完毕，直接跳出函数
            return;
        else  //否则交换父子内容再继续子节点和孙节点比较
        {
            swap(nums + dad, nums +son);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
 
void heapSort(int *nums, int len) 
{
    int i;
    //初始化，i从最後一个父节点开始调整
    for (i = len / 2 - 1; i >= 0; i--)
        maxHeapify(nums, i, len - 1);
    //先将第一个元素和已排好元素前一位做交换，再重新调整，直到排序完毕
    for (i = len - 1; i > 0; i--) 
    {
        swap(nums, nums + i);
        maxHeapify(nums, 0, i - 1);
    }
}
 
/* int main() {
    int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    
    heapSort(arr, len);
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
 */