#include "AnimalFilter.h"


#include <unordered_map>  // ʹ�� unordered_map ����߲���Ч��

std::vector<std::wstring> Filter(std::vector<std::wstring> target, Repository* rep) {
    std::vector<std::vector<std::wstring>> t_list;
    std::vector<std::wstring> result;

    const auto& rep_map = rep->getMap();

    // ���� target ��� t_list
    for (const auto& entry : target) {
        auto it = rep_map.find(entry);

        if (it != rep_map.end())
            t_list.push_back(it->second);  // ���� it->second �� std::vector<std::wstring>
    }

    std::unordered_map<std::wstring, int> KEY_COUNT;

    // ͳ��ÿ��Ԫ�س��ֵĴ���
    for (const auto& entry : t_list) 
        for (const auto& val : entry) 
            KEY_COUNT[val]++;  // �Զ����벢���Ӽ���

    // �������ɸѡ����ÿ��Ŀ���ж����ֵ�Ԫ��
    for (const auto& entry : KEY_COUNT) 
        if (entry.second == t_list.size()) 
            result.push_back(entry.first);

    return result;
}
