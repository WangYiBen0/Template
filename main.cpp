#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#if __cplusplus >= 202000ll
#include <format>
#if __cplusplus >= 202300ll
#include <print>
#endif
#endif

namespace W1ngD1nGa5ter
{
    class Process
    {
    public:
        Process() = default;
        int operator()()
        {
            // TODO
            return 0;
        }
    };
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    std::cin.tie(nullptr)->sync_with_stdio(false);
    {
#if __cplusplus >= 202000ll
        auto str = std::format("  Start Program at [UTC {:%Y年%m月%d日-%H:%M:%S}].  ", std::chrono::system_clock::now());
#else

        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::gmtime(&time_t);

        std::ostringstream oss;
        oss << "  Start Program at [UTC "
            << std::put_time(&tm, "%Y年%m月%d日-%H:%M:%S")
            << "].  ";
        auto str = oss.str();
#endif
        std::cerr << str << std::endl;
        for (std::size_t i{0}; i < str.size(); ++i)
            std::cerr.put('-');
        std::cerr.put('\n');
    }

    {
        W1ngD1nGa5ter::Process Main;
        int T = 1, lastRet;
        std::cin >> T;
        while (T--)
        {
            lastRet = Main();
            if (lastRet)
                break;
        }
        if (lastRet)
            std::cerr << "ERROR: returned " << lastRet << '\n';
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - start;
    {
#if __cplusplus >= 202000ll
        auto str = std::format("  done with code 0. Time: {} == {}  ", elapsed, std::chrono::duration_cast<std::chrono::milliseconds>(elapsed));
#else
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);

        std::ostringstream oss;
        oss << "  done with code 0. Time: "
            << elapsed_ns.count() << "ns == "
            << elapsed_ms.count() << "ms  ";
        auto str = oss.str();
#endif
        for (std::size_t i{0}; i < str.size(); ++i)
            std::cerr.put('-');
        std::cerr.put('\n');
        std::cerr << str << std::endl;
    }
    return 0;
}
