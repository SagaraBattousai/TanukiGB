#ifndef __TANUKIGB_UTILITY_PIMPL_H__
#define __TANUKIGB_UTILITY_PIMPL_H__

#include <memory>
#include <utility>

namespace tanukigb {

template<typename Impl>
class Pimpl {
 public:
  Pimpl() : impl_(std::make_unique<Impl>()) {}
 template <typename... Args>
  Pimpl(Args&&... args) : impl_(std::make_unique<Impl, Args...>(std::forward<Args>(args)...)) {}
  ~Pimpl() = default;

  //TODO: Do make copyable, later
  Pimpl(const Pimpl&) = delete;
  Pimpl(Pimpl&&) = default;

  // TODO: Do make copy assignable?, later or just leave copy constructable only?
  Pimpl& operator=(const Pimpl&) = delete;
  Pimpl& operator=(Pimpl&&) = default;

  // I feel it should be a constant ptr to (non const) but ... it's not how GotW does
  Impl* const operator->() noexcept { return impl_.operator->(); }
  const Impl* const operator->() const noexcept { return impl_.operator->(); }

  // I feel it should be a constant ptr to (non const) but ... it's not how GotW does
  Impl& operator*() noexcept { return impl_.operator*(); }
  const Impl& operator*() const noexcept { return impl_.operator*(); }


 private:
  std::unique_ptr<Impl> impl_;
};


}


#endif