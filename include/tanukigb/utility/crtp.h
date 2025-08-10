#ifndef __TANUKIGB_UTILITY_CRTP_H__
#define __TANUKIGB_UTILITY_CRTP_H__

#include <type_traits>

namespace tanukigb {

template<typename Derived, template <typename> typename CRTP_T>
class Crtp {
 public:
  using derived_type = Derived;

  derived_type& as_derived() noexcept {
    return static_cast<derived_type&>(*this);
  }

  const derived_type& as_derived() const noexcept {
    return static_cast<const derived_type&>(*this);
  }

 private:
  Crtp() = default;
  friend CRTP_T<Derived>;
};

template <typename Derived, template <typename> typename CRTP_T>
class StaticCrtp {
 public:
  using derived_type = Derived;

 private:
  StaticCrtp() = default;
  friend CRTP_T<Derived>;
};

}  // namespace tanukigb

#endif
