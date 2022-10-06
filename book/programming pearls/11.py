from random import randint


def split_correctly(nums: list, left: int, cur_pos: int, split_pos: int, compare_target: int):
    for i in range(left, split_pos + 1):
        if nums[i] >= compare_target:
            return False
    for i in range(split_pos + 1, cur_pos + 1):
        if nums[i] < compare_target:
            return False
    return True


def is_sorted(nums: list, left: int, right: int):
    for i in range(left, right):
        if nums[i] > nums[i + 1]:
            return False
    return True


def quick_sort(nums: list, left: int, right: int):
    while left < right and nums[left] == nums[left + 1]:
        left += 1
    while right > left and nums[right] == nums[right - 1]:
        right -= 1

    if left >= right:
        return

    random_pos = randint(left, right)

    swap(nums, left, random_pos)
    t = nums[left]
    m = left - 1
    for i in range(left + 1, right + 1):
        if nums[i] < t:
            swap(nums, i, m + 1)
            m += 1
        assert split_correctly(nums, left, i, m, t), '分割不正确'

    assert left - 1 <= m <= right, '分割位置不正确'

    quick_sort(nums, left, m)
    quick_sort(nums, m + 1, right)

    assert is_sorted(nums, left, right), '排序不正确'


def swap(nums, pos1, pos2):
    t = nums[pos1]
    nums[pos1] = nums[pos2]
    nums[pos2] = t


if __name__ == '__main__':
    length = 100
    numbers = list(map(lambda _: randint(0, length * length), range(length)))
    print(numbers)
    quick_sort(numbers, 0, length - 1)
    print(numbers)
