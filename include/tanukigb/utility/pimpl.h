#ifndef __TANUKIGB_UTILITY_PIMPL_H__
#define __TANUKIGB_UTILITY_PIMPL_H__

#include <memory>

namespace tanukigb {

// Still unsure if this is correct in the way that it is, templates with imcomplete types
// is sothething I need to look into more.

// May need to move implmentation to pimpl_impl.h
// However I think, so long as we dont call any of these functions while Impl is undefined, it's
// safe to leave it in one file.
template<typename Impl>
class Pimpl {
 public:
  Pimpl() : impl_(std::make_unique()) {}
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