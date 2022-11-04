from random import randint


def split_correctly(nums: list, left: int, right: int, split_pos: int, compare_target: int):
    # print('split_correctly', nums)
    # print('split_correctly', left, right, split_pos, compare_target)
    for i in range(left, split_pos):
        if nums[i] >= compare_target:
            return False
    for i in range(split_pos + 1, right + 1):
        if nums[i] < compare_target:
            return False
    return True


def is_sorted(nums: list, left: int, right: int):
    # print('is_sorted', nums[left:right + 1])
    for i in range(left, right):
        if nums[i] > nums[i + 1]:
            return False
    return True


# 注意分割的时候还是要比较用的数字移动到分割处，递归将比较数字排除，否则值都一样，由于范围没有缩小，会进入无限循环
def quick_sort(nums: list, left: int, right: int):
    if left >= right:
        return

    random_pos = randint(left, right)

    swap(nums, left, random_pos)
    t = nums[left]
    m = left
    for i in range(left + 1, right + 1):
        if nums[i] < t:
            swap(nums, i, m + 1)
            m += 1

    swap(nums, left, m)

    assert split_correctly(nums, left, i, m, t), '分割不正确'
    assert left - 1 <= m <= right, '分割位置不正确'

    quick_sort(nums, left, m - 1)
    quick_sort(nums, m + 1, right)

    assert is_sorted(nums, left, right), '排序不正确'


def swap(nums, pos1, pos2):
    t = nums[pos1]
    nums[pos1] = nums[pos2]
    nums[pos2] = t


if __name__ == '__main__':
    for length in range(1000):
        numbers = list(map(lambda _: randint(0, length * length), range(length)))
        # print('------------------------\n\n')
        # print(numbers)
        quick_sort(numbers, 0, length - 1)
