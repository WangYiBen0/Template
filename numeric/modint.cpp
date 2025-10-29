#include <iostream>

namespace W1ngD1nGa5ter
{
    namespace numeric
    {
        template <unsigned MOD = 998244353>
        class mod
        {
        public:
            mod() = default;

            explicit mod(unsigned x) : val{x} {}

            mod operator+(mod b) const noexcept { return b.val += val, b.val >= MOD ? b.val -= MOD, b : b; };
            mod operator-(mod b) const noexcept { return val < b.val ? b.val = val + MOD - b.val : b.val = val - b.val, b; };
            mod operator*(mod b) const noexcept { return b.val = static_cast<int>(1ull * val * b.val % MOD), b; };

            friend std::ostream &operator<<(std::ostream &os, const mod &x) { return os << x.val; }
            friend std::istream &operator>>(std::istream &is, mod &x) { return is >> x.val, x.val %= MOD, is; }

            mod &operator+=(mod b) noexcept { return val += b.val, val >= MOD ? val -= MOD : val, *this; }
            mod &operator-=(mod b) noexcept { return val < b.val ? val = val + MOD - b.val : val -= b.val, *this; }
            mod &operator*=(mod b) noexcept { return val = static_cast<int>(1ull * val * b.val % MOD), *this; }

        private:
            unsigned val{};
        };
    }
}
