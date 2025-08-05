
#include <gtest/gtest.h>
#include <tanukigb/cpu/register/register_set.h>

#include <type_traits>

namespace tanukigb {
namespace tests {
/*
class RegisterSetTest : public testing::Test {
 protected:
  RegisterSet rs;
};

class RegisterSetFlagsTest
    : public RegisterSetTest,
      public testing::WithParamInterface<RegisterSet::Flag> {
  // public:
};

TEST_F(RegisterSetTest, InitalisedWithRegistersZeroed) {
  ASSERT_EQ(rs.A(), (byte_t)0x00) << "Register A should start at 0";
  ASSERT_EQ(rs.F(), (byte_t)0x00) << "Register F should start at 0";
  ASSERT_EQ(rs.B(), (byte_t)0x00) << "Register B should start at 0";
  ASSERT_EQ(rs.C(), (byte_t)0x00) << "Register C should start at 0";
  ASSERT_EQ(rs.D(), (byte_t)0x00) << "Register D should start at 0";
  ASSERT_EQ(rs.E(), (byte_t)0x00) << "Register E should start at 0";
  ASSERT_EQ(rs.H(), (byte_t)0x00) << "Register H should start at 0";
  ASSERT_EQ(rs.L(), (byte_t)0x00) << "Register L should start at 0";

  EXPECT_EQ(rs.SP(), (word_t)0x00) << "Register SP should start at 0";
  EXPECT_EQ(rs.PC(), (word_t)0x00) << "Register PC should start at 0";

  EXPECT_EQ(rs.AF(), (word_t)0x00) << "Composite Register AF should start at 0";
  EXPECT_EQ(rs.BC(), (word_t)0x00) << "Composite Register BC should start at 0";
  EXPECT_EQ(rs.DE(), (word_t)0x00) << "Composite Register DE should start at 0";
  EXPECT_EQ(rs.HL(), (word_t)0x00) << "Composite Register HL should start at 0";
}

TEST_F(RegisterSetTest, RegisterFIsGetFlags) {
  EXPECT_EQ(rs.F(), rs.GetFlags())
      << "Getflags should return same as register F";
}

TEST_P(RegisterSetFlagsTest, FlagsCanBeSetAndCleared) {
  rs.SetFlags(GetParam());
  EXPECT_EQ(rs.GetFlags(),
            std::underlying_type_t<RegisterSet::Flag>(GetParam()))
      << "Flag now set, and only flag set";

  ASSERT_EQ(rs.F(), rs.GetFlags())
      << "Get flags still returns same as F register";

  rs.ClearFlags(GetParam());
  EXPECT_EQ(rs.GetFlags(), 0) << "Flag is now unset";

  ASSERT_EQ(rs.F(), rs.GetFlags())
      << "Get flags still returns same as F register";
}

INSTANTIATE_TEST_SUITE_P(
    SingleFlagSetAndUnset, RegisterSetFlagsTest,
    testing::Values(RegisterSet::Flag::Z, RegisterSet::Flag::N,
                    RegisterSet::Flag::H, RegisterSet::Flag::C),
    [](const testing::TestParamInfo<RegisterSetFlagsTest::ParamType>& info) {
      using UT = std::underlying_type_t<RegisterSet::Flag>;
      switch (static_cast<UT>(info.param)) {
        case static_cast<UT>(RegisterSet::Flag::Z):
          return "ZFlag";
        case static_cast<UT>(RegisterSet::Flag::N):
          return "NFlag";
        case static_cast<UT>(RegisterSet::Flag::H):
          return "HFlag";
        case static_cast<UT>(RegisterSet::Flag::C):
          return "CFlag";
      }
    });

    */

}  // namespace tests
}  // namespace tanukigb