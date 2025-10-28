#include <vector>

namespace W1ngD1nGa5ter
{
    namespace data_structure
    {
        template <typename Inf>
        class binary_indexed_tree {
            std::vector<Inf> data;

        public:
            binary_indexed_tree() = default;
            binary_indexed_tree(binary_indexed_tree &&) = default;
            binary_indexed_tree(const binary_indexed_tree &) = default;
            binary_indexed_tree &operator=(binary_indexed_tree &&) = default;
            binary_indexed_tree &operator=(const binary_indexed_tree &) = default;
            ~binary_indexed_tree() = default;

            void update(std::size_t x, Inf delta)
            {
                while (x < data.size())
                {
                    data[x] += delta;
                    x += x & -x;
                }
            }

            Inf query(std::size_t x)
            {
                Inf res{};
                while (x)
                {
                    res += data[x];
                    x &= -x;
                }
                return res;
            }
        };
    }
}
