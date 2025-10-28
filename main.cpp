#include <iostream>
#include <chrono>
#include <print>

namespace W1ngD1nGa5ter
{
    class Solution
    {
    public:
        Solution() {}
        void operator()() {}
    };
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    std::cin.tie(nullptr)->sync_with_stdio(false);
    {
        auto str = std::format("  Start Program at [UTC {:%Y年%m月%d日-%H:%M:%S}].  ", std::chrono::system_clock::now());
        std::cerr << str << std::endl;
        for (std::size_t i{0}; i < str.size(); ++i)
            std::cerr.put('-');
        std::cerr.put('\n');
    }

    {
        int T = 1;
        std::cin >> T;
        while (T--)
            W1ngD1nGa5ter::Solution()();
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - start;
    {
        auto str = std::format("  done with code 0. Time: {} == {}  ", elapsed, std::chrono::duration_cast<std::chrono::milliseconds>(elapsed));
        for (std::size_t i{0}; i < str.size(); ++i)
            std::cerr.put('-');
        std::cerr.put('\n');
        std::cerr << str << std::endl;
    }
    return 0;
}
