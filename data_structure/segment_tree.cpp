#include <bit>
#include <vector>

namespace W1ngD1nGa5ter
{
    namespace data_structure
    {
        template <typename Inf, typename Tag, bool TagOrdered>
        class segment_tree
        {
            std::size_t n, m;
            std::vector<Inf> segment;
            std::vector<Tag> lazytag;

            void build()
            {
                for (std::size_t i{m - 1}; i; --i)
                    segment[i] = segment[i << 1] + segment[i << 1 | 1];
            }

        public:
            segment_tree() = default;
            segment_tree(const segment_tree &) = default;
            segment_tree(segment_tree &&) = default;
            segment_tree &operator=(const segment_tree &) = default;
            segment_tree &operator=(segment_tree &&) = default;
            ~segment_tree() = default;

            segment_tree(std::size_t sz) : n{sz}, m{std::bit_floor(n - 1) << 1}, segment(m << 1), lazytag(m << 1) {}
            segment_tree(std::vector<Inf> &&v) : segment_tree(v.size())
            {
                std::move(v.begin(), v.end(), segment.begin() + m);
                build();
            }
            segment_tree(const std::vector<Inf> &v) : segment_tree(v.size())
            {
                std::copy(v.begin(), v.end(), segment.begin() + m);
                build();
            }
            segment_tree(std::size_t sz, Inf dflt) : segment_tree(sz)
            {
                std::fill(segment.begin() + m, segment.end(), dflt);
                build();
            }
        };
    }
}
