#include <iostream>
#include <vector>
#include <set>

bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int indexDiff, int valueDiff)
{
    std::multiset<long long> window;

    for (int i = 0; i < (int)nums.size(); ++i)
    {
        long long x = nums[i];

        auto it = window.lower_bound(x - (long long)valueDiff);
        if (it != window.end() && *it <= x + (long long)valueDiff)
        {
            return true;
        }

        window.insert(x);

        if (i >= indexDiff)
        {
            window.erase(window.find((long long)nums[i - indexDiff]));
        }
    }

    return false;
}

int main()
{
    std::vector<int> nums1 = {1, 2, 3, 1};
    int indexDiff1 = 3;
    int valueDiff1 = 0;
    std::cout << containsNearbyAlmostDuplicate(nums1, indexDiff1, valueDiff1) << '\n';

    std::vector<int> nums2 = {1, 5, 9, 1, 5, 9};
    int indexDiff2 = 2;
    int valueDiff2 = 3;
    std::cout << containsNearbyAlmostDuplicate(nums2, indexDiff2, valueDiff2) << '\n';

    return 0;
}
