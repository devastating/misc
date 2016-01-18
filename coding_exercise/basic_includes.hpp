// Basic includes so that I don't have to type every time..

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <climits>
#include <assert.h>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

template<typename _vector_type>
static inline void print_vector(std::vector<_vector_type> in,
                                std::string title = "Input")
{
    std::cout << title << ": ";
    for (auto item: in)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";
}
