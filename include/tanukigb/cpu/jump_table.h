#ifndef __TANUKIGB_CPU_JUMP_TABLE_H__
#define __TANUKIGB_CPU_JUMP_TABLE_H__

#include <array>
#include <type_traits>

// Purely generic so it can be lifted to library (or sub module but I like
// keeping dependancies one way to avoid cycles)

namespace tanukigb {

//Has to be std::size_t Num_Ops (in all other integer_sequences) as although we want 0 - (N-1) we have to specify N and N may not fit into the type (even though 0 - (N-1) will.

template <typename ReturnType, typename Reciever, std::size_t Num_Ops>
using JumpTable = std::array<ReturnType (*)(Reciever), Num_Ops>;

namespace jumptable_details {
// Dont think I need any of this actually (FP Stuff) TODO: Remove on commit
template <typename FP>
struct is_function_pointer
    : std::bool_constant<std::is_pointer_v<FP> &&
                         std::is_function_v<std::remove_pointer_t<FP>>> {};

template <typename FP>
constexpr inline bool is_function_pointer_v = is_function_pointer<FP>::value;

template <typename FP>
concept FunctionPtr = is_function_pointer_v<FP>;

// Required as OpcodeType has to come first so we cant do it for Concept wiout
// specifying for every integral so... Reciever should be lvalue ref but I think
// we should leave that for the caller to decide? Technically could check if
// reciver is_class and then choose ref vs pointer but I think its fine.
template <typename OpcodeType, template <OpcodeType> typename T,
          typename ReturnType, typename Reciever>
struct is_table_handler
    : std::bool_constant<
          std::is_integral_v<OpcodeType> &&
          std::is_same_v<
              ReturnType,
              std::invoke_result_t<&T<OpcodeType{}>::template execute<Reciever>,
                                   Reciever>>> {};

template <typename OpcodeType, template <OpcodeType> typename T,
          typename ReturnType, typename Reciever>
constexpr inline bool is_table_handler_v =
    is_table_handler<OpcodeType, T, ReturnType, Reciever>::value;

template <typename OpcodeType, template <OpcodeType> typename T,
          typename ReturnType, typename Reciever, std::size_t... Ops>
  requires is_table_handler_v<OpcodeType, T, ReturnType, Reciever>
constexpr JumpTable<ReturnType, Reciever, sizeof...(Ops)> GenerateJumpTable(
    std::index_sequence<Ops...>) {
  return {(&T<Ops>::template execute<Reciever>)...};
}
}  // namespace jumptable_details

// template <Executor E, opcode_type Num_Ops>
template <typename OpcodeType, template <OpcodeType> typename T,
          typename ReturnType, typename Reciever, std::size_t Num_Ops>
constexpr auto GenerateJumpTable() {
  return jumptable_details::GenerateJumpTable<OpcodeType, T, ReturnType,
                                              Reciever>(
      std::make_index_sequence<Num_Ops>{});
}

}  // namespace tanukigb
#endif