import random


def is_sorted(nums: list):
    for i in range(len(nums) - 1):
        if not nums[i] <= nums[i + 1]:
            return False
    return True


# 编程几株中的二分，中位数不再使用，容易导致搜索范围全部高于或者低于目标值
# 书中循环不变量只有在包含目标值得情况下才能始终成立
# 实际循环不变量用 目标值必然不在去掉的范围内更加合适
def binary_search_0(nums: list, left: int, right: int, target: int):
    assert is_sorted(nums), "未排序"

    if target < nums[left] or target > nums[right]:
        return -1

    while left <= right:

        # 这里因为没有目标值的情况下，范围可能直接在目标外，所以这个断言没法用
        # assert nums[left] <= target and nums[right] >= target, "目标值超出范围{} {} {} {}".format(left, right, target, nums)
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


# 中位数继续作为边界使用，边界值始终不可能是目标值
def binary_search_1(nums: list, left: int, right: int, target: int):
    assert is_sorted(nums), "未排序"

    if target < nums[left] or target > nums[right]:
        return -1

    if nums[left] == target:
        return left
    if nums[right] == target:
        return right

    # 因为目标值不再边界上，所以长度为2时就可以停止
    while left < right - 1:
        # 这里循环不变量 目标值始终在边界内，不再边界上
        assert nums[left] < target and nums[right] > target, "目标值超出范围{} {} {} {}".format(left, right, target, nums)
        if target == nums[left]:
            return left
        if target == nums[right]:
            return right

        num_range = right - left
        middle = (left + right) // 2
        if nums[middle] == target:
            return middle

        if nums[middle] < target:
            left = middle
        else:
            right = middle

        assert right - left < num_range, "搜索范围未缩减{} {} {} {}".format(left, right, target, nums)

    return -1


def gen_numbers(length: int):
    length = 10
    numbers = list(
        map(lambda _: random.randint(0, length * length),
            range(length)))
    numbers.sort()
    return numbers


def test(numbers: list, search_func):
    print(search_func)
    length = len(numbers)
    test_targets = []
    for n in numbers:
        test_targets.append(n)
        test_targets.append(random.randint(0, length * length))
    positions = list(map(lambda n: search_func(numbers, 0, length - 1, n), test_targets))
    print(numbers)
    for i in range(len(test_targets)):
        pos = positions[i]
        if pos == -1:
            print(test_targets[i], pos)
        else:
            print(test_targets[i], pos, numbers[pos])


if __name__ == '__main__':
    for func in [binary_search_0, binary_search_1]:
        test(gen_numbers(10), binary_search_0)
