#include <vector>
#include <iostream>
#include <format>
//#include <print>

int main()
{
    std::vector<int> ints { 2, 4, 6, 1, 3, 5 };
    for (size_t index = 0u; auto element : ints)
    {
        //std::cout << "Index: " << index << " Value: " << element << '\n';
        //printf("Index: %i Value: %i \n", (int)index, (int)element);
        std::cout << std::format("Index: {} Value: {} \n", index, element);
        ++index;
    }

    return 0;
}
