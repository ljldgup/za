from random import randint


def is_sorted(nums: list, left: int, right: int):
    # print('is_sorted', nums[left:right + 1])
    for i in range(left, right):
        if nums[i] > nums[i + 1]:
            return False
    return True


def heap_ordered(nums, pos, length):
    for child in [2 * pos + 1, 2 * pos + 2]:
        if child < length and nums[child] > nums[pos]:
            return False
    return True


def heap_sort(nums: list):
    length = len(nums)
    for i in range(length // 2, -1, -1):
        max_heap(nums, i, length)

    assert all(map(lambda n: heap_ordered(nums, n, length), range(length)))

    for i in range(length - 1, -1, -1):
        swap(nums, 0, i)
        # print(nums[0:i])
        max_heap(nums, 0, i)
        # print(nums[0:i])
        assert all(map(lambda n: nums[n] <= nums[i], range(0, i - 1)))
        assert is_sorted(nums, i, length - 1)


def swap(nums: list, a: int, b: int):
    t = nums[a]
    nums[a] = nums[b]
    nums[b] = t


def max_heap(nums, pos, length):
    max_pos = pos

    for child in [2 * pos + 1, 2 * pos + 2]:
        if child < length and nums[child] > nums[max_pos]:
            max_pos = child

    if max_pos != pos:
        swap(nums, pos, max_pos)
        max_heap(nums, max_pos, length)


if __name__ == '__main__':
    length = 10
    numbers = list(map(lambda _: randint(0, length * length), range(length)))
    # print('------------------------\n\n')
    # print(numbers)
    heap_sort(numbers)
    print(numbers)
