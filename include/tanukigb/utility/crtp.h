#ifndef __TANUKIGB_UTILITY_CRTP_H__
#define __TANUKIGB_UTILITY_CRTP_H__

#include <type_traits>

namespace tanukigb {

// Cant refer to CU in Crtp (at least the way I was trying
//template <typename Underlying, template <typename CU> typename CRTP_T>
template<typename Underlying, template <typename> typename CRTP_T>
class Crtp {
 public:
  Underlying& to_underlying() noexcept {
    return static_cast<Underlying&>(*this);
  }

  const Underlying& to_underlying() const noexcept {
    return static_cast<const Underlying&>(*this);
  }

 private:
  Crtp() = default;           /*{
    static_assert(std::is_same_v<Underlying, typename CU>,
                  "Crtp base class must have a crtp pattern class as its "
                  "second parameter and its underlying type must be the same "
                  "as the template parameter Underlying.")
  }*/
  friend CRTP_T<Underlying>;  // Maybe same as static assert as otherwise the
                              // constructor cannot be called?
};

}  // namespace tanukigb

#endif
