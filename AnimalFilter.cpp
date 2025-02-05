#include "AnimalFilter.h"


#include <unordered_map>  // 使用 unordered_map 来提高查找效率

std::vector<std::wstring> Filter(std::vector<std::wstring> target, Repository* rep) {
    std::vector<std::vector<std::wstring>> t_list;
    std::vector<std::wstring> result;

    const auto& rep_map = rep->getMap();

    // 遍历 target 填充 t_list
    for (const auto& entry : target) {
        auto it = rep_map.find(entry);

        if (it != rep_map.end())
            t_list.push_back(it->second);  // 假设 it->second 是 std::vector<std::wstring>
    }

    std::unordered_map<std::wstring, int> KEY_COUNT;

    // 统计每个元素出现的次数
    for (const auto& entry : t_list) 
        for (const auto& val : entry) 
            KEY_COUNT[val]++;  // 自动插入并增加计数

    // 结果集，筛选出在每个目标中都出现的元素
    for (const auto& entry : KEY_COUNT) 
        if (entry.second == t_list.size()) 
            result.push_back(entry.first);

    return result;
}
