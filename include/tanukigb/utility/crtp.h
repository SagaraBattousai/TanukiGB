#ifndef __TANUKIGB_UTILITY_CRTP_H__
#define __TANUKIGB_UTILITY_CRTP_H__

#include <type_traits>

namespace tanukigb {

template<typename Underlying, template <typename> typename CRTP_T>
class Crtp {
 public:
  using underlying_type = Underlying;

  underlying_type& to_underlying() noexcept {
    return static_cast<underlying_type&>(*this);
  }

  const underlying_type& to_underlying() const noexcept {
    return static_cast<const underlying_type&>(*this);
  }

 private:
  Crtp() = default;
  friend CRTP_T<Underlying>;
};

}  // namespace tanukigb

#endif
