from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hashmap = {}
        for i, num in enumerate(nums):
            if target - num in hashmap:
                return [hashmap[target - num], i]
            hashmap[num] = i
        return []


def test():
    sol = Solution()
    nums = [3, 6, 3, 15]
    target = 6
    result = sol.twoSum(nums, target)
    print(result)

if __name__ == "__main__":
    test()

