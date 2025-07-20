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
concept Free_Getter_Invokable =
    std::is_invocable_r_v<ValueType, Fn> ||
    std::is_invocable_r_v<const std::add_lvalue_reference_t<ValueType>, Fn>;

template <typename Fn, typename ValueType>
concept Free_Copy_Setter_Invokable =
    std::is_invocable_r_v<std::add_lvalue_reference_t<ValueType>, Fn,
                          const std::add_lvalue_reference_t<ValueType>>;

template <typename Fn, typename ValueType>
concept Free_Move_Setter_Invokable = std::is_invocable_r_v<
    std::add_lvalue_reference_t<ValueType>, Fn,
    std::add_rvalue_reference_t<std::remove_reference_t<ValueType>>>;

}  // namespace

// Free Getter, Copy Setter and Move Setter
 template <NonReference T, Free_Getter_Invokable<T> GetterFn,
          Free_Copy_Setter_Invokable<T> CopySetterFn,
          Free_Move_Setter_Invokable<T> MoveSetterFn>
class FreeProperty {
 public:
  //using value_type = T;
  typedef T value_type;
  using reference = value_type&;
  using getter_type = GetterFn;

 public:
  FreeProperty(GetterFn gf, CopySetterFn cf, MoveSetterFn mf)
      : gf_{gf}, cf_{cf}, mf_{mf} {}
  ~FreeProperty() = default;

  FreeProperty(const T&) = delete;
  FreeProperty(T&&) = delete;

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