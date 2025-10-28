#include <pointer>
#include <vector>
#include <random>

namespace W1ngD1nGa5ter
{
    namespace data_structure
    {
        template <typename Value, typename Key = std::size_t, typename random_engine = std::mt19937>
        class Treap
        {
        public:
            Treap();
            Treap(Treap &&) = default;
            Treap(const Treap &) = default;
            Treap &operator=(Treap &&) = default;
            Treap &operator=(const Treap &) = default;
            ~Treap();

            struct node
            {
                Key key;
                Value val;
                node *lson, *rson;
            } *root;

            Treap split(int); // split a new fhq-treap whose root is x
            void merge(Treap &&); // merge with the treap
            friend merge(Treap &&a, Treap &&b); // merge two treap according to key

        private:
        };

        Treap::Treap()
        {
        }

        Treap::~Treap()
        {
        }
    }
}
