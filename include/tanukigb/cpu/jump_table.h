#ifndef __TANUKIGB_CPU_JUMP_TABLE_H__
#define __TANUKIGB_CPU_JUMP_TABLE_H__

#include <array>
#include <utility>

// Purely generic so it can be lifted to library (or sub module but I like
// keeping dependancies one way to avoid cycles)

namespace tanukigb {

template <typename ReturnType, typename Reciever, std::size_t Num_Ops>
using JumpTable = std::array<ReturnType (*)(Reciever&), Num_Ops>;

namespace jumptable_details {

/*
Unfortunatly cannot be used as a replacement for typename as JumpSwitchType must
come first so it needs to be in the requires clause
*/
template <typename JumpSwitchType, template <JumpSwitchType> typename Handler,
          typename ReturnType, typename Reciever>
concept OpcodeHandler =
    std::is_integral_v<JumpSwitchType> && requires(Reciever& arg) {
      {
        Handler<static_cast<JumpSwitchType>(0)>::template execute<Reciever>(arg)
      } -> std::same_as<ReturnType>;
    };

template <typename JumpSwitchType, template <JumpSwitchType> typename Handler,
          typename ReturnType, typename Reciever, std::size_t... Ops>
  requires OpcodeHandler<JumpSwitchType, Handler, ReturnType, Reciever>
constexpr JumpTable<ReturnType, Reciever, sizeof...(Ops)> GenerateJumpTable(
    std::index_sequence<Ops...>) {
  return {(&Handler<Ops>::template execute<Reciever>)...};
}
}  // namespace jumptable_details

template <typename JumpSwitchType, template <JumpSwitchType> typename Handler,
          typename ReturnType, typename Reciever, std::size_t Num_Ops>
  requires jumptable_details::OpcodeHandler<JumpSwitchType, Handler, ReturnType,
                                            Reciever>
constexpr auto GenerateJumpTable() {
  return jumptable_details::GenerateJumpTable<JumpSwitchType, Handler,
                                              ReturnType, Reciever>(
      std::make_index_sequence<Num_Ops>{});
}

}  // namespace tanukigb
#endif