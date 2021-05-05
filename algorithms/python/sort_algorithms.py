import sys
import numpy as np


def merge(array: list, st: int, mid: int, ed: int):
    left = array[st:mid]
    right = array[mid:ed]
    right.append(sys.maxsize)
    left.append(sys.maxsize)

    n, m = 0, 0
    for i in range(st, ed):
        print(left[n], right[m])
        if left[n] <= right[m]:
            array[i] = left[n]
            n += 1
        else:
            array[i] = right[m]
            m += 1


def merge_sort(array: list, st: int, ed: int):
    if st + 1 < ed:
        mid = (st + ed) // 2
        merge_sort(array, st, mid)
        merge_sort(array, mid, ed)
        merge(array, st, mid, ed)



if __name__ == '__main__':
    array = np.random.randint(0, 10000, size=(1000,)).tolist()
    merge_sort(array, 0, len(array))
    print(array)
