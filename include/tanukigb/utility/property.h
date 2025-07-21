#ifndef __TANUKIGB_UTILITY_PROPERTY_H__
#define __TANUKIGB_UTILITY_PROPERTY_H__

#include <concepts>
#include <functional>
#include <type_traits>

namespace tanukigb {

template <typename T, typename ContainingClass, bool ReadOnly,
          bool CopyAssignable, bool MoveAssignable>
class Property {
  static_assert(false,
                "Primary template class should not be posible to instantiate");
};

// ReadWrite, Move and Copy assignable
template <typename T, typename ContainingClass>
class Property<T, ContainingClass, false, true, true> {
 private:
  using non_reference = std::remove_reference_t<T>;
  using reference = std::add_lvalue_reference<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

  using getter_type = T (ContainingClass::*)();
  using copy_setter_type =
      typename reference(ContainingClass::*)(const reference);
  using move_setter_type =
      typename reference(ContainingClass::*)(rvalue_reference);

 public:
  Property(ContainingClass& container, getter_type getter,
           copy_setter_type copy_setter, move_setter_type move_setter)
      : container_{container},
        getter_{getter},
        copy_setter_{copy_setter},
        move_setter_{move_setter} {}
  ~Property() = default;

  Property(const Property&) = delete;
  Property(Property&&) = delete;

  operator T() { return container_.*getter_(); }

  reference operator=(const reference rhs) {
    return container_.*copy_setter_(rhs);
  }

  reference operator=(rvalue_reference rhs) {
    return container_.*move_setter_(std::move(rhs));
  }

 private:
  ContainingClass& container_;
  getter_type getter_;
  copy_setter_type copy_setter_;
  move_setter_type move_setter_;
};

// Readonly (therfore copy and move assignable are irrelevant)
template <typename T, typename ContainingClass, bool CopyAssignable,
          bool MoveAssignable>
class Property<T, ContainingClass, true, CopyAssignable, MoveAssignable> {
 private:
  using non_reference = std::remove_reference_t<T>;
  using reference = std::add_lvalue_reference<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

  using getter_type = T (ContainingClass::*)();

 public:
  Property(ContainingClass& container, getter_type getter)
      : container_{container},
        getter_{getter} {}
  ~Property() = default;

  Property(const Property&) = delete;
  Property(Property&&) = delete;

  operator T() { return container_.*getter_(); }

  reference operator=(const reference rhs) = delete;

  reference operator=(rvalue_reference rhs) = delete;

 private:
  ContainingClass& container_;
  getter_type getter_;
};

// Copy but not Move Assignable
template <typename T, typename ContainingClass>
class Property<T, ContainingClass, false, true, false> {
 private:
  using non_reference = std::remove_reference_t<T>;
  using reference = std::add_lvalue_reference<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

  using getter_type = T (ContainingClass::*)();
  using copy_setter_type =
      typename reference (ContainingClass::*)(const reference);

 public:
  Property(ContainingClass& container, getter_type getter,
           copy_setter_type copy_setter)
      : container_{container},
        getter_{getter},
        copy_setter_{copy_setter} {}
  ~Property() = default;

  Property(const Property&) = delete;
  Property(Property&&) = delete;

  operator T() { return container_.*getter_(); }

  reference operator=(const reference rhs) {
    return container_.*copy_setter_(rhs);
  }

  reference operator=(rvalue_reference rhs) = delete;

 private:
  ContainingClass& container_;
  getter_type getter_;
  copy_setter_type copy_setter_;
};

// Move but not Copy Assignable
template <typename T, typename ContainingClass>
class Property<T, ContainingClass, false, false, true> {
 private:
  using non_reference = std::remove_reference_t<T>;
  using reference = std::add_lvalue_reference<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

  using getter_type = T (ContainingClass::*)();
  using move_setter_type =
      typename reference (ContainingClass::*)(rvalue_reference);

 public:
  Property(ContainingClass& container, getter_type getter,  move_setter_type move_setter)
      : container_{container},
        getter_{getter},
        move_setter_{move_setter} {}
  ~Property() = default;

  Property(const Property&) = delete;
  Property(Property&&) = delete;

  operator T() { return container_.*getter_(); }

  reference operator=(const reference rhs) = delete;

  reference operator=(rvalue_reference rhs) {
    return container_.*move_setter_(std::move(rhs));
  }

 private:
  ContainingClass& container_;
  getter_type getter_;
  move_setter_type move_setter_;
};



// Useful when member style access is wanted only allowing set and get.
// Originally an unused primary template but we can actually do everything here
// and use static assert instead of deleting the function.
//
// Usually youll want T to be an lvalue reference unless using a literal
// (pass-by-value) type
//
// Seems to work for now.
//

template <typename T, bool ReadOnly = false>
class SelfBackedProperty {
 private:
  using non_reference = std::remove_reference_t<T>;
  using rvalue_reference = std::add_rvalue_reference_t<non_reference>;

 public:
  using value_type = std::conditional_t<ReadOnly, const T, T>;

  SelfBackedProperty() : value_{} {}
  ~SelfBackedProperty() = default;

  SelfBackedProperty(const SelfBackedProperty&) = delete;
  SelfBackedProperty(SelfBackedProperty&&) = delete;

  // No (by) Value constructor to simplify despite that by value is good for
  // literal types...

  SelfBackedProperty(const T& initial_value) : value_{initial_value} {}
  SelfBackedProperty(rvalue_reference initial_value)
      : value_{std::move(initial_value)} {}

  operator value_type() { return value_; }

  // TODO: may have an issue here
  T operator=(const T& rhs) {
    static_assert(!ReadOnly,
                  "Cannot call deleted copy asignment (T operator=(const T&)) "
                  "on ReadOnly Property");
    return value_ = rhs;
  }

  // TODO: may have an issue here
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