#ifndef __TANUKIGB_UTILITY_PROPERTY_H__
#define __TANUKIGB_UTILITY_PROPERTY_H__

#include <concepts>
#include <functional>
#include <type_traits>

namespace tanukigb {

namespace {
// Despite google's style guide's dislike of concepts (afaik)I've already added
// a tonne and although it's basically handled in the getters and setters its
// annother check I guess
template <typename T>
concept NonReference = !std::is_reference_v<T>;

template <typename Fn, typename ValueType>
concept Getter =
    std::is_invocable_r_v<ValueType, Fn> ||
    std::is_invocable_r_v<const std::add_lvalue_reference_t<ValueType>, Fn>;

template <typename Fn, typename ValueType>
concept Copy_Setter =
    std::is_invocable_r_v<std::add_lvalue_reference_t<ValueType>, Fn,
                          const std::add_lvalue_reference_t<ValueType>>;

template <typename Fn, typename ValueType>
concept Move_Setter = std::is_invocable_r_v<
    std::add_lvalue_reference_t<ValueType>, Fn,
    std::add_rvalue_reference_t<std::remove_reference_t<ValueType>>>;
}  // namespace

// TODO: Can I use static assert to call error if write is called on read only
// property?
//       or should I make it a different name or basec class??

template <NonReference T, Getter<T> GetterFn, Copy_Setter<T> CopySetterFn,
          Move_Setter<T> MoveSetterFn>
class Property {
 private:
  using value_type = T;
  using reference = value_type&;

 public:
  Property(GetterFn gf, CopySetterFn cf, MoveSetterFn mf)
      : gf_{gf}, cf_{cf}, mf_{mf} {}
  ~Property() = default;

  Property(const T&) = delete;
  Property(T&&) = delete;

  // Should operator= return ref to T or ref to Property??
  // Ordinarilly I'd say Property but here the Get and Set are delegates so...

  operator std::invoke_result_t<GetterFn>() { return std::invoke(gf_); }

  reference operator=(const reference rhs) {
    // return std::invoke(CopySetterFn, rhs);
    return std::invoke(cf_, rhs);
  }

  reference operator=(value_type&& rhs) {
    // return std::invoke(MoveSetterFn, rhs);
    return std::invoke(mf_, std::move(rhs));
  }

 private:
  GetterFn gf_;
  CopySetterFn cf_;
  MoveSetterFn mf_;
};

}  // namespace tanukigb
#endif