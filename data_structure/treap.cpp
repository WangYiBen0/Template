#include <chrono>
#include <memory>
#include <random>

namespace W1ngD1nGa5ter {

namespace data_structure {

template <typename ValueType, typename RandomEngine = std::mt19937>
class treap {
public:
  using value_type = ValueType;
  using key_type = typename RandomEngine::result_type;
  using random_engine_type = RandomEngine;
  treap();
  treap(treap &&) = default;
  treap(const treap &) = delete;
  treap &operator=(treap &&) = default;
  treap &operator=(const treap &) = delete;
  ~treap();

  class Node {
  public:
    Node() = delete;
    Node(Node &&) = default;
    Node(const Node &) = delete;
    Node &operator=(Node &&) = default;
    Node &operator=(const Node &) = delete;
    ~Node() = default;

    explicit Node(ValueType &&value, key_type key)
        : val(std::forward<ValueType>(value)), key(key), sz(1), lson(), rson() {
    }

    void pushup() noexcept {
      sz = (lson ? lson->sz : 0) + (rson ? rson->sz : 0) + 1;
    }

    template <typename VT, typename RE> friend class treap;

  private:
    value_type val;
    key_type key;
    size_t sz;
    std::unique_ptr<Node> lson, rson;
  };

private:
  std::pair<std::unique_ptr<Node>, std::unique_ptr<Node>>
  split(std::unique_ptr<Node> root, ValueType k) {
    if (!root) {
      return {nullptr, nullptr};
    }
    if (root->val < k) {
      auto result = split(std::move(root->rson), k);
      root->rson = std::move(result.first);
      root->pushup();
      return {std::move(root), std::move(result.second)};
    } else {
      auto result = split(std::move(root->lson), k);
      root->lson = std::move(result.second);
      root->pushup();
      return {std::move(result.first), std::move(root)};
    }
  }

  std::pair<std::unique_ptr<Node>, std::unique_ptr<Node>>
  split_first_n(std::unique_ptr<Node> root, size_t n) {
    if (!root) {
      return {nullptr, nullptr};
    }
    size_t ls_sz = root->lson ? root->lson->sz : 0;
    if (ls_sz < n) {
      auto result = split_first_n(std::move(root->rson), n - ls_sz - 1);
      root->rson = std::move(result.first);
      root->pushup();
      return {std::move(root), std::move(result.second)};
    } else {
      auto result = split_first_n(std::move(root->lson), n);
      root->lson = std::move(result.second);
      root->pushup();
      return {std::move(result.first), std::move(root)};
    }
  }

  std::unique_ptr<Node> merge(std::unique_ptr<Node> u,
                              std::unique_ptr<Node> v) {
    if (!u)
      return v;
    if (!v)
      return u;

    if (u->key < v->key) {
      u->rson = merge(std::move(u->rson), std::move(v));
      u->pushup();
      return u;
    } else {
      v->lson = merge(std::move(u), std::move(v->lson));
      v->pushup();
      return v;
    }
  }

public:
  void insert(ValueType v) {
    auto part = split(std::move(root), v);
    auto new_node = std::make_unique<Node>(std::move(v), rng());
    root = merge(merge(std::move(part.first), std::move(new_node)),
                 std::move(part.second));
  }

  void erase_one(ValueType v) {
    auto lpart = split(std::move(root), v);
    auto rpart = split(std::move(lpart.second), v + 1);
    if (!rpart.first) {
      root = merge(std::move(lpart.first), std::move(rpart.second));
      return;
    }
    auto new_root =
        merge(std::move(rpart.first->lson), std::move(rpart.first->rson));
    rpart.first.reset();
    root = merge(std::move(lpart.first),
                 merge(std::move(new_root), std::move(rpart.second)));
  }

  ValueType nth_element(size_t n) {
    auto part = split_first_n(std::move(root), n);
    if (!part.first) {
      root = merge(std::move(part.first), std::move(part.second));
      throw "No such element!";
    }
    Node *cur = part.first.get();
    while (cur->rson) {
      cur = cur->rson.get();
    }
    value_type ret = cur->val;
    root = merge(std::move(part.first), std::move(part.second));
    return ret;
  }

  ValueType prev(ValueType v) {
    auto part = split(std::move(root), v);
    if (!part.first) {
      root = merge(std::move(part.first), std::move(part.second));
      throw "No prev element!";
    }
    Node *cur = part.first.get();
    while (cur->rson) {
      cur = cur->rson.get();
    }
    value_type ret = cur->val;
    root = merge(std::move(part.first), std::move(part.second));
    return ret;
  }

  ValueType next(ValueType v) {
    auto part = split(std::move(root), v + 1);
    if (!part.second) {
      root = merge(std::move(part.first), std::move(part.second));
      throw "No next element!";
    }
    Node *cur = part.second.get();
    while (cur->lson) {
      cur = cur->lson.get();
    }
    value_type ret = cur->val;
    root = merge(std::move(part.first), std::move(part.second));
    return ret;
  }

  size_t rank(ValueType v) {
    auto part = split(std::move(root), v);
    size_t ret = part.first ? part.first->sz : 0;
    root = merge(std::move(part.first), std::move(part.second));
    return ret;
  }

  size_t size() const { return root ? root->sz : 0; }

  bool empty() const { return !root; }

private:
  std::unique_ptr<Node> root;
  random_engine_type rng;
};

template <typename ValueType, typename RandomEngine>
treap<ValueType, RandomEngine>::treap()
    : rng(std::random_device{}.entropy() > 0
              ? std::random_device{}()
              : std::chrono::system_clock::now().time_since_epoch().count()) {}

template <typename ValueType, typename RandomEngine>
treap<ValueType, RandomEngine>::~treap() {}

} // namespace data_structure

} // namespace W1ngD1nGa5ter
