#include <iostream>

namespace W1ngD1nGa5ter
{
    namespace numeric
    {
        template <typename T = unsigned, T MOD = 998244353>
        class mod
        {
        public:
            using value_type = T;

            mod() = default;

            explicit mod(value_type x) : val{x} {}

            constexpr mod operator+(mod b) const noexcept { return b.val += val, b.val >= MOD ? b.val -= MOD, b : b; };
            constexpr mod operator-(mod b) const noexcept { return val < b.val ? b.val = val + MOD - b.val : b.val = val - b.val, b; };
            constexpr mod operator*(mod b) const noexcept { return b.val = static_cast<int>(1ull * val * b.val % MOD), b; };

            friend std::ostream &operator<<(std::ostream &os, const mod &x) { return os << x.val; }
            friend std::istream &operator>>(std::istream &is, mod &x) { return is >> x.val, x.val %= MOD, is; }

#if __cplusplus >= 202000ll
            constexpr auto operator<=>(const mod &other) const noexcept = default;
#else
            constexpr bool operator==(const mod &b) const noexcept { return val == b.val; }
            constexpr bool operator!=(const mod &b) const noexcept { return val != b.val; }
            constexpr bool operator<(const mod &b) const noexcept { return val < b.val; }
            constexpr bool operator<=(const mod &b) const noexcept { return val <= b.val; }
            constexpr bool operator>(const mod &b) const noexcept { return val > b.val; }
            constexpr bool operator>=(const mod &b) const noexcept { return val >= b.val; }
#endif

            constexpr mod &operator+=(mod b) noexcept { return val += b.val, val >= MOD ? val -= MOD : val, *this; }
            constexpr mod &operator-=(mod b) noexcept { return val < b.val ? val = val + MOD - b.val : val -= b.val, *this; }
            constexpr mod &operator*=(mod b) noexcept { return val = static_cast<int>(1ull * val * b.val % MOD), *this; }
            constexpr mod operator+() const noexcept { return *this; }
            constexpr mod operator-() const noexcept { return mod{val ? MOD - val : 0}; }

            constexpr mod &operator++() noexcept
            {
                if (++val == MOD)
                    val = 0;
                return *this;
            }

            constexpr mod operator++(int) noexcept
            {
                mod temp = *this;
                ++(*this);
                return temp;
            }

            constexpr mod &operator--() noexcept
            {
                if (val == 0)
                    val = MOD;
                return --val, *this;
            }

            constexpr mod operator--(int) noexcept
            {
                mod temp = *this;
                --(*this);
                return temp;
            }
            constexpr explicit operator bool() const noexcept { return val != 0; }
            constexpr explicit operator int() const noexcept { return static_cast<int>(val); }
            constexpr explicit operator long long() const noexcept { return static_cast<long long>(val); }
            constexpr explicit operator unsigned() const noexcept { return val; }

            constexpr value_type value() const noexcept { return val; }

            static constexpr value_type modulus() noexcept { return MOD; }
            static constexpr mod zero() noexcept { return mod{0}; }
            static constexpr mod one() noexcept { return mod{1}; }
            static constexpr mod identity() noexcept { return one(); }

        private:
            value_type val{};
        };
    } // namespace numeric
} // namespace W1ngD1nGa5ter
