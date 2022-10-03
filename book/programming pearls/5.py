import random


def is_sorted(nums: list):
    for i in range(len(nums) - 1):
        if not nums[i] <= nums[i + 1]:
            return False
    return True


def binary_search(nums: list, left: int, right: int, target: int):
    assert is_sorted(nums), "未排序"

    if target < nums[left] or target > nums[right]:
        return -1

    while left < right:

        assert nums[left] <= target and nums[right] >= target, "目标值超出范围{} {} {} {}".format(left, right, target, nums)
        if target == nums[left]:
            return left
        if target == nums[right]:
            return right

        num_range = right - left
        middle = (left + right) // 2
        if nums[middle] == target:
            return middle

        if nums[middle] < target:
            left = middle + 1
        else:
            right = middle - 1

        assert right - left < num_range, "搜索范围未缩减{} {} {} {}".format(left, right, target, nums)

    return -1


if __name__ == '__main__':
    length = 10
    numbers = list(
        map(lambda _: random.randint(0, length * length),
            range(length)))

    numbers.sort()
    test_targets = []
    for n in numbers:
        test_targets.append(n)
        test_targets.append(random.randint(0, length * length))
    postions = list(map(lambda n: binary_search(numbers, 0, length - 1, n), test_targets))
    print(numbers)
    for i in range(len(test_targets)):
        print(test_targets[i], postions[i], numbers[postions[i]])
