#include <iostream>

namespace W1ngD1nGa5ter {
namespace numeric {
template <typename T = unsigned, T MOD = 998244353> class modint {
  using value_type = T;
  value_type _val;

public:
  constexpr modint() = default;
  constexpr explicit modint(const value_type &x) : _val{x % MOD} {}
  constexpr modint &operator++() noexcept {
    return ++_val -= -(_val >= MOD) & MOD, *this;
  }
  constexpr modint operator++(int) noexcept {
    modint tmp = *this;
    ++*this;
    return tmp;
  }
  constexpr modint &operator--() noexcept {
    return --_val += -(_val >= MOD) & MOD, *this;
  }
  constexpr modint operator--(int) noexcept {
    modint tmp = *this;
    --*this;
    return tmp;
  }
  explicit constexpr operator value_type() const noexcept { return _val; }
  constexpr bool operator==(const modint &x) const noexcept {
    return _val == x._val;
  }
  constexpr modint operator-() const noexcept { return modint(MOD - _val); }
#if __cplusplus >= 2020000ll
  constexpr auto operator<=>(const modint &) const noexcept = default;
#else
  constexpr bool operator<(const modint &x) const noexcept {
    return _val < x._val;
  }
  constexpr bool operator<=(const modint &x) const noexcept {
    return _val <= x._val;
  }
  constexpr bool operator>(const modint &x) const noexcept {
    return _val > x._val;
  }
  constexpr bool operator>=(const modint &x) const noexcept {
    return _val >= x._val;
  }
  constexpr bool operator!=(const modint &x) const noexcept {
    return _val != x._val;
  }
#endif
  constexpr modint &operator+=(const modint &x) noexcept {
    return (_val += x._val), (_val -= MOD & -(_val >= MOD)), *this;
  }
  friend constexpr modint operator+(modint a, const modint &b) noexcept {
    return a += b;
  }
  constexpr modint &operator-=(const modint &x) noexcept {
    return (_val -= x._val), (_val += MOD & -(_val >= MOD)), *this;
  }
  friend constexpr modint operator-(modint a, const modint &b) noexcept {
    return a -= b;
  }
  constexpr modint &operator*=(const modint &x) noexcept {
    return _val = static_cast<unsigned long long>(_val) * x._val % MOD, *this;
  }
  friend constexpr modint operator*(modint a, const modint &b) noexcept {
    return a *= b;
  }
  friend std::istream &operator>>(std::istream &is, modint &x) noexcept {
    is >> x._val;
    x._val %= MOD;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const modint &x) noexcept {
    return os << x._val;
  }
};
} // namespace numeric
} // namespace W1ngD1nGa5ter
