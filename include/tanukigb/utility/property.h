#ifndef __TANUKIGB_UTILITY_PROPERTY_H__
#define __TANUKIGB_UTILITY_PROPERTY_H__

#include <concepts>
#include <functional>
#include <type_traits>

namespace tanukigb {

namespace {

template <typename R, typename CC, typename... Args>
struct member_function_ptr {
  typedef R (CC::*type)(Args...);
};
template <typename R, typename CC, typename... Args>
using member_function_ptr_t =
    typename member_function_ptr<R, CC, Args...>::type;

template <typename R, typename CC, typename... Args>
struct const_member_function_ptr {
  typedef R (CC::*type)(Args...) const;
};
template <typename R, typename CC, typename... Args>
using const_member_function_ptr_t =
    typename const_member_function_ptr<R, CC, Args...>::type;

template <typename T, typename CC>
class copy_assign_member_function_ptr {
 private:
  using reference = std::add_lvalue_reference_t<T>;

 public:
  typedef reference (CC::*type)(const reference);
};
template <typename T, typename CC>
using copy_assign_member_function_ptr_t =
    typename copy_assign_member_function_ptr<T, CC>::type;

template <typename T, typename CC>
class move_assign_member_function_ptr {
 private:
  using non_reference = std::remove_reference_t<T>;
  using reference = std::add_lvalue_reference_t<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

 public:
  typedef reference (CC::*type)(rvalue_reference);
};
template <typename T, typename CC>
using move_assign_member_function_ptr_t =
    typename move_assign_member_function_ptr<T, CC>::type;

}  // namespace

// Although it is theoretically possible to have a property with no getter
// it's such a corner case it's better to force setting of getter to nullptr
// manually
//
// Is forcing the getter to be const good?
//
// Could remove need to hold reference to ContainingClass by taking it as a
// param but as we want this to be syntatic sugar (and it could be exploited)
// its better not to.
//
template <
    typename T, typename ContainingClass,
    const_member_function_ptr_t<T, ContainingClass> Getter,
    copy_assign_member_function_ptr_t<T, ContainingClass> CopySetter = nullptr,
    move_assign_member_function_ptr_t<T, ContainingClass> MoveSetter = nullptr>
class Property {
 private:
  using non_reference = std::remove_reference_t<T>;
  using reference = std::add_lvalue_reference_t<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

 public:
  Property(ContainingClass& container) : container_{container} {}
  ~Property() = default;

  Property(const Property&) = delete;
  Property(Property&&) = delete;

  operator T() {
    static_assert(Getter != nullptr,
                  "Cannot call deleted Conversion (T()) AKA No getter set."
                  " If this is required, pass a Getter template parameter");
    return (container_.*Getter)();
  }

  reference operator=(const reference rhs) {
    static_assert(CopySetter != nullptr,
                  "Cannot call deleted copy asignment (T& operator=(const T&))."
                  " If this is required, pass a CopySetter template parameter");
    return (container_.*CopySetter)(rhs);
  }

  reference operator=(rvalue_reference rhs) {
    static_assert(MoveSetter != nullptr,
                  "Cannot call deleted move asignment (T& operator=(T&&))."
                  " If this is required, pass a MoveSetter template parameter");
    return (container_.*MoveSetter)(std::move(rhs));
  }

 private:
  ContainingClass& container_;
};

template <typename T, bool ReadOnly = false>
class SelfBackedProperty {
 private:
  using non_reference = std::remove_reference_t<T>;
  using reference = std::add_lvalue_reference_t<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

 public:
  using value_type = std::conditional_t<ReadOnly, const T, T>;

  SelfBackedProperty() : value_{} {}
  SelfBackedProperty(T initial_value) : value_{initial_value} {}
  SelfBackedProperty(const reference initial_value) : value_{initial_value} {}
  SelfBackedProperty(rvalue_reference initial_value)
      : value_{std::move(initial_value)} {}
  ~SelfBackedProperty() = default;

  SelfBackedProperty(const SelfBackedProperty&) = delete;
  SelfBackedProperty(SelfBackedProperty&&) = delete;

  operator value_type() { return value_; }

  T operator=(const reference rhs) {
    static_assert(!ReadOnly,
                  "Cannot call deleted copy asignment (T operator=(const T&)) "
                  "on ReadOnly Property");
    return value_ = rhs;
  }

  T operator=(rvalue_reference rhs) {
    static_assert(!ReadOnly,
                  "Cannot call deleted move asignment (T operator=(T&&)) "
                  "on ReadOnly Property");
    return value_ = std::move(rhs);
  }

 private:
  using stored_type =
      std::conditional_t<ReadOnly, const non_reference, non_reference>;
  stored_type value_;
};

}  // namespace tanukigb
#endif