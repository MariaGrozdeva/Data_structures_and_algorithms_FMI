#include <iostream>
#include <vector>
#include <unordered_map>

int subarraySum(const std::vector<int>& v, int k)
{
    int sum = 0;
    size_t count = 0;
    std::unordered_map<int, int> map;
    
    for (size_t i = 0; i < v.size(); i++)
    {
        sum += v[i];
        if (sum == k)
        {
            count++;
        }
        if (map.find(sum - k) != map.end())
        {
            count += map[sum - k];
        }
        map[sum]++;
    }
    
    return count;
}

int main()
{
    std::vector<int> v{ 4, 2, 2 };
    std::cout << subarraySum(v, 4);
}
