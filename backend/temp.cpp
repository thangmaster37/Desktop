#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v = {5, 2, 8, 10, 9};
    auto maxElementIndex = std::max_element(v.begin(), v.end()) - v.begin();
    std::cout << "maxElementIndex:" << maxElementIndex << '\n';
    return 0;
}